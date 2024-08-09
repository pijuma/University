import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class SearchMenu extends JFrame {
    private Socket cliente;
    private String filename;
    private JTextField idField;
    private JTextField ageField;
    private JTextField nameField;
    private JTextField nationalityField;
    private JTextField clubField;
    private JButton searchButton;
    private JButton listButton;

    public SearchMenu(String filename1, Socket socket1) {
        cliente = socket1;
        filename = filename1;
        setTitle("Buscar Jogadores");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 2));

        idField = new JTextField(20);
        ageField = new JTextField(20);
        nameField = new JTextField(20);
        nationalityField = new JTextField(20);
        clubField = new JTextField(20);
        searchButton = new JButton("PROCURAR");
        listButton = new JButton("LISTAR");
        Font font = new Font("Arial", Font.PLAIN, 36);
        idField.setFont(font);
        ageField.setFont(font);
        nameField.setFont(font);
        nationalityField.setFont(font);
        clubField.setFont(font);
        searchButton.setFont(font);
        listButton.setFont(font);

        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String id = "-1";
                String age = "-1";
                String name = "-1";
                String nationality = "-1";
                String club = "-1";
                int ct_not_null = 0;
                if (!idField.getText().trim().isEmpty()) {
                    id = idField.getText();
                    ct_not_null++;
                }
                if (!ageField.getText().trim().isEmpty()) {
                    age = ageField.getText();
                    ct_not_null++;
                }
                if (!nameField.getText().trim().isEmpty()) {
                    name = nameField.getText();
                    ct_not_null++;
                }
                if (!nationalityField.getText().trim().isEmpty()) {
                    nationality = nationalityField.getText();
                    ct_not_null++;
                }
                if (!clubField.getText().trim().isEmpty()) {
                    club = clubField.getText();
                    ct_not_null++;
                }
                
                String busca = "";

                try {
                    // Envia mensagem para o servidor
                    DataOutputStream saida = new DataOutputStream(cliente.getOutputStream());
                    String message = "Buscar " + filename + ".bin ";
                    message += ct_not_null + " ";

                    // quais campos buscar ? Formato: Nome do campo valor Nome do campo2 valor2
                    if (id != "-1")
                        message += "id " + id + " ";
                    if (age != "-1")
                        message += "idade " + age + " ";
                    if (name != "-1")
                        message += "nomeJogador " + name + " ";
                    if (nationality != "-1")
                        message += "nacionalidade " + nationality + " ";
                    if (club != "-1")
                        message += "nomeClube " + club + " ";

                    saida.writeUTF(message);
                    saida.flush();

                    // Recebe resposta do servidor
                    DataInputStream entrada = new DataInputStream(cliente.getInputStream());
                    // lê até o \0
                    StringBuilder resposta = new StringBuilder();
                    char c;
                    while ((c = (char) entrada.readByte()) != '\0') {
                        resposta.append(c);
                    }
                    
                    busca = resposta.toString();

                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                new ResultsMenu(busca, filename, cliente);
            }
        });

        listButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JTextArea textArea = new JTextArea(20, 40);
                try {
                    // Envia mensagem para o servidor
                    DataOutputStream saida = new DataOutputStream(cliente.getOutputStream());
                    String message = "Listar " + filename + ".bin";
                    saida.writeUTF(message);
                    saida.flush();

                    // Recebe resposta do servidor
                    DataInputStream entrada = new DataInputStream(cliente.getInputStream());
                    // lê até o \0
                    StringBuilder resposta = new StringBuilder();
                    char c;
                    while ((c = (char) entrada.readByte()) != '\0') {
                        resposta.append(c);
                    }
                    textArea.setText(resposta.toString());

                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                JOptionPane.showMessageDialog(null, new JScrollPane(textArea), "Listagem de Jogadores",
                        JOptionPane.INFORMATION_MESSAGE);
            }
        });

        JLabel idLabel = new JLabel("ID:");
        idLabel.setFont(font);
        add(idLabel);
        add(idField);

        JLabel ageLabel = new JLabel("Idade:");
        ageLabel.setFont(font);
        add(ageLabel);
        add(ageField);

        JLabel nameLabel = new JLabel("Nome do Jogador:");
        nameLabel.setFont(font);
        add(nameLabel);
        add(nameField);

        JLabel nationalityLabel = new JLabel("Nacionalidade:");
        nationalityLabel.setFont(font);
        add(nationalityLabel);
        add(nationalityField);

        JLabel clubLabel = new JLabel("Nome do Clube:");
        clubLabel.setFont(font);
        add(clubLabel);
        add(clubField);

        add(searchButton);
        add(listButton);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }
}
