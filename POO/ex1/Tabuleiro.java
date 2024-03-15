package exercicio1;

import java.util.Scanner;

/*
considerei que
0 1 2
3 4 5
6 7 8
é uma solução, pois o 0 representa uma posição vazia,
considerei que só acaba quando a posição vazia estiver no canto (0, 0)
o programa só encerra quando acha uma matriz que é solução
 */
public class Tabuleiro {
    Scanner scanner = new Scanner(System.in);
    private int[][] table ; // cria objeto matriz
    int xvazio, yvazio ;
    // posicao vazia sempre é (0, 0) inicialmente
    public Tabuleiro(int n, int m) {
        table = new int[n][m] ;
        this.xvazio = 0 ;
        this.yvazio = 0 ;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < table[i].length ; j++){
                table[i][j] = scanner.nextInt() ;
            }
        }
    }

    boolean valid(int x, int y){ // ta indo para um cara valido?
        return x >= 0 && y >= 0 && x < table.length && y < table[x].length ;
    }

    public void getLeft(){
        if(!valid(xvazio, yvazio+1)) return ;
        int baixo = table[xvazio][yvazio+1] ;
        System.out.println(baixo);
        table[xvazio][yvazio+1] = 0 ;
        table[xvazio][yvazio] = baixo ;
        yvazio++ ;
    }
    public void getRight(){
        if(!valid(xvazio, yvazio-1)) return ;
        int posCima = table[xvazio][yvazio-1] ;
        table[xvazio][yvazio-1] = 0 ;
        table[xvazio][yvazio] = posCima ;
        yvazio-- ;
    }

    public void getUp(){
        if(!valid(xvazio+1, yvazio)) return ;
        int dir = table[xvazio+1][yvazio] ;
        table[xvazio+1][yvazio] = 0 ;
        table[xvazio][yvazio] = dir ;
        xvazio++ ;
    }

    public void getDown(){
        if(!valid(xvazio-1, yvazio)) return ;
        int dir = table[xvazio-1][yvazio] ;
        table[xvazio-1][yvazio] = 0 ;
        table[xvazio][yvazio] = dir ;
        xvazio-- ;
    }

    public void printMatrix(){
        for(int i = 0 ; i < table.length ; i++){
            for(int j = 0 ; j < table[i].length ; j++){
                System.out.print(table[i][j] + " ");
            }
            System.out.println();
        }
    }

    public boolean findSolution(){
        int ct = 1 ;
        for(int i = 0 ; i < table.length ; i++){
            for(int j = 0 ; j < table[i].length ; j++){
                if(i == 0 && j == 0) continue ;
                if(table[i][j] != ct) return false ;
                ct++ ;
            }
        }
        return true ;
    }

}
