import javax.swing.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class IPPage extends JFrame {
    private JTextField campoIp;
    private JButton botaoCarregar;
    private JLabel label;

    public IPPage() {
        setTitle("Setar IP");
        setLayout(new GridLayout(3, 1));

        campoIp = new JTextField(20);
        botaoCarregar = new JButton("Tentar conexão");
        label = new JLabel("Endereço IP do servidor:");

        Font font = new Font("Arial", Font.PLAIN, 36);
        campoIp.setFont(font);
        botaoCarregar.setFont(font);
        label.setFont(font);

        botaoCarregar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String nomeServer = campoIp.getText();
                System.out.println("Tentando conectar ao servidor: " + nomeServer);

                int port = 50000; // Porta configurada no servidor Python
                
                Socket cliente = null;

                try {
                    cliente = new Socket(nomeServer, port);
                    System.out.println("Conexão estabelecida com sucesso!");

                    new ChooseCSV(cliente);

                } catch (UnknownHostException err) {
                    err.printStackTrace();
                    JOptionPane.showMessageDialog(null, "Host desconhecido: " + nomeServer, "Erro de conexão", JOptionPane.ERROR_MESSAGE);
                } catch (IOException err) {
                    err.printStackTrace();
                    JOptionPane.showMessageDialog(null, "Erro ao conectar ao servidor: " + nomeServer, "Erro de conexão", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        add(label);
        add(campoIp);
        add(botaoCarregar);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new IPPage();
            }
        });
    }
}
