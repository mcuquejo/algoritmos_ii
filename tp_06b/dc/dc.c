#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "strutil.h"
#define RAIZ "sqrt"
#define RAIZ_FINAL_LINEA "sqrt\n"
#define LOG "log"
#define LOG_FINAL_LINEA "log\n"
enum estado {SUMA = 43, RESTA = 45, MULTIPLICACION = 42, DIVISION = 47, POTENCIA = 94, TERNARIO = 63};

bool sumar(lista_t* buffer){
    printf("ESTO ES UNA SUMA\n");
    if (lista_largo(buffer) >= 2) {
        char* p;
        p = malloc(sizeof(int)); 
        if(p == NULL) { 
            return false;            
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        int resultado = a + b;
        sprintf(p,"%d",resultado);
        printf("resultado suma = %i\n", atoi(p));
        lista_insertar_primero(buffer, p);
    } else {
        fprintf(stdout, "ERROR INTERNO SUMA\n");
        return false;
    }
    return true;
}

bool restar(lista_t* buffer){
    printf("ESTO ES UNA RESTA\n");
    if (lista_largo(buffer) >= 2) {
        char* p;
        p = malloc(sizeof(int)); 
        if(p == NULL) { 
            return false;            
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        int resultado = a - b;
        printf("el resultado de la resta (parcial), sería %d\n",resultado);
        sprintf(p,"%d",resultado);
        printf("resultado resta = %i\n", atoi(p));
        lista_insertar_primero(buffer, p);
    } else {
        fprintf(stdout, "ERROR INTERNO RESTA\n");
        return false;
    }
    return true;
}

int potencia(int base, int e) {
    printf("base: %d, exponente: %d\n", base, e);
    if (e == 0) {
        return 1;
    } else {
        int resultado = potencia(base*base, e/2);
        if (e % 2 == 1) {
            resultado = base * resultado;
        }
        return resultado;
    }
}

bool elevar(lista_t* buffer) {
    printf("ESTO ES UNA POTENCIA\n");
    if (lista_largo(buffer) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        if (a > 0) {
        int resultado = potencia(a, b);
        sprintf(p,"%d",resultado);
        printf("resultado potencia = %i\n", atoi(p));
        lista_insertar_primero(buffer, p);
        } else {
            fprintf(stdout, "ERROR INTERNO POTENCIA\n");
            return false;
        }
    } else {
        fprintf(stdout, "ERROR INTERNO POTENCIA\n");
        return false;
    }
    return true;
}

int raiz(int radicando, int inicio, int fin, int cont) {
    if ( inicio > fin) return 0;
    int medio = (inicio + fin) / 2;
    printf("medio = %i\n", medio);
    if (medio * medio == radicando || (medio * medio) + 1 == radicando) {
        printf("cantidad de ejecuciones: %i\n", cont);
        return medio;
    }    
    if (medio * medio > radicando){
        return raiz(radicando, inicio, medio - 1, cont + 1);
    } else {
        return raiz(radicando, medio + 1, fin, cont + 1);
    }
}

bool radicar(lista_t* buffer) {
    printf("ESTO ES UNA RAIZ\n");
    if (lista_largo(buffer) >= 1) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        int a = atoi(lista_borrar_primero(buffer));
        if (a > 0) {
        int resultado = raiz(a, 1, a,0);
        sprintf(p,"%d",resultado);
        printf("resultado raiz = %i\n", atoi(p));
        lista_insertar_primero(buffer, p);
        } else {
            fprintf(stdout, "ERROR INTERNO RAIZ\n");
            return false;
        }
    } else {
        fprintf(stdout, "ERROR INTERNO RAIZ\n");
        return false;
    }
    return true;
}

bool dividir(lista_t* buffer) {
    printf("ESTO ES UNA DIVISION\n");
    if (lista_largo(buffer) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        if (b > 0) {
            int resultado = a / b;
            sprintf(p,"%d",resultado);
            printf("resultado division = %i\n", atoi(p));
            lista_insertar_primero(buffer, p);
        } else {
            fprintf(stdout, "ERROR INTERNO DIVISION\n");
            return false;
        }
    } else {
        fprintf(stdout, "ERROR INTERNO DIVISION\n");
        return false;
    }
    return true;
}

bool multiplicar(lista_t* buffer) {
    printf("ESTO ES UNA MULTIPLICACION\n");
    if (lista_largo(buffer) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        int resultado = a * b;
        sprintf(p,"%d",resultado);
        printf("resultado multiplicacion = %i\n", atoi(p));
        lista_insertar_primero(buffer, p);
    } else {
        fprintf(stdout, "ERROR INTERNO MULTIPLICACION\n");
        return false;
    }
    return true;
}

int calcular_logaritmo(int base, int valor) {
    printf("valor = %i, base = %i\n", valor, base);
    if (valor == 1 || valor < base) {
        return 0;
    }
    return calcular_logaritmo(base, valor / base) + 1;
}

bool logaritmo(lista_t* buffer) {
    printf("ESTO ES UNA LOGARITMO\n");
    if (lista_largo(buffer) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        printf("a = %i, b = %i\n", a, b);
        if (b > 1) {
            int resultado = calcular_logaritmo(b,a);
            sprintf(p,"%d",resultado);
            printf("resultado logaritmo = %i\n", atoi(p));
            lista_insertar_primero(buffer, p);
        } else {
            fprintf(stdout, "ERROR INTERNO LOGARITMO\n");
            return false;
        }
    } else {
        fprintf(stdout, "ERROR INTERNO LOGARITMO\n");
        return false;
    }
    return true;
}

bool ternario(lista_t* buffer) {
    printf("ESTO ES UN TERNARIO\n");
    if (lista_largo(buffer) >= 3) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        int a = atoi(lista_borrar_primero(buffer));
        int b = atoi(lista_borrar_primero(buffer));
        int c = atoi(lista_borrar_primero(buffer));
        int resultado = a != 0 ? b : c;
        sprintf(p,"%d",resultado);
        printf("resultado ternario = %i\n", atoi(p));
        lista_insertar_primero(buffer, p);
    } else {
        fprintf(stdout, "ERROR INTERNO TERNARIO\n");
        return false;
    }
    return true;
}

