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
        if(isalnum(caracter) || caracter == '.') {
            // Leer todos los digitos consecutivos
            while(j < i && (isalnum(expresion[j]) || expresion[j] == '.')) {
                salida[indiceSalida++] = expresion[j];
                j++;
            }
            // Agregar espacio despues de cada operando
            salida[indiceSalida++] = ' ';
            j--; // Ajustar j ya que se avanzo uno de mas
        }
        else if(caracter == '(') {
            P = push(P, caracter);
        }
        else if(caracter == ')') {
            while(P != NULL && P->dato != '(') {
                salida[indiceSalida++] = pop(&P);
                salida[indiceSalida++] = ' '; // Agregar espacio despues de cada operador
            }
            if(P != NULL) {
                pop(&P);
            }
        }
        else if(!isspace(caracter)) { // Ignorar espacios
            while(P != NULL && prioridad(P->dato) >= prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
                salida[indiceSalida++] = ' '; // Agregar espacio despues de cada operador
            }
            P = push(P, caracter);
        }
    }
    
    while(P != NULL) {  // Agregar los operadores restantes
        salida[indiceSalida++] = pop(&P);
        salida[indiceSalida++] = ' ';
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
        if(isalnum(caracter) || caracter == '.') {
            // Leer todos los digitos consecutivos
            int start = j;
            while(j >= 0 && (isalnum(expresion[j]) || expresion[j] == '.')) {
                j--;
            }
            j++; // Ajustar j ya que se decremento uno de mas
            
            for(int k = j; k <= start; k++) {
                salida[indiceSalida++] = expresion[k]; // Agregar operandos
            }
            salida[indiceSalida++] = ' '; // Agregar espacio despues de cada operando
        }
        else if(caracter == ')') {
            P = push(P, caracter); // Agregar parentesis a la pila
        }
        else if(caracter == '(') { 
            while(P != NULL && P->dato != ')') { 
                salida[indiceSalida++] = pop(&P);
                salida[indiceSalida++] = ' '; // Agregar espacio despues de cada operador
            }
            if(P != NULL) {
                pop(&P); 
            }
        }
        else if(!isspace(caracter)) {  // Ignorar espacios
            while(P != NULL && prioridad(P->dato) >= prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
                salida[indiceSalida++] = ' '; 
            }
            P = push(P, caracter); 
        }
    }
    
    while(P != NULL) {
        salida[indiceSalida++] = pop(&P);
        salida[indiceSalida++] = ' ';
    }
    salida[indiceSalida] = '\0';

    // Voltear la cadena
    char temp[100];
    strcpy(temp, salida);
    for(int j = 0; j < indiceSalida; j++) {
        salida[j] = temp[indiceSalida - 1 - j];
    }
    salida[indiceSalida] = '\0';

    return strdup(salida);
}
