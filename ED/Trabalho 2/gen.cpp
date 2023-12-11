#include<bits/stdc++.h>
using namespace std ; 

int main(){

	srand(time(NULL)) ; 

	int n = 100000 ; 
	int m = 100000 ;

	cout << n << endl ; 
	cout << n << endl ; 

	int lst = 0 ; 

	for(int i = 1 ; i <= n ; i++){
		int a = (rand()%m) + 1 ;
		cout << a << " " ;  
		lst = a ; 
	}

	cout << "\n" ;  

	for(int i = 1 ; i <= n ; i++){
		int a = (rand()%m) + 1 ;
		cout << a << " " ;  
	}
	
	cout << "\n" ; 

	cout << 4 << " " << lst << "\n" ;

}