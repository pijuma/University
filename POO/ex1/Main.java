package exercicio1;

import exercicio1.Tabuleiro;

import java.util.Scanner;

public class Main {
    static public void main(String[] agrs) {

        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt() ;
        int op = scanner.nextInt() ; // op = 1 entrada aleatoria/ op = 0 usuario digita

        //considerar o 0 como posição vazia
        // o usuario deve sempre colocar a posicao (0, 0) como vazia

        Tabuleiro t1 = new Tabuleiro(n, n, op, scanner) ;
        System.out.println("matriz inicial:\n");
        t1.printMatrix();

        // o usuario digita o movimento
        while(!t1.findSolution()){ // enquanto nao achou solucao, continue movimentando
            char type = scanner.next().charAt(0);
            if(type == 'D') t1.getDown();
            else if(type == 'L') t1.getLeft();
            else if(type == 'U') t1.getUp();
            else t1.getRight();
            t1.printMatrix();
        }
        System.out.println("terminou yey\n");
    }
}
