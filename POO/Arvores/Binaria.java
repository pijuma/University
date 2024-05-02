import java.util.Scanner ;
import java.util.Stack;
//arvore "pai"
public class Binaria{
    protected int n_nos, TamMax ;
    protected String[] array ;
    Scanner scanner = new Scanner(System.in) ;

    public Binaria(){ // construtor inicializar vazio
        this.n_nos = 0 ; this.TamMax = 0 ;
        array = null ;
    }
    //construtores
    public Binaria(int size){

        this.TamMax = (1<<size)  ;
        array = new String[this.TamMax] ;
        //colocar todas as posições vazias como nullo, nao existem nós
        for(int i = 0 ; i < this.TamMax ; i++){
            array[i] = null ; //inicialmente nao tem ninguem na arvore
        }

    }

    //metodo ToString
    //padroniza em uma String todos os valores escritos nos nós
    //usado para retornar a arvore como saida
    public String ToString(){
        StringBuilder output = new StringBuilder() ;
        output.append("digraph {\n") ;
        if(this.n_nos == 1){//se tiver apenas um nó nao temos arestas para add mas queremos imprimir o nó existente
            output.append(String.format("\"%d %s\"", 0, array[0]));
            output.append(" }") ;
            return output.toString() ;
        }
        for(int i = 0 ; i < this.TamMax ; i++){
            if(array[i] == null) continue ;
            int at = i ;
            int esq = (2*at) + 1, dir = (2*at) + 2 ;
            if(esq < this.TamMax){
                if(array[esq]!=null){
                    output.append(String.format("\"%d %s\" ->\"%d %s\" \n", at, array[at], esq, array[esq])) ;
                }
            }
            if(dir < this.TamMax){
                if(array[dir] != null){
                    output.append(String.format("\"%d %s\" ->\"%d %s\" \n", at, array[at], dir, array[dir])) ;
                }
            }
        }
        output.append("}") ;
        return output.toString() ;
    }

    //mudar o valor guardado em um nó
    protected void setNode(int node, String v){
        if(node >= this.TamMax) return ;
        if(node == -1 || v == null) return ;
        array[node] = v ;
    }
    //função recursiva que retorna a altura de um nó
    protected int get_alt(int node){
        if(node >= this.TamMax || array[node] == null) return 0 ;
        return 1 + Math.max(get_alt(nodeLeft(node)), get_alt(nodeRight(node))) ;
    }

    //checa se é balanceada
    //nessa classe essa função não faz muito sentido pois não existe balanceamento
    //porem para a herança ela será sobrescrita utilizando o conceito de balanceado da arvore implementada em cada classe
    protected  boolean isBalance(){
        return true;
    }

    //retorna o valor de um nó
    protected String getNode(int node){
        if(node >= this.TamMax) return null ;
        return array[node] ;
    }

    //retorna a quantidade de nós ativos
    public int CountNodes(){
        return this.n_nos ;
    }

    //retorna o nó esquerdo de um dado nó
    protected int nodeLeft(int node){
        return (2*node) + 1 ;
    }

    //retorna o nó direito de um dado nó
    protected  int nodeRight(int node){
        return (2*node) + 2 ;
    }

    // inserir um novo no
    protected void recursive_insert(int node, String v){
        if(node >= this.TamMax) return ;
        String atual = array[node] ;
        if(atual == null){// achei local pra inserir
            array[node] = v ;
            return ;
        }
        else if(v.compareTo(atual) < 0) recursive_insert(2*node + 1, v);
        else recursive_insert(2*node + 2, v) ;
    }

    //usado apenas para as outras classes já que nessa não temos balanceamento
    protected void rebalancear(){
        return ;
    }

    //checar se um nó existe -> feito com busca binária
    protected boolean find_node(int node, String v){
        if(node >= this.TamMax) return false ;
        String atual = array[node] ;
        if(atual == null) return false ;
        if(v.compareTo(atual) == 0)  return true ; // achou
        else if(v.compareTo(atual) < 0) return find_node(2*node + 1, v) ;
        else return find_node(2*node + 2, v) ;
    }

    public boolean find(String v){
        return find_node(0, v) ;
    }

    public void insert(String v){
        if(find(v)) return ; // já está na arvore
        recursive_insert(0, v) ;
        this.n_nos++ ;
        rebalancear() ;
    }

    //achar o maior valor de um nó de uma subarvore -> utilizado na remoção
    protected int find_max(int node){
        if(2*node + 2 >= this.TamMax) return node ;
        if(array[2*node+2] == null) return node ;
        return find_max(2*node + 2)  ;
    }

    //achar o menor valor de um nó em uma subarvore
    protected int find_min(int node){
        if(2*node+1 >= this.TamMax) return node ;
        if(array[2*node+1] == null) return node ;
        return find_min(2*node + 1) ;
    }

    //remoção
    protected boolean recursive_rem(int node, String v){
        if(node >= this.TamMax) return false ;
        String atual = array[node] ;
        if(atual == null) return false ;
        if(v.compareTo(atual) == 0){ //achamos a posição a ser removida
            array[node] = null ;// null diz que não tem nó na dada posição
            if(2*node + 1 >= this.TamMax) return true ; // n tem filho -> basta "remover" meu nó
            if(array[2*node + 1] == null && (2*node + 1 >= this.TamMax || array[2*node+2] == null)) return true ; // n tem filho
            if(array[2*node+1] != null){ // tem filho esq
                int mx = find_max(2*node+1) ; // coloco o maior cara da minha sub do meu filho esquerdo pra me substituir
                //assim não quebra a estrutura da arvore binaria
                array[node] = array[mx] ;
                recursive_rem(mx, array[mx]);//removo esse meu mx ja que ele agora esta em "node"
            }
            else if(2*node + 2 >= this.TamMax) return true ;
            else{ // tem filho dir
                int mn = find_min(2*node+2) ;//faço a mesma coisa mas agora pegando o min na subarvore direita
                array[node] = array[mn] ;
                recursive_rem(mn, array[mn]);
            }
            return true ;
        }
        //procurando o no a ser removido
        else if(v.compareTo(atual) < 0) return recursive_rem(2*node + 1, v);
        else return recursive_rem(2*node + 2, v);
    }

    public boolean remove(String v){
        if(find(v) == false) return false ; //se o nó não existe não tem oq remover
        boolean ok = recursive_rem(0, v) ;
        rebalancear() ;
        if(ok) this.n_nos-- ;
        return ok ;
    }

}
