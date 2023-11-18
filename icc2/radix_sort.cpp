#include<bits/stdc++.h>
using namespace std ; 

const int maxn = 1e5 + 5 ; 

int n ; 
int v[maxn] ; 

int dig(int a, int k){

    int ct = 0 ; 

    while(a){
        ct++ ; 
        int at = a%10 ; 
        if(ct == k) return at ; 
        a/= 10 ; 
    }

    return 0 ; 

}

void radix_sort(){

    queue<int> fila[11] ; 

    vector<int> vec ; 

    for(int i = 1 ; i <= n ; i++) vec.push_back(v[i]) ;

    int mx = 0 ; 

    for(int i = 1 ; i <= n ; i++){
        int ct = 1 ; int x = v[i] ; 
        while(x){
            ct++ ; x /= 10 ; 
        }
        mx = max(mx, ct)  ;
    }

    cout << mx << "\n" ; 

    for(int k = 1 ; k <= mx ; k++){
        for(auto a : vec){
            fila[dig(a, k)].push(a) ; 
        }
        vec.clear() ;
        for(int i = 0 ; i <= 9 ; i++){
            while(fila[i].size()){
                int at = fila[i].front() ; fila[i].pop() ; 
                vec.push_back(at) ;
            }
        }
        for(int i = 1 ; i <= n ; i++) v[i] = vec[i-1] ; 
    }

}

int main(){

    cin >> n ; 

    for(int i = 1 ; i <= n ; i++) cin >> v[i] ; 

    radix_sort() ;

    for(int i = 1 ; i <= n ; i++) cout << v[i] << " " ; 
    cout << "\n" ; 

}
