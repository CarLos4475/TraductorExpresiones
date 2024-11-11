#include "Pila.h"
#include <stdio.h>
#include <ctype.h> 

//PROGRAMA QUE TRADUCE UNA EXPRESION INFIJA A POSTFIJA
int main(){
    Nodo *P = NULL;
    char ch;
    printf("Introduce una expresion infija: ");

    while((ch = getchar()) != '\n'){
        if(isalnum(ch)){  //COMPRUEBA SI ES UNA LETRA O UN NUMERO
            printf("%c", ch);
        }else if(ch == '('){
            P = push(P, ch);
        }else if(ch == ')'){
            while(P->dato != '('){
                printf("%c", pop(&P));
            }
            pop(&P);
        }else{
            while(P != NULL && prioridad(P->dato) >= prioridad(ch)){
                printf("%c", pop(&P));
            }
            P = push(P, ch);
        }
    }
    while(P != NULL){
        printf("%c", pop(&P));
    }
    return 0;
}