package exercicio1;

import exercicio1.Tabuleiro;

import java.util.Scanner;

public class Main {
    static public void main(String[] agrs) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt() ;
        Tabuleiro t1 = new Tabuleiro(n, n) ;
        while(!t1.findSolution()){
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
