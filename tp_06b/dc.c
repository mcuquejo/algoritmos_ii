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

bool suma(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 2) {
        char* p;
        p = malloc(sizeof(int)); 
        if(p == NULL) { 
            return false;            
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        int resultado = atoi(a) + atoi(b);
        sprintf(p,"%d",resultado);
        lista_insertar_primero(lista_operaciones, p);
        free(a);
        free(b);
    } else {
        return false;
    }
    return true;
}

bool resta(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 2) {
        char* p;
        p = malloc(sizeof(int)); 
        if(p == NULL) { 
            return false;            
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        int resultado = atoi(a) - atoi(b);
        sprintf(p,"%d",resultado);
        lista_insertar_primero(lista_operaciones, p);
        free(a);
        free(b);
    } else {
        return false;
    }
    return true;
}

int calcular_potencia(int base, int e) {
    if (e == 0) {
        return 1;
    } else {
        int resultado = calcular_potencia(base * base, e / 2);
        if (e % 2 == 1) {
            resultado = base * resultado;
        }
        return resultado;
    }
}

bool potencia(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        if (atoi(a) > 0) {
        int resultado = calcular_potencia(atoi(a), atoi(b));
        sprintf(p,"%d",resultado);
        lista_insertar_primero(lista_operaciones, p);
        free(a);
        free(b);
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

int calcular_raiz(int radicando, int inicio, int fin) {
    if ( inicio > fin) return 0;
    int medio = (inicio + fin) / 2;
    if (medio * medio == radicando || (medio * medio) + 1 == radicando) {
        return medio;
    }    
    if (medio * medio > radicando) {
        return calcular_raiz(radicando, inicio, medio - 1);
    } else {
        return calcular_raiz(radicando, medio + 1, fin);
    }
}

bool raiz(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 1) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        void* a = lista_borrar_primero(lista_operaciones);
        if (atoi(a) > 0) {
        int resultado = calcular_raiz(atoi(a), 1, atoi(a));
        sprintf(p,"%d",resultado);
        lista_insertar_primero(lista_operaciones, p);
        free(a);
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool division(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        if (atoi(b) > 0) {
            int resultado = atoi(a) / atoi(b);
            sprintf(p,"%d",resultado);
            lista_insertar_primero(lista_operaciones, p);
            free(a);
            free(b);
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool multiplicacion(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        int resultado = atoi(a) * atoi(b);
        sprintf(p,"%d",resultado);
        lista_insertar_primero(lista_operaciones, p);
        free(a);
        free(b);
    } else {
        return false;
    }
    return true;
}

int calcular_logaritmo(int base, int valor) {
    if (valor == 1 || valor < base) {
        return 0;
    }
    return calcular_logaritmo(base, valor / base) + 1;
}

bool logaritmo(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 2) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        if (atoi(b) > 1) {
            int resultado = calcular_logaritmo(atoi(b), atoi(a));
            sprintf(p,"%d",resultado);
            lista_insertar_primero(lista_operaciones, p);
            free(a);
            free(b);
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool ternario(lista_t* lista_operaciones) {
    if (lista_largo(lista_operaciones) >= 3) {
        char* p;
        p = malloc(sizeof(int));
        if(p == NULL) {
            return false;
        }
        void* a = lista_borrar_primero(lista_operaciones);
        void* b = lista_borrar_primero(lista_operaciones);
        void* c = lista_borrar_primero(lista_operaciones);
        int resultado = atoi(a) != 0 ? atoi(b) : atoi(c);
        sprintf(p,"%d",resultado);
        lista_insertar_primero(lista_operaciones, p);
        free(a);
        free(b);
        free(c);
            
    } else {
        return false;
    }
    return true;
}

int dc() {
    lista_t* lista_operaciones = lista_crear();
    if (lista_operaciones == NULL) {
        return 1;
    }    
    char* linea = NULL;
    size_t capacidad = 0;
    while (getline(&linea, &capacidad, stdin) != EOF) {
        char** lista = split(linea, ' ');
        size_t indice_lista = 0;
        bool resultado_ok = true;
        while (lista[indice_lista] != NULL) {
            void* elemento = lista[indice_lista];
            if((atoi((char*)elemento) == 0 && strcmp((char*)elemento,"0") == 0) || (atoi((char*)elemento) != 0)) {
                lista_insertar_primero(lista_operaciones, lista[indice_lista]);
            } else if (*(char*)elemento == SUMA) {
                resultado_ok = suma(lista_operaciones);                
            } else if (*(char*)elemento == RESTA) {
                resultado_ok = resta(lista_operaciones);                
            } else if (*(char*)elemento == POTENCIA) {
                resultado_ok = potencia(lista_operaciones);                
            } else if (*(char*)elemento == DIVISION) {
                resultado_ok = division(lista_operaciones);
            } else if (*(char*)elemento == MULTIPLICACION) {
                resultado_ok = multiplicacion(lista_operaciones);
            } else if (*(char*)elemento == TERNARIO) {
                resultado_ok = ternario(lista_operaciones);
            } else if (strcmp((char*)elemento, RAIZ) == 0 || strcmp((char*)elemento, RAIZ_FINAL_LINEA) == 0) {
                resultado_ok = raiz(lista_operaciones);
            } else if (strcmp((char*)elemento, LOG) == 0 || strcmp((char*)elemento, LOG_FINAL_LINEA) == 0) {
                resultado_ok = logaritmo(lista_operaciones);
            } else {
                resultado_ok = false;
            }
            indice_lista++;
            free(elemento);
        }        
        if (resultado_ok) {
            void* valor = lista_borrar_primero(lista_operaciones);
            fprintf(stdout, "%d\n", atoi(valor));            
            free(valor);
        } else {
            fprintf(stdout, "ERROR\n");
        }
        free(lista);
    }
    lista_destruir(lista_operaciones, free);
    free(linea);
    return 0;
}

int main() {
    dc();
    return 0;
}
