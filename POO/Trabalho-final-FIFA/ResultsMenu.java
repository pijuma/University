import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class ResultsMenu extends JFrame {
    private String resultado_busca;
    private Socket cliente;
    private String filename;
    private JTable table;
    private DefaultTableModel tableModel;

    public ResultsMenu(String resultado_busca, String filename, Socket cliente) {
        this.resultado_busca = resultado_busca;
        this.cliente = cliente;
        this.filename = filename;
        setTitle("Resultados da Busca"); // Define o título da janela
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Configura o comportamento de fechamento da janela
        setLayout(new BorderLayout()); // Define o layout da janela como BorderLayout

        Font font = new Font("Arial", Font.PLAIN, 36);
        JButton searchButton = new JButton("PROCURAR");
        searchButton.setFont(font);

        // Define as colunas e os dados iniciais da tabela
        String[] columnNames = {"ID", "Idade", "Nome do Jogador", "Nacionalidade", "Nome do Clube", "Editar"};
        String linhas[] = resultado_busca.split("\n");

        Object[][] data = new Object[linhas.length][];

        for(int i = 0; i < linhas.length; i++) {
            String linha = linhas[i];
            String dados[] = linha.split("/");
            if (dados.length >=5) {
                data[i] = new Object[] {
                    Integer.parseInt(dados[0].trim()),   
                    Integer.parseInt(dados[1].trim()),  // Idade (converte para inteiro)
                    dados[2].trim(),  // Nome do Jogador
                    dados[3].trim(),  // Nacionalidade
                    dados[4].trim(),  // Nome do Clube
                    "Editar"          // Texto para o botão "Editar"
                };
            } else {
                // deu erro - registro inexistente.
                JOptionPane.showMessageDialog(null, "REGISTRO INEXISTE OU É INVÁLIDO", "Erro", JOptionPane.ERROR_MESSAGE);
                return;
            }
        }

        // Cria o modelo da tabela com os dados e colunas definidos
        tableModel = new DefaultTableModel(data, columnNames) {
            @Override
            public boolean isCellEditable(int row, int column) {
                // Sobrescreve o método para desativar a edição direta nas células, exceto na coluna "Editar"
                return column == 5; // Permite a edição apenas na coluna "Editar"
            }
        };
        
        // Cria a tabela usando o modelo de tabela personalizado
        table = new JTable(tableModel);
        table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        // Configura o renderizador e editor para a coluna "Editar"
        table.getColumn("Editar").setCellRenderer(new ButtonRenderer());
        table.getColumn("Editar").setCellEditor(new ButtonEditor(new JCheckBox(), table));

        // Adiciona a tabela dentro de um JScrollPane para rolagem
        add(new JScrollPane(table), BorderLayout.CENTER);

        // Empacota os componentes e exibe a janela
        pack();
        setLocationRelativeTo(null); // Centraliza a janela na tela
        setVisible(true); // Torna a janela visível
    }

    // Classe interna para renderizar o botão "Editar" na tabela
    class ButtonRenderer extends JButton implements TableCellRenderer {
        public ButtonRenderer() {
            setOpaque(true); // Garante que o componente seja opaco
        }

        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
            // Define o texto do botão com o valor da célula
            setText((value == null) ? "" : value.toString());
            return this; // Retorna o próprio componente (botão)
        }
    }

    // Classe interna para editar o botão "Editar" na tabela
    class ButtonEditor extends DefaultCellEditor {
        protected JButton button;
        private String label;
        private boolean isPushed;
        private JTable table;
        private int row;

        public ButtonEditor(JCheckBox checkBox, JTable table) {
            super(checkBox); // Chama o construtor da superclasse DefaultCellEditor
            this.table = table;
            button = new JButton(); // Cria um novo botão para edição
            button.setOpaque(true); // Garante que o botão seja opaco
            button.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    fireEditingStopped(); // Dispara o evento de edição encerrada
                }
            });
        }

        // Retorna o componente para edição na célula da tabela
        public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column) {
            this.row = row; // Armazena o índice da linha
            label = (value == null) ? "" : value.toString(); // Armazena o texto do botão
            button.setText(label); // Define o texto do botão
            isPushed = true; // Define que o botão foi pressionado
            return button; // Retorna o botão para edição
        }

        // Retorna o valor da célula após a edição
        public Object getCellEditorValue() {
            if (isPushed) {
                if (row < 0 || row >= table.getRowCount()) {
                    isPushed = false;
                    return label; // Retorna o texto original se a linha for inválida
                }

                // Obtém os valores atuais da linha da tabela
                Object playerId = table.getValueAt(row, 0);
                Object playerAge = table.getValueAt(row, 1);
                Object playerName = table.getValueAt(row, 2);
                Object playerNationality = table.getValueAt(row, 3);
                Object playerClub = table.getValueAt(row, 4);

                // Cria um diálogo de edição para o jogador selecionado
                PlayerDetails editDialog = new PlayerDetails(
                    playerId, playerAge, playerName, playerNationality, playerClub, row, ResultsMenu.this);
                editDialog.setVisible(true); // Exibe o diálogo de edição

                // Se as alterações forem salvas, atualiza os valores na tabela
                if (editDialog.isSaved()) {
                    // MEÇO DIRETO NO ARQUIVO - OPERAÇÃO DE ATUALIZAR
                    String id = (String) editDialog.getPlayerId();
                    String nova_idade = (String) editDialog.getPlayerAge();
                    String novo_nome = (String) editDialog.getPlayerName();
                    String nova_nacionalidade = (String) editDialog.getPlayerNationality();
                    String novo_clube = (String) editDialog.getPlayerClub();
                    
                    String resultado_busca_atualizado = "";

                    try {
                        // Envia mensagem para o servidor para remover no arquivo
                        DataOutputStream saida = new DataOutputStream(cliente.getOutputStream());
                        String message = "Remover " + filename + ".bin " + id;
                        saida.writeUTF(message);
                        saida.flush();

                        DataOutputStream saida2 = new DataOutputStream(cliente.getOutputStream());
                        if (id == null || id.trim().isEmpty()) id = "NULO";
                        if (nova_idade == null || nova_idade.trim().isEmpty()) nova_idade = "NULO";
                        if (novo_nome == null || novo_nome.trim().isEmpty()) novo_nome = "NULO";
                        if (nova_nacionalidade == null || nova_nacionalidade.trim().isEmpty()) nova_nacionalidade = "NULO";
                        if (novo_clube == null || novo_clube.trim().isEmpty()) novo_clube = "NULO";
                        String message2 = "Inserir/#-" + filename + ".bin/#-" + id + "/#-" + nova_idade + "/#-" + novo_nome + "/#-" + nova_nacionalidade + "/#-" + novo_clube;
                        saida2.writeUTF(message2);
                        saida2.flush();

                        String linhas[] = resultado_busca.split("\n");

                        for(String linha : linhas) {
                            String dados[] = linha.split("/");
                            if (!dados[0].equals(id)) {
                                resultado_busca_atualizado += linha;
                                resultado_busca_atualizado += '\n';
                            } else {
                                dados[0] = id;
                                dados[1] = nova_idade;
                                dados[2] = novo_nome;
                                dados[3] = nova_nacionalidade;
                                dados[4] = novo_clube;
                                resultado_busca_atualizado += String.join("/", dados);
                                resultado_busca_atualizado += '\n';
                            }
                        }
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }

                    ResultsMenu.this.dispose();
                    // remover ele da minha string para recarregar a pagina da tabela

                    // chamar o resultsMenu novamente
                    new ResultsMenu(resultado_busca_atualizado, filename, cliente);
                }

                if (editDialog.isDeleted()) {
                    // MEÇO DIRETO NO ARQUIVO - OPERAÇÃO DE REMOVER
                    String id = (String) editDialog.getPlayerId();
                    String resultado_busca_atualizado = "";
                    try {
                        // Envia mensagem para o servidor para remover no arquivo
                        DataOutputStream saida = new DataOutputStream(cliente.getOutputStream());
                        String message = "Remover " + filename + ".bin " + id;
                        saida.writeUTF(message);
                        saida.flush();

                        String linhas[] = resultado_busca.split("\n");

                        for(String linha : linhas) {
                            String dados[] = linha.split("/");
                            if (!dados[0].equals(id)) {
                                resultado_busca_atualizado += linha;
                                resultado_busca_atualizado += '\n';
                            } 
                        }
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                    
                    ResultsMenu.this.dispose();
                    // remover ele da minha string para recarregar a pagina da tabela

                    // chamar o resultsMenu novamente
                    new ResultsMenu(resultado_busca_atualizado, filename, cliente);
                }
            }
            isPushed = false; // Reseta a flag de botão pressionado
            return label; // Retorna o texto do botão
        }

        // Interrompe a edição da célula
        public boolean stopCellEditing() {
            isPushed = false; // Reseta a flag de botão pressionado
            return super.stopCellEditing(); // Chama o método da superclasse para parar a edição
        }

        // Dispara o evento de edição encerrada
        protected void fireEditingStopped() {
            super.fireEditingStopped(); // Chama o método da superclasse para disparar o evento
        }
    }
}
