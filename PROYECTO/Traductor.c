#include "Pila.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* traducePostFijo(const char* expresion);
char* traducePreFijo(const char* expresion);

int main() {
    char expresion[100];
    char resultado_post[100];
    char resultado_pre[100];
    char continuar;
    
    do {
        printf("\nBienvenido al conversor de notacion infija\n");
        printf("Introduce una expresion infija: ");
        fgets(expresion, sizeof(expresion), stdin);
        expresion[strcspn(expresion, "\n")] = 0; // Remover newline
        
        // Convertir a postfijo
        strcpy(resultado_post, traducePostFijo(expresion));
        printf("Notacion postfija: %s\n", eliminaEspacios(resultado_post));
        
        // Convertir a prefijo
        strcpy(resultado_pre, traducePreFijo(expresion));
        printf("Notacion prefija: %s\n", resultado_pre);
        
        // Evaluar expresión postfija
        printf("Evaluando expresion:\n");
        revisaVariables(resultado_post);
        evaluaExpresion(resultado_post);
        
        printf("\nDesea continuar? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); 
        
    } while(continuar == 's' || continuar == 'S');
    
    return 0;
}

char* traducePostFijo(const char* expresion) {
    Nodo *P = NULL;
    char salida[100];
    int indiceSalida = 0;
    int i = strlen(expresion);
    
    for(int j = 0; j < i; j++) {
        char caracter = expresion[j];
        // Detectar funciones trigonométricas
        if(j + 3 < i && 
          ((expresion[j] == 's' && expresion[j+1] == 'e' && expresion[j+2] == 'n') ||
           (expresion[j] == 'c' && expresion[j+1] == 'o' && expresion[j+2] == 's') ||
           (expresion[j] == 't' && expresion[j+1] == 'a' && expresion[j+2] == 'n'))) {
            
            if(expresion[j] == 's') {
                strcpy(&salida[indiceSalida], "sen ");
                indiceSalida += 4;
            } else if(expresion[j] == 'c') {
                strcpy(&salida[indiceSalida], "cos ");
                indiceSalida += 4;
            } else {
                strcpy(&salida[indiceSalida], "tan ");
                indiceSalida += 4;
            }
            j += 3;
            continue;
        }
        else if(isalnum(caracter) || caracter == '.') {
            // Copiar número completo incluyendo decimales
            while(j < i && (isalnum(expresion[j]) || expresion[j] == '.')) {
                salida[indiceSalida++] = expresion[j];
                j++;
            }
            j--; // Retroceder un carácter
            salida[indiceSalida++] = ' ';
        }
        else if(caracter == '(') {
            P = push(P, caracter);
        }
        else if(caracter == ')') {
            while(P != NULL && P->dato != '(') {
                salida[indiceSalida++] = pop(&P);
                salida[indiceSalida++] = ' '; 
            }
            if(P != NULL) pop(&P);
        }
        else if(!isspace(caracter)) {
            while(P != NULL && prioridad(P->dato) >= prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
                salida[indiceSalida++] = ' '; 
            }
            P = push(P, caracter);
        }
    }
    
    while(P != NULL) {
        char op = pop(&P);
        if(op != '(' && op != ')') {
            salida[indiceSalida++] = op;
            salida[indiceSalida++] = ' '; 
        }
    }
    
    if(indiceSalida > 0 && salida[indiceSalida-1] == ' ') {
        indiceSalida--;
    }
    salida[indiceSalida] = '\0';
    
    return strdup(salida);
}

char* traducePreFijo(const char* expresion) {
    // Detectar funciones trigonométricas
    for(int j = 0; j < strlen(expresion)-2; j++) {
        if((expresion[j] == 's' && expresion[j+1] == 'e' && expresion[j+2] == 'n') ||
           (expresion[j] == 'c' && expresion[j+1] == 'o' && expresion[j+2] == 's') ||
           (expresion[j] == 't' && expresion[j+1] == 'a' && expresion[j+2] == 'n')) {
            return strdup("NO SE PROCESAN FUNCIONES TRIGONOMETRICAS EN NOTACION PREFIJA");
        }
    }

    Nodo *P = NULL;
    char salida[100];
    int indiceSalida = 0;
    int i = strlen(expresion);
    
    for(int j = i-1; j >= 0; j--) {
        char caracter = expresion[j];
        if(isalnum(caracter) || caracter == '.') {
            salida[indiceSalida++] = caracter;
        }
        else if(caracter == ')') {
            P = push(P, caracter);
        }
        else if(caracter == '(') {
            while(P != NULL && P->dato != ')') {
                salida[indiceSalida++] = pop(&P);
            }
            if(P != NULL) pop(&P);
        }
        else if(!isspace(caracter)) {
            while(P != NULL && prioridad(P->dato) > prioridad(caracter)) {
                salida[indiceSalida++] = pop(&P);
            }
            P = push(P, caracter);
        }
    }
    
    while(P != NULL) {
        char op = pop(&P);
        if(op != '(' && op != ')') {
            salida[indiceSalida++] = op;
        }
    }
    salida[indiceSalida] = '\0';
    
    for(int j = 0; j < indiceSalida/2; j++) {
        char temp = salida[j];
        salida[j] = salida[indiceSalida-1-j];
        salida[indiceSalida-1-j] = temp;
    }
    
    return strdup(salida);
}
