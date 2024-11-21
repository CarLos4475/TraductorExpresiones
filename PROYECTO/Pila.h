#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Nodo {
    float dato;
    struct Nodo *liga;
} Nodo;

Nodo *push(Nodo *pila, float x){
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->dato = x;
    nuevo->liga = pila;
    return nuevo;
}

float pop(Nodo **pila){
    Nodo *auxiliar = *pila;
    float x = auxiliar->dato;
    *pila = auxiliar->liga;
    free(auxiliar);
    return x;
}

int prioridad(char ch){
    if(ch == '+' || ch == '-'){
        return 1;
    }else if(ch == '*' || ch == '/'){
        return 2;
    }else if(ch == '^'){
        return 3;
    }else{
        return 0;
    }
}

void revisaVariables(char *expresion) {
    char aux[100];
    float valorAux[100];
    int contador = 0, esta;
    char temporal[20];
    char nuevaExp[1000] = "";
    int nuevoIndice = 0;
    
    for (int i = 0; i < strlen(expresion); i++) {
        if (isalpha(expresion[i])) {
            esta = 0;
            for (int j = 0; j < contador; j++) {
                if (aux[j] == expresion[i]) {
                    sprintf(temporal, "%f", valorAux[j]);
                    strcat(nuevaExp, temporal);
                    nuevoIndice += strlen(temporal);
                    esta = 1;
                    break;
                }
            }
            if (!esta) {
                aux[contador] = expresion[i];
                printf("Valor %c: ", expresion[i]);
                scanf("%f", &valorAux[contador]);
                sprintf(temporal, "%f", valorAux[contador]);
                strcat(nuevaExp, temporal);
                nuevoIndice += strlen(temporal);
                contador++;
            }
        } else {
            nuevaExp[nuevoIndice++] = expresion[i];
            nuevaExp[nuevoIndice] = '\0';
        }
    }
    strcpy(expresion, nuevaExp);
}

void evaluaExpresion(char *expresion){
    Nodo *pila = NULL; 
    float resultado = 0; 
    float numero; 
    char *ptrFin; // Puntero al final del número
    
    for (int i = 0; i < strlen(expresion); ) {
        if (isdigit(expresion[i]) || expresion[i] == '.') { // Verifica si es un número
            numero = strtof(&expresion[i], &ptrFin); // Convierte la cadena a un número
            i = ptrFin - expresion; // Actualiza el índice
            pila = push(pila, numero); // Agrega el número a la pila
        } else if (expresion[i] != ' ') { // Verifica si es un operador
            float operando2 = pop(&pila); // Obtiene el segundo operando
            float operando1 = pop(&pila); // Obtiene el primer operando
            switch (expresion[i]) { // Realiza la operación correspondiente
                case '+':
                    resultado = operando1 + operando2;
                    break;
                case '-':
                    resultado = operando1 - operando2;
                    break;
                case '*':
                    resultado = operando1 * operando2;
                    break;
                case '/':
                    resultado = operando1 / operando2;
                    break;
                case '^':
                    resultado = 1;
                    for(int j = 0; j < (int)operando2; j++) {
                        resultado *= operando1;
                    }
                    break;
            }
            pila = push(pila, resultado); // Agrega el resultado a la pila
            i++;
        } else {
            i++; // Ignora los espacios
        }
    }
    printf("Resultado: %f\n", (float)pop(&pila)); // Imprime el resultado
}
