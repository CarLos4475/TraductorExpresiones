#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *Liga;
} Nodo;

Nodo *push(Nodo *P, int x){
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->dato = x;
    nuevo->Liga = P;
    return nuevo;
}

int pop(Nodo **P){
    Nodo *aux = *P;
    int x = aux->dato;
    *P = aux->Liga;
    free(aux);
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