int dc() {
    lista_t* buffer = lista_crear();
    if (buffer == NULL) {
        fprintf(stdout, "Falló la creación del buffer\n");
        return 1;
    }    
    char* linea = NULL;
    size_t capacidad = 0;
    while (getline(&linea, &capacidad, stdin) != EOF) {
        char** lista = split(linea, ' ');
        size_t indice_lista = 0;
        bool resultado_ok = true;
        while (lista[indice_lista] != NULL && resultado_ok) {
            void* elemento = lista[indice_lista];
            if((atoi((char*)elemento) == 0 && strcmp((char*)elemento,"0") == 0) || (atoi((char*)elemento) != 0)) {
                lista_insertar_primero(buffer, lista[indice_lista]);
                printf("llego a insertar. El largo de la lista es de %zu\n", lista_largo(buffer));
            } else if (*(char*)elemento == SUMA) {
                resultado_ok = sumar(buffer);
            } else if (*(char*)elemento == RESTA) {
                resultado_ok = restar(buffer);
            } else if (*(char*)elemento == POTENCIA) {
                resultado_ok = elevar(buffer);
            } else if (*(char*)elemento == DIVISION) {
                resultado_ok = dividir(buffer);
            } else if (*(char*)elemento == MULTIPLICACION) {
                resultado_ok = multiplicar(buffer);
            } else if (*(char*)elemento == TERNARIO) {
                resultado_ok = ternario(buffer);
            } else if (strcmp((char*)elemento, RAIZ) == 0 || strcmp((char*)elemento, RAIZ_FINAL_LINEA) == 0) {
                resultado_ok = radicar(buffer);
            } else if (strcmp((char*)elemento, LOG) == 0 || strcmp((char*)elemento, LOG_FINAL_LINEA) == 0) {
                resultado_ok = logaritmo(buffer);
            } else {
                fprintf(stdout, "ERROR PORQUE NO COINCIDIO NADA\n");
                return 1;
            }
            
            fprintf(stdout, "elemento: %s\n", (char*)elemento);
            indice_lista++;
        }
        if (resultado_ok) {
            fprintf(stdout, "esto es lo que me devuelve la salida: %d\n", atoi(lista_borrar_primero(buffer)));            
        } else {
            fprintf(stdout, "ERROR\n");
        }
    }
    lista_destruir(buffer, free);
    free(linea);
    return 0;
}

int main() {
    printf("INICIA EL PROCESO\n\n");
    dc();
    return 0;
}
