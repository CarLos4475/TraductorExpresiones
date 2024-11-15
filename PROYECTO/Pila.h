#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

void revisaVariables(char *exp){
    char aux[100];
    int auxVal[100];
    int count = 0,is;
    for (int i = 0; i < strlen(exp); i++) {
        if (isalpha(exp[i])) {
            for (int j = 0; j < count; j++) {
                if (aux[j] == exp[i]) {
                    exp[i] = auxVal[j];
                    is = 1;
                }
            }
            if(!is){
                aux[count] = exp[i];
                printf("Valor %c: ", exp[i]);
                scanf(" %c", &exp[i]);
                auxVal[count] = exp[i];
                count++;
            }
        }
    }
}

void evaluaExpresion(char *exp){
    Nodo *P = NULL;
    int resultado = 0;
    for (int i = 0; i < strlen(exp); i++) {
        if (isdigit(exp[i])) {
            P = push(P, exp[i] - '0');
        }else{
            int op2 = pop(&P);
            int op1 = pop(&P);
            switch (exp[i]) {
                case '+':
                    resultado = op1 + op2;
                    break;
                case '-':
                    resultado = op1 - op2;
                    break;
                case '*':
                    resultado = op1 * op2;
                    break;
                case '/':
                    resultado = op1 / op2;
                    break;
                case '^':
                    resultado = 1;
                    for(int j = 0; j < op2; j++) {
                        resultado *= op1;
                    }
                    break;
            }
            P = push(P, resultado);
        }
    }
    printf("Resultado: %d\n", pop(&P));
}

