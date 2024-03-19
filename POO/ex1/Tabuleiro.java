package exercicio1;

import java.util.Scanner;
import java.util.ArrayList ;
import java.util.Collections ;

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
    private int[][] table ; // cria objeto matriz
    int xvazio, yvazio ;
    private Scanner scanner; // colocar como atributo privado da classe o scanner usando na main
    // posicao vazia sempre é (0, 0) inicialmente
    public Tabuleiro(int n, int m, int op, Scanner scanner) {
        table = new int[n][m] ;
        this.xvazio = 0 ;
        this.yvazio = 0 ;
        this.scanner = scanner ; // inicializando as coisas
        if(op==1) { //matriz aleatoria
            ArrayList<String> lista = new ArrayList<>() ; // cria um array - similar ao "vector"
            for(int i = 1 ; i < n*n ; i++){
                lista.add(Integer.toString(i)) ;
            }
            Collections.shuffle(lista) ;//embaralha
            int ct = 0 ;
            for(int i = 0 ; i < n ; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j && i == 0) {
                        table[i][j] = 0;
                        continue;
                    }
                    table[i][j] = Integer.parseInt(lista.get(ct++)); // pega o valor da pos ct
                }
            }
        }
        else{
            for(int i = 0 ; i < n ; i++){
                for(int j = 0 ; j < n ; j++){
                    table[i][j] = scanner.nextInt(); //caso o usuario queira inserir manualmente
                }
            }
        }
    }

    boolean valid(int x, int y){ // ta indo para um cara valido?
        return x >= 0 && y >= 0 && x < table.length && y < table[x].length ;
    }

    public void getLeft(){ //metodos para movimentacao
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

    public void printMatrix(){ //metodo para imprimir a matriz
        for(int i = 0 ; i < table.length ; i++){
            for(int j = 0 ; j < table[i].length ; j++){
                System.out.print(table[i][j] + " "); // imprime sem quebra de linha
            }
            System.out.println();//imprime quebra de linha
        }
    }

    public boolean findSolution(){ //achou solucao?
        int ct = 1 ;
        if(table[0][0] != 0) return false ;
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
