import java.util.Objects;
import java.util.Scanner ;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in) ;
        int n = 20 ;
        //criar os objetos, cada arvore de um tipo
        ArvBal balanced = new ArvBal(n) ;
        Binaria binaria = new Binaria(n) ;
        AVL avl = new AVL(n) ;
        boolean ok=true;
        while(scanner.hasNextLine()) {
            String at;
            at = scanner.nextLine();
            String[] vec = at.split(" ");
            //ler as inserções e remoções
            switch (vec[0]) {

                case "i":
                    balanced.insert(vec[1]);
                    binaria.insert(vec[1]);
                    avl.insert(vec[1]);
                    break;
                case "d":
                    balanced.remove(vec[1]);
                    binaria.remove(vec[1]);
                    avl.remove(vec[1]) ;
                    break;
            }
        }
        //imprimir as arvores finais de cada tipo
        //usando o metotodo ToString implementado
        System.out.println(binaria.ToString());
        System.out.println();
        System.out.println(balanced.ToString());
        System.out.println();
        System.out.println(avl.ToString());
        System.out.println();
        scanner.close() ;
    }
}
