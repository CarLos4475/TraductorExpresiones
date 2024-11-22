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
    if(ch == 's' || ch == 'c' || ch == 't') { 
        return 4;
    }else if(ch == '+' || ch == '-'){
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
        // Detectar funciones trigonométricas
        if (i + 2 < strlen(expresion) && 
           ((expresion[i] == 's' && expresion[i+1] == 'e' && expresion[i+2] == 'n') ||
            (expresion[i] == 'c' && expresion[i+1] == 'o' && expresion[i+2] == 's') ||
            (expresion[i] == 't' && expresion[i+1] == 'a' && expresion[i+2] == 'n'))) {
            
            if (expresion[i] == 's') {
                strcat(nuevaExp, "sen");
                nuevoIndice += 3;
            } else if (expresion[i] == 'c') {
                strcat(nuevaExp, "cos");
                nuevoIndice += 3;
            } else {
                strcat(nuevaExp, "tan");
                nuevoIndice += 3;
            }
            i += 2; // Saltar resto de la función
            continue;
        }
        // Proceso normal para variables
        else if (isalpha(expresion[i])) {
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

void evaluaExpresion(char *expresion) {
    Nodo *pila = NULL;
    float resultado = 0;
    char *token = strtok(expresion, " ");
    
    while(token != NULL) {
        // Si es función trigonométrica
        if(strncmp(token, "sen", 3) == 0 || 
           strncmp(token, "cos", 3) == 0 || 
           strncmp(token, "tan", 3) == 0) {
            
            char funcion[4];
            strncpy(funcion, token, 3);
            funcion[3] = '\0';
            
            token = strtok(NULL, " ");
            if(token == NULL) {
                printf("Error: Falta argumento para función trigonométrica\n");
                return;
            }
            
            float angulo = atof(token);
            
            if(strcmp(funcion, "sen") == 0) {
                resultado = sin(angulo);
            } else if(strcmp(funcion, "cos") == 0) {
                resultado = cos(angulo);
            } else {  // tan
                resultado = tan(angulo);
            }
            pila = push(pila, resultado);
        }
        else if(isdigit(token[0]) || token[0] == '.' || (token[0] == '-' && isdigit(token[1]))) {
            float num = atof(token);
            pila = push(pila, num);
        }
        else if(token[0] == '+' || token[0] == '-' || token[0] == '*' || 
                token[0] == '/' || token[0] == '^') {
            if(pila == NULL || pila->liga == NULL) {
                printf("Error: Faltan operandos\n");
                return;
            }
            float operando2 = pop(&pila);
            float operando1 = pop(&pila);
            
            switch(token[0]) {
                case '+': resultado = operando1 + operando2; break;
                case '-': resultado = operando1 - operando2; break;
                case '*': resultado = operando1 * operando2; break;
                case '/': 
                    if(operando2 != 0) {
                        resultado = operando1 / operando2;
                    } else {
                        printf("Error: División por cero\n");
                        return;
                    }
                    break;
                case '^': resultado = pow(operando1, operando2); break;
            }
            pila = push(pila, resultado);
        }
        token = strtok(NULL, " ");
    }
    
    if(pila != NULL) {
        resultado = pop(&pila);
        if(pila != NULL) {
            printf("Error: Sobran operandos\n");
            return;
        }
        printf("\nResultado: %f\n", resultado);
    }
}

char* eliminaEspacios(const char *expresion) {
    static char resultado[100];
    char *aux = resultado;
    
    while(*expresion) {
        if(!isspace(*expresion)) {
            *aux++ = *expresion;
        }
        expresion++;
    }
    *aux = '\0';
    
    return resultado;
}
