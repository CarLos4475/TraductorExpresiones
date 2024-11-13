#include "Pila.h"
#include <stdio.h>
#include <ctype.h> 

void traducePostFijo();
void traducePreFijo();

int main(){
    traducePostFijo();
    printf("\n");
    traducePreFijo();

    return 0;
}

void traducePostFijo(){
    Nodo *P = NULL;
    char caracter;
    printf("Introduce una expresion infija: ");
    
    while((caracter = getchar()) != '\n'){
        if(isalnum(caracter)){  
            printf("%c", caracter);
        }else if(caracter == '('){
            P = push(P, caracter);
        }else if(caracter == ')'){
            while(P->dato != '('){
                printf("%c", pop(&P));
            }
            pop(&P);
        }else{
            while(P != NULL && prioridad(P->dato) >= prioridad(caracter)){
                printf("%c", pop(&P));
            }
            P = push(P, caracter);
        }
    }
    while(P != NULL){
        printf("%c", pop(&P));
    }
}

void traducePreFijo() {
    Nodo *P = NULL;
    char expresion[100];
    char salida[100];
    int i = 0;
    int indiceSalida = 0;
    
    printf("Introduce una expresion infija: ");
    char caracter;
    while((caracter = getchar()) != '\n' && i < 99) {
        expresion[i++] = caracter;
    }
    expresion[i] = '\0';
    
    for(int j = i-1; j >= 0; j--) {
        caracter = expresion[j];
        if(isalnum(caracter)) {
            salida[indiceSalida++] = caracter;
        }
        else if(caracter == ')') {
            P = push(P, caracter);
        }
        else if(caracter == '(') {
            while(P != NULL && P->dato != ')') {
                salida[indiceSalida++] = pop(&P);
            }
            if(P != NULL) {
                pop(&P);
            }
        }
        else { 
            while(P != NULL && prioridad(P->dato) > prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
            }
            P = push(P, caracter);
        }
    }
    while(P != NULL) {
        salida[indiceSalida++] = pop(&P);
    }
    salida[indiceSalida] = '\0';

    for(int j = indiceSalida-1; j >= 0; j--) {
        printf("%c", salida[j]);
    }
    printf("\n");
}
