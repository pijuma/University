import java.util.Scanner;

public class Main {
    static public void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        //considerar o 0 como posição vazia
        // o usuario deve sempre colocar a posicao (0, 0) como vazia

        String entrada = scanner.nextLine() ;
        String[] valores = entrada.split(" ") ;
        String mov = scanner.nextLine() ;
        int n = (int) Math.sqrt(valores.length) ;

        Tabuleiro t1 = new Tabuleiro(n, valores, scanner) ;

        t1.printMatrix();

        // o usuario digita o movimento
        for(int i = 0 ; i < mov.length() ; i++) { // enquanto nao achou solucao, continue movimentando
            char type = mov.charAt(i);
            if (type == 'd') t1.getDown();
            else if (type == 'l') t1.getLeft();
            else if (type == 'u') t1.getUp();
            else t1.getRight();
            t1.printMatrix();
        }

        if(t1.findSolution()) System.out.println("Posicao final: true") ;
        else System.out.println("Posicao final: false");

    }
}
