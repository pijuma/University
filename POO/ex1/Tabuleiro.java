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
    private int[][] table ; // cria objeto matriz
    int xvazio, yvazio ;
    private Scanner scanner; // colocar como atributo privado da classe o scanner usando na main
    public Tabuleiro(int n, String[] valores, Scanner scanner) {
        table = new int[n][n] ;
        this.scanner = scanner ; // inicializando as coisa
        int id = 0 ;
        for(int i = 0 ; i < n ; i++) {
            for (int j = 0; j < n; j++) {
                if( Integer.parseInt(valores[id]) == 0){
                    this.xvazio = i ; this.yvazio = j ;
                }
                table[i][j] = Integer.parseInt(valores[id++]); //caso o usuario queira inserir manualmente
            }
        }
    }

    boolean valid(int x, int y){ // ta indo para um cara valido?
        return x >= 0 && y >= 0 && x < table.length && y < table[x].length ;
    }

    public void getLeft(){ //metodos para movimentacao
        if(!valid(xvazio, yvazio+1)) return ;
        int baixo = table[xvazio][yvazio+1] ;
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
        for(int j = 0 ; j < table.length ; j++){
            System.out.print("+------");
        }
        System.out.println("+");
        for(int i = 0 ; i < table.length ; i++){
            System.out.print("|");
            for(int j = 0 ; j < table.length ; j++){
                // %3d formata o numero, colocando espaços em branco caso o numero seja menor
                //pra sempre o quadrado da tabela ter o mesmo tamanho (3)
                System.out.printf(" %3d  |", + table[i][j]); // imprime sem quebra de linha
            }
            System.out.println();
            for(int j = 0 ; j < table.length ; j++){
                System.out.print("+------");
            }
            System.out.println("+"); //imprime com quebra de linha
        }
        System.out.println();
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
