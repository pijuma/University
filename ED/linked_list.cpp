#include<bits/stdc++.h>
using namespace std ; 

struct Node{
    
    int data ; 
    Node *next ; 

    Node(int val){
        data = val ; 
        next = NULL ; 
    }

} ;

class LinkedList{

private:

    Node *head ; 
    Node *end ; 

public: 

    LinkedList(){head = NULL ; end = NULL ; }

    void insert(int val){//inserir no final 
        
        Node *neww = new Node(val) ; 

        if(end == NULL){
            head = end = neww ; return ;  
        }

        end->next = neww ; 
        end = neww ; 

    }

    void rem(int val){ //remover um elemento 
        
        if(head == NULL) return ; 
        Node *at = head ; 

        if(head->data == val){//mudar o inicio 
            auto temp = head ; 
            head = head->next ; 
            if(temp == end) end = head ; 
            delete temp ; 
            return ; 
        }

        Node *prev = NULL ; 

        while(at != NULL){
            if(at->data == val){//achei
                Node *temp = at ; 
                if(end == at){
                    prev->next = NULL ; 
                    end = prev ; 
                }
                else{
                    if(prev != NULL) prev->next = at->next ; 
                    else head = at->next ; 
                }
                delete at ; 
                break ; 
            }
            prev = at ; 
            at = at->next ; 
        }

    }

    void show(){//imprimir tudo 
        Node *at = head ; 
        while(at != NULL){
            cout << at->data << " " ; 
            at = at->next ; 
        }
        cout << "\n" ; 
    }

    //se fizer ~LinkedList o destrutor é chamado automaticamente

    void liberar_mem(){
        Node *temp = head ; 
        while(temp != NULL){
            Node *nxt = temp->next ; 
            delete temp ; 
            temp = nxt ; 
        }
    }

} ;

int main(){

    LinkedList lista ; 

    lista.insert(2) ; 
    lista.insert(4) ; 
    lista.insert(5) ; 
    
    lista.show() ; 

    lista.rem(5) ; 

    lista.show() ; 

}
