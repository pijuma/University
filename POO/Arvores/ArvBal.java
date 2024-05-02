import java.util.Scanner;

public class ArvBal extends Binaria{
    protected int atual ;
    Scanner scanner = new Scanner(System.in) ;

    public ArvBal(){ // construtor inicializar vazio
        super() ;
    }

    public ArvBal(int size){
        super(size) ;
    }

    //percorrer o vetor ordenado
    //mudar array colocando a nova arvore
    //pego o valor do meio coloco como nó atual e passo pra esquerda e direita colocando
    // os valores menores que o nó na esq [l, mid-1] e maiores que o nó na direita [mid+1, r]
    protected void recursive_balance(int node, int l, int r, String []ord){
        if(l > r) return ;
        if(node >= this.TamMax) return ;
        //meio eh minha nova raiz
        int mid = (l+r)/2 ;
        array[node] = ord[mid] ;
        recursive_balance((2*node)+1, l, mid-1, ord);
        recursive_balance((2*node)+2, mid+1, r, ord);
    }

    //percorrer esq atual dir -> dfs
    protected void ordenar(int node, String[] ord){
        if(node >= this.TamMax) return ;
        if(array[node] == null) return ;
        //filho esq 1o
        ordenar(((2*node) + 1), ord);
        //colocar meu kra atual
        ord[++this.atual] = array[node] ;
        ordenar(((2*node)+2), ord) ;
    }

    // pego o vetor do jeito que ta na avl, ordenado ja
    // crio um novo rebalanceando
    @Override
    protected void rebalancear(){
        if(isBalance()) return ;
        this.atual = -1 ;
        String[] ord = new String[this.TamMax] ;
        ordenar(0, ord) ;
        //for(int i = 0 ; i < this.n_nos ; i++) System.out.println(ord[i]);
        int fim = this.atual ;
        for(int i = 0 ; i < this.TamMax ; i++) array[i] = null ; // apagar tudo do antigo p reescrever
        recursive_balance(0, 0, fim, ord) ;
        //em array sera guardado a nova arvore balanceada
    }

    // percorre todos nós para ver se a arvore está balanceada
    // ou seja se a altura de duas subs "irmãs" difere em no máximo 1
    protected boolean check_alt(int node){
        if(array[node] == null) return true ;
        boolean ok = check_alt(nodeLeft(node))&check_alt(nodeRight(node)) ;
        if(Math.abs(get_alt(nodeLeft(node)) - get_alt(nodeRight(node))) > 1) return false ;
        return ok ;
    }

    //diferenca das alturas no max 1 sempre
    @Override
    protected  boolean isBalance(){
        return check_alt(0) ;
    }

}
