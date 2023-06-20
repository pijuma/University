#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
// M - 65 -  90 
// m - 97 

char tol(char a){
    if(a >= 97 && a <= 122) return a ; 
    if(a >= 65 && a <= 90) return ((a-'a')+32)+'a' ; 
    return a ; 
}

int main(){

    char *p, o ; 
    p = NULL ; 

    int at = 0 ; 

    while(scanf("%c", &o) != EOF){
        p = (char *) realloc(p, (at + 1)*sizeof(char)) ;
        p[at] = tol(o) ; 
        at++ ; 
    }

    p = (char *) realloc(p, (at + 1)*sizeof(char)) ;
    p[at] = '\0' ;

    int freq[27] ; 
    for(char i = 'a' ; i <= 'z' ; i++) freq[i-'a'] = 0 ; 
    for(int i = 0 ; i < at ; i++) freq[p[i]-'a']++ ; 
    for(char i = 'a' ; i <= 'z' ; i++) if(freq[i-'a'] != 0) printf("%c: %d\n", i, freq[i-'a']) ;
    
}
