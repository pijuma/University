public class AVL extends Binaria{

    public AVL(){ // construtor inicializar vazio
        super() ;
    }

    public AVL(int size){
        super(size) ;
    }

    //funcao para calcular fator de balanceamento de um no
    int fb(int node){
        if(node >= this.TamMax || array[node] == null) return -1000000 ;
        return get_alt(nodeLeft(node)) - get_alt(nodeRight(node)) ;
    }

    //rotações necessarias na insercao e remocao
    protected void RodaEsq(int node){
        String [] copy = new String[this.TamMax] ;

        for(int i = 0 ; i < this.TamMax ; i++){
            copy[i] = array[i] ;
        }

        // trocar T1
        // eat vira eeat
        int eat = nodeLeft(node) ;
        int eeat = nodeLeft(nodeLeft(node)) ;
        // filhos de eeat viram filhos de eat -> arrumei t1
        move_sub(eeat, eat, copy) ;

        // trocar T2
        // edat vira deat
        int edat = nodeLeft(nodeRight(node)) ;
        int deat = nodeRight(nodeLeft(node)) ;
        move_sub(deat, edat, copy);

        //trocar T3
        // ddat vira dat
        int dat = nodeRight(node) ;
        int ddat = nodeRight(nodeRight(node)) ;
        move_sub(dat, ddat, copy);

        copy[node] = array[nodeRight(node)] ;
        copy[nodeLeft(node)] = array[node] ;

        for(int i = 0 ; i < this.TamMax ; i++){
            array[i] = copy[i] ;
        }

    }

    //funcao para mover uma subarvore de um lugar para outro
    //vou de nó a nó mudando a posição da subarvore da posicao antiga para nova
    // para nao ter problemas uso um outro vetor para atualizar a arvore nova e depois
    //copio esse vetor para o antigo (com a nova AVL)
    protected void move_sub(int new_at, int at, String [] neww){
        if(at >= this.TamMax || new_at >= this.TamMax) return ;
        neww[new_at] = array[at] ;
        move_sub(nodeLeft(new_at), nodeLeft(at), neww);
        move_sub(nodeRight(new_at), nodeRight(at), neww);
    }

    //rotacao direita
    protected void RodaDir(int node){
        String [] copy = new String[this.TamMax] ;

        for(int i = 0 ; i < this.TamMax ; i++){
            copy[i] = array[i] ;
        }

        int eat = nodeLeft(node) ;
        int eeat = nodeLeft(nodeLeft(node)) ;
        // filhos de eeat viram filhos de eat -> arrumei t1
        move_sub(eat, eeat, copy) ;

        //filhos deat viram filhos de edat -> arrumei t2
        int deat = nodeRight(nodeLeft((node))) ;
        int edat = nodeLeft(nodeRight(node)) ;
        move_sub(edat, deat, copy);

        //filhos dat viram filho de ddat -> arrumei t3
        int dat = nodeRight(node) ;
        int ddat = nodeRight(nodeRight(node)) ;
        move_sub(ddat, dat, copy);

        //arrumar 1
        copy[node] = array[nodeLeft(node)] ;
        copy[nodeRight(node)] = array[node] ;

        for(int i = 0 ; i < this.TamMax ; i++){
            array[i] = copy[i] ;
        }

    }

    //rotação dupla: Esq + Dir
    protected void RodarEsqDir(int node){
        RodaEsq(nodeLeft(node));
        RodaDir(node);
    }

    //rotação dupla: Dir + Esq
    protected void RodarDirEsq(int node){
        RodaDir(nodeRight(node));
        RodaEsq(node);
    }

    //troco meu vertice com o maior que esta na subarvore do meu filho esquerdo
    protected void TrocaMaxEsq(int node){
        int mx = find_max(nodeLeft(node)) ;
        array[node] = array[mx] ;
    }
    @Override
    protected void recursive_insert(int node, String v){
        if(node >= this.TamMax) return ;
        if(array[node] == null){
            array[node] = v ;
        }
        else if(array[node].compareTo(v) < 0) recursive_insert(nodeRight(node), v);
        else if(array[node].compareTo(v) > 0) recursive_insert(nodeLeft(node), v);

        // esta balanceada? Quais rotações devo fazer?
        if(fb(node) == 2){
            if(array[nodeLeft(node)].compareTo(v) < 0) RodarEsqDir(node) ;
            else RodaDir(node);
        }

        else if(fb(node) == -2){
            if(array[nodeRight(node)].compareTo(v) > 0) RodarDirEsq(node) ;
            else RodaEsq(node) ;
        }

    }

    // faço a mudança de uma subarvore de um lugar para outro
    //fiz a função apenas para organizar por conta das copias de objetos criados
    //que ficariam chatas de fazer no meio do código
    protected  void rearruma(int novo, int ant){
        if(ant == -1 || ant >= this.TamMax || array[ant] == null) return ;
        String [] copy = new String[this.TamMax] ;

        for(int i = 0 ; i < this.TamMax ; i++){
            copy[i] = array[i] ;
        }

        move_sub(novo, ant, copy);

        for(int i = 0 ; i < this.TamMax ; i++){
            array[i] = copy[i] ;
        }

    }

    //dado meu nó, quem é meu pai? Uso na remoção
    protected int pai(int node){
        return (node-1)/2 ;
    }

    @Override
    protected boolean recursive_rem(int node, String v){
        if(node >= this.TamMax || array[node] == null) return false;
        if(array[node].compareTo(v)==0){//achei o nó pra remover
            array[node] = null ;
            //tenho um ou nenhum filho
            if(nodeRight(node) >= this.TamMax || nodeLeft((node)) >= this.TamMax || array[nodeLeft(node)] == null || array[nodeRight(node)] == null){
                if(nodeRight(node) >= this.TamMax && nodeLeft(node) >= this.TamMax){
                    array[node] = null ; //apago meu nó atual
                }
                else if(array[nodeRight(node)] == null && array[nodeLeft(node)] == null) array[node] = null ; // nao faco nada
                else if(nodeRight(node) >= this.TamMax || array[nodeRight(node)] == null){//tenho filho esq
                    array[node] = array[nodeLeft(node)] ;
                    array[nodeLeft(node)] =  null ;
                    rearruma(nodeRight(node), nodeRight(nodeRight(node)));
                    rearruma(nodeLeft(node), nodeLeft(nodeRight(node))) ;
                }
                else if(nodeLeft(node) >= this.TamMax || array[nodeLeft(node)] == null){ // tenho filho direito
                    array[node] = array[nodeRight(node)] ;
                    array[nodeRight(node)] = null ;
                    rearruma(nodeLeft(node), nodeLeft((nodeLeft(node))));
                    rearruma(nodeRight(node), nodeRight(nodeLeft(node)));
                }
            }
            else{ // 2 filhos
                //troca max esq
                int mx = find_max(2*node+1) ;
                array[node] = array[mx] ;
                rearruma(nodeRight(pai(mx)), nodeLeft(mx));
                recursive_rem(mx, array[mx]);
            }
        }
        else if(array[node].compareTo(v) < 0) recursive_rem(nodeRight(node), v) ;
        else if(array[node].compareTo(v) > 0) recursive_rem(nodeLeft(node), v) ;

        if(array[node] == null) return true ;

        //rebalancear usando as rotações
        if(fb(node) == 2){
            if(fb(nodeLeft(node)) < 0) RodarEsqDir(node);
            else RodaDir(node);
        }

        else if(fb(node) == -2){
            if(fb(nodeRight(node)) > 0) RodarDirEsq(node);
            else RodaEsq(node);
        }

        return true ;

    }

}
