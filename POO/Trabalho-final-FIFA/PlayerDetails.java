import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JTextField;

class PlayerDetails extends JDialog {
    private JTextField txtPlayerId;
    private JTextField txtPlayerAge;
    private JTextField txtPlayerName;
    private JTextField txtPlayerNationality;
    private JTextField txtPlayerClub;
    private boolean saved, deleted;

    public PlayerDetails(Object playerId, Object playerAge, Object playerName, Object playerNationality, Object playerClub, int row, ResultsMenu parent) {
        setTitle("Editar Jogador"); // Define o título do diálogo
        setModal(true); // Define o diálogo como modal (bloqueia interações com a janela principal)
        setLayout(new GridLayout(6, 2)); // Define o layout do diálogo
        setSize(400, 300); // Define o tamanho do diálogo

        // Cria campos de texto para editar as informações do jogador
        txtPlayerId = new JTextField(playerId.toString());
        txtPlayerId.setEditable(false); // Impede a edição do ID do jogador
        txtPlayerAge = new JTextField(playerAge.toString());
        txtPlayerName = new JTextField(playerName.toString());
        txtPlayerNationality = new JTextField(playerNationality.toString());
        txtPlayerClub = new JTextField(playerClub.toString());

        // Adiciona rótulos e campos de texto ao diálogo
        add(new JLabel("ID:"));
        add(txtPlayerId);
        add(new JLabel("Idade:"));
        add(txtPlayerAge);
        add(new JLabel("Nome do Jogador:"));
        add(txtPlayerName);
        add(new JLabel("Nacionalidade:"));
        add(txtPlayerNationality);
        add(new JLabel("Nome do Clube:"));
        add(txtPlayerClub);

        // Cria botões para salvar ou cancelar as edições
        JButton btnSave = new JButton("Salvar");
        btnSave.addActionListener(e -> {
            saved = true; // Marca que as alterações foram salvas
            dispose(); // Fecha o diálogo
        });
        JButton btnRemove = new JButton("Remover");
        btnRemove.addActionListener(e -> {
            deleted = true;
            dispose();
        }); // Fecha o diálogo sem salvar as alterações

        // Adiciona os botões ao diálogo
        add(btnSave);
        add(btnRemove);

        setLocationRelativeTo(null); // Centraliza o diálogo na tela
    }

    // Retorna se as alterações foram salvas
    public boolean isSaved() {
        return saved;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public Object getPlayerId() {
        return txtPlayerId.getText();
    }

    // Retorna a idade do jogador editada
    public Object getPlayerAge() {
        return txtPlayerAge.getText();
    }

    // Retorna o nome do jogador editado
    public Object getPlayerName() {
        return txtPlayerName.getText();
    }

    // Retorna a nacionalidade do jogador editada
    public Object getPlayerNationality() {
        return txtPlayerNationality.getText();
    }

    // Retorna o clube do jogador editado
    public Object getPlayerClub() {
        return txtPlayerClub.getText();
    }
}