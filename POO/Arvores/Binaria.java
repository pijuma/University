import java.util.Scanner ;
import java.util.Stack;

public class Binaria{
    protected int n_nos, TamMax ;
    protected String[] array ;
    Scanner scanner = new Scanner(System.in) ;

    public Binaria(){ // construtor inicializar vazio
        this.n_nos = 0 ; this.TamMax = 0 ;
        array = null ;
    }

    public Binaria(int size){

        this.TamMax = (1<<size)  ;
        array = new String[this.TamMax] ;

        for(int i = 0 ; i < this.TamMax ; i++){
            array[i] = null ; //inicialmente nao tem ninguem na arvore
        }

    }

    //retorna string pra usar no graphviz
    public String ToString(){
        StringBuilder output = new StringBuilder() ;
        output.append("digraph {\n") ;
        Stack<Integer> fila = new Stack<> () ;//fila pra bfs
        fila.push(0) ;
        if(this.n_nos == 1){
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

    protected void setNode(int node, String v){
        if(node >= this.TamMax) return ;
        if(node == -1 || v == null) return ;
        array[node] = v ;
    }

    protected int get_alt(int node){
        if(node >= this.TamMax || array[node] == null) return 0 ;
        return 1 + Math.max(get_alt(nodeLeft(node)), get_alt(nodeRight(node))) ;
    }

    // na binaria de busca sempre "esta balanceada"
    protected  boolean isBalance(){
        return true;
    }

    //retorna o valor de um nó
    protected String getNode(int node){
        if(node >= this.TamMax) return null ;
        return array[node] ;
    }
    public int CountNodes(){
        return this.n_nos ;
    }

    protected int nodeLeft(int node){
        return (2*node) + 1 ;
    }
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

    protected void rebalancear(){
        return ;
    }

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

    protected int find_max(int node){
        if(2*node + 2 >= this.TamMax) return node ;
        if(array[2*node+2] == null) return node ;
        return find_max(2*node + 2)  ;
    }

    protected int find_min(int node){
        if(2*node+1 >= this.TamMax) return node ;
        if(array[2*node+1] == null) return node ;
        return find_min(2*node + 1) ;
    }

    protected boolean recursive_rem(int node, String v){
        if(node >= this.TamMax) return false ;
        String atual = array[node] ;
        if(atual == null) return false ;
        if(v.compareTo(atual) == 0){
            array[node] = null ;
            if(2*node + 1 >= this.TamMax) return true ; // n tem filho
            if(array[2*node + 1] == null && array[2*node+2] == null) return true ; // n tem filho
            if(array[2*node+1] != null){ // tem filho esq
                int mx = find_max(2*node+1) ;
                array[node] = array[mx] ;
                recursive_rem(mx, array[mx]);
            }
            else if(2*node + 2 >= this.TamMax) return true ;
            else{ // tem filho dir
                int mn = find_min(2*node+2) ;
                array[node] = array[mn] ;
                recursive_rem(mn, array[mn]);
            }
            return true ;
        }
        else if(v.compareTo(atual) < 0) return recursive_rem(2*node + 1, v);
        else return recursive_rem(2*node + 2, v);
    }

    public boolean remove(String v){
        if(find(v) == false) return false ;
        boolean ok = recursive_rem(0, v) ;
        rebalancear() ;
        if(ok) this.n_nos-- ;
        return ok ;
    }

}
