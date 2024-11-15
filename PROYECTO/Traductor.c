#include "Pila.h"
#include <stdio.h>
#include <ctype.h> 
#include <string.h>

char* traducePostFijo();
char* traducePreFijo();

int main(){
    char hola[100];
    //traducePostFijo();
    printf("\n");
    //traducePreFijo();

    strcpy(hola, traducePostFijo());

    printf("lon: %lu\n",strlen(hola));

    for (int i = 0; i < strlen(hola); i++){
        printf("%c", hola[i]);
    }

    printf("\n");
    revisaVariables(hola);

    for (int i = 0; i < strlen(hola); i++){
        printf("%c", hola[i]);
    }
    printf("\n\n");
    evaluaExpresion(hola);

    return 0;
}

char* traducePostFijo() {
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
    
    for(int j = 0; j < i; j++) {
        caracter = expresion[j];
        if(isalnum(caracter)) {
            salida[indiceSalida++] = caracter;
        }
        else if(caracter == '(') {
            P = push(P, caracter);
        }
        else if(caracter == ')') {
            while(P != NULL && P->dato != '(') {
                salida[indiceSalida++] = pop(&P);
            }
            if(P != NULL) {
                pop(&P);
            }
        }
        else {
            while(P != NULL && prioridad(P->dato) >= prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
            }
            P = push(P, caracter);
        }
    }
    
    while(P != NULL) {
        salida[indiceSalida++] = pop(&P);
    }
    salida[indiceSalida] = '\0';
    
    return strdup(salida);
}

char* traducePreFijo() {
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
    
    // Process from right to left
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
            while(P != NULL && prioridad(P->dato) >= prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
            }
            P = push(P, caracter);
        }
    }
    
    while(P != NULL) {
        salida[indiceSalida++] = pop(&P);
    }
    salida[indiceSalida] = '\0';

    // Reverse the string to get prefix notation
    char temp[100];
    strcpy(temp, salida);
    for(int j = 0; j < indiceSalida; j++) {
        salida[j] = temp[indiceSalida - 1 - j];
    }
    salida[indiceSalida] = '\0';

    return strdup(salida);
}
