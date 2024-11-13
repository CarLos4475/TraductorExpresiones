#include "Pila.h"
#include <stdio.h>
#include <ctype.h> 

void traducePostFijo();
void traducePreFijo();

//PROGRAMA QUE TRADUCE UNA EXPRESION INFIJA A POSTFIJA
int main(){
    traducePostFijo();
    printf("\n");
    traducePreFijo();

    return 0;
}

void traducePostFijo(){
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
}

void traducePreFijo() {
    Nodo *P = NULL;
    char expresion[100];
    char output[100];
    int i = 0;
    int outIndex = 0;
    
    printf("Introduce una expresion infija: ");
    char ch;
    while((ch = getchar()) != '\n' && i < 99) {
        expresion[i++] = ch;
    }
    expresion[i] = '\0';
    
    for(int j = i-1; j >= 0; j--) {
        ch = expresion[j];
        if(isalnum(ch)) { //COMPRUEBA SI ES UNA LETRA O UN NUMERO
            output[outIndex++] = ch;
        }
        else if(ch == ')') {
            P = push(P, ch);
        }
        else if(ch == '(') {
            while(P != NULL && P->dato != ')') {
                output[outIndex++] = pop(&P);
            }
            if(P != NULL) {
                pop(&P);
            }
        }
        else { 
            while(P != NULL && prioridad(P->dato) > prioridad(ch)) {
                output[outIndex++] = pop(&P);
            }
            P = push(P, ch);
        }
    }
    while(P != NULL) {
        output[outIndex++] = pop(&P);
    }
    output[outIndex] = '\0';

    for(int j = outIndex-1; j >= 0; j--) {
        printf("%c", output[j]);
    }
    printf("\n");
}
