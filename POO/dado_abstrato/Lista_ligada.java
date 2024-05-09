import java.util.Scanner ;
class Node <T>{

    public T val ;

    public Node<T> nxt ; //como ta publico nao precisa fazer um metodo para pegar nem settar next

    public Node(T at) {
        this.val =  at ;
        this.nxt = null ;
    }

    public String toString(){ return val.toString() ; }

    public T get_val(){ return this.val ; }

}

public class ListaLigada<T>{
    private Node<T> ini, lst ;
    int tam ;

    public ListaLigada(){
        ini = null ;
        lst = null ;
        tam = 0 ;
    }

    public String toString(){
        StringBuilder output = new StringBuilder();
        Node<T> current = ini;
        while(current != null){
            T value = current.val;
            output.append(value.toString()).append(" ");
            current = current.nxt;
        }
        return output.toString();
    }

    public void insertInit(T at){
        Node<T> neww = new Node<T>(at) ;//crio um novo no que tem como prox meu ini antigo
        //sou novo ini
        neww.nxt = ini ;
        ini = neww ;
        if(tam == 0){
            lst = neww ;
        }
        this.tam++ ;
    }

    public void insertEnd(T at){
        Node<T> neww = new Node<T>(at) ;//aponto pro fim
        if(this.lst!=null){//ja tenho algum
            lst.nxt = neww ;
        }
        this.lst = neww ;
        this.tam++ ;
    }

}
