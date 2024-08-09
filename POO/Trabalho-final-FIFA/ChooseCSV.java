import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class ChooseCSV extends JFrame implements ActionListener {

    private Socket cliente;
    private DataOutputStream saida;  // DataOutputStream para enviar dados ao servidor

    public ChooseCSV(Socket cliente) {
        this.cliente = cliente;
        setTitle("Escolha um arquivo");

        // Configuração da interface gráfica
        JMenuBar barra = new JMenuBar();
        setJMenuBar(barra);
        JMenu arquivos = new JMenu("Arquivos");
        JMenu abrir_arquivos = new JMenu("Abrir");

        JMenuItem fifa17 = new JMenuItem("FIFA 2017");
        JMenuItem fifa18 = new JMenuItem("FIFA 2018");
        JMenuItem fifa19 = new JMenuItem("FIFA 2019");
        JMenuItem fifa20 = new JMenuItem("FIFA 2020");
        JMenuItem fifa21 = new JMenuItem("FIFA 2021");
        JMenuItem fifa22 = new JMenuItem("FIFA 2022");
        JMenuItem fifa23 = new JMenuItem("FIFA 2023");

        abrir_arquivos.add(fifa17);
        abrir_arquivos.add(fifa18);
        abrir_arquivos.add(fifa19);
        abrir_arquivos.add(fifa20);
        abrir_arquivos.add(fifa21);
        abrir_arquivos.add(fifa22);
        abrir_arquivos.add(fifa23);

        arquivos.add(abrir_arquivos);
        barra.add(arquivos);

        Font font = new Font("Arial", Font.PLAIN, 25);

        fifa17.setFont(font);
        fifa18.setFont(font);
        fifa19.setFont(font);
        fifa20.setFont(font);
        fifa21.setFont(font);
        fifa22.setFont(font);
        fifa23.setFont(font);
        arquivos.setFont(font);
        abrir_arquivos.setFont(font);

        fifa17.setActionCommand("binario1");
        fifa17.addActionListener(this);
        fifa18.setActionCommand("binario2");
        fifa18.addActionListener(this);
        fifa19.setActionCommand("binario3");
        fifa19.addActionListener(this);
        fifa20.setActionCommand("binario4");
        fifa20.addActionListener(this);
        fifa21.setActionCommand("binario5");
        fifa21.addActionListener(this);
        fifa22.setActionCommand("binario6");
        fifa22.addActionListener(this);
        fifa23.setActionCommand("binario7");
        fifa23.addActionListener(this);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        // Inicializa o DataOutputStream para enviar dados ao servidor
        try {
            saida = new DataOutputStream(cliente.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
            // Trate a exceção adequadamente
        }
    }
 
    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();

        try {
            String message = "Carregar " + command + ".bin";
            saida.writeUTF(message);
            saida.flush();  // Certifica-se de que todos os dados sejam enviados

            // Fecha o DataOutputStream após o envio
        } catch (IOException ex) {
            ex.printStackTrace();  // Trate a exceção adequadamente
        }

        new SearchMenu(command, cliente);
    }
}
