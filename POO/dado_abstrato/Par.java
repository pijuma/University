import java.util.Scanner ;
public class Par<T1, T2>{

    private T1 ff ;
    private T2 ss ;

    public Par(T1 a, T2 b){
        ff = a  ;
        ss = b ;
    }

    T1 getf(){ return ff ; }
    T2 gets(){return ss ; }

    public String toString(){
        return "(" + ff + "," + ss + ")" ;
    }

}
