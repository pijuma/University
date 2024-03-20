package exercicio1;

import exercicio1.Tabuleiro;

import java.util.Scanner;

public class Main {
    static public void main(String[] agrs) {

        Scanner scanner = new Scanner(System.in);
        //considerar o 0 como posição vazia
        // o usuario deve sempre colocar a posicao (0, 0) como vazia

        String entrada = scanner.nextLine() ;
        String[] valores = entrada.split(" ") ;
        int n = (int) Math.sqrt(valores.length) ;
        if(n*n != valores.length){
            System.out.println("nao forma matriz quadrada");
            return ;
        }

        Tabuleiro t1 = new Tabuleiro(n, valores, scanner) ;
        String mov = scanner.nextLine() ;

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

        if(t1.findSolution()) System.out.println("Posição final: true\n") ;
        else System.out.println("Posição final: false\n");

    }
}
