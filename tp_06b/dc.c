#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"
#include "strutil.h"
#define RAIZ "sqrt"
#define RAIZ_FINAL_LINEA "sqrt\n"
#define LOG "log"
#define LOG_FINAL_LINEA "log\n"
enum estado {SUMA = 43, RESTA = 45, MULTIPLICACION = 42, DIVISION = 47, POTENCIA = 94, TERNARIO = 63};

bool suma(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 2) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* a = pila_desapilar(pila_operaciones);
        int* b = pila_desapilar(pila_operaciones);
        *resultado = *a + *b;
        pila_apilar(pila_operaciones, resultado);
        free(a);
        free(b);
    } else {
        return false;
    }
    return true;
}

bool resta(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 2) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* a = pila_desapilar(pila_operaciones);
        int* b = pila_desapilar(pila_operaciones);
        *resultado = *a - *b;
        pila_apilar(pila_operaciones, resultado);
        free(a);
        free(b);
    } else {
        return false;
    }
    return true;
}

int calcular_potencia(int base, int exponente) {
    if (exponente == 0) {
        return 1;
    } else {
        int resultado = calcular_potencia(base * base, exponente / 2);
        if (exponente % 2 == 1) {
            resultado = base * resultado;
        }
        return resultado;
    }
}

bool potencia(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 2) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* base = pila_desapilar(pila_operaciones);
        int* exponente = pila_desapilar(pila_operaciones);
        if (*exponente >= 0) {
            *resultado = calcular_potencia(*base, *exponente);
            pila_apilar(pila_operaciones, resultado);
            free(base);
            free(exponente);
        } else {
            free(base);
            free(exponente);
            free(resultado);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

int calcular_raiz(int radicando, int inicio, int fin) {
    if ( inicio > fin) {        
        return inicio - 1;
    }
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

bool raiz(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 1) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* radicando = pila_desapilar(pila_operaciones);
        if (*radicando >= 0) {
            *resultado = calcular_raiz(*radicando, 1, *radicando);
            pila_apilar(pila_operaciones, resultado);
            free(radicando);
        } else {
            free(radicando);
            free(resultado);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool division(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 2) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* dividendo = pila_desapilar(pila_operaciones);
        int* divisor = pila_desapilar(pila_operaciones);
        if (*divisor != 0) {
            *resultado = *dividendo / *divisor;
            pila_apilar(pila_operaciones, resultado);
            free(dividendo);
            free(divisor);
        } else {
            free(dividendo);
            free(divisor);
            free(resultado);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool multiplicacion(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 2) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* multiplicando = pila_desapilar(pila_operaciones);
        int* multipicador = pila_desapilar(pila_operaciones);
        *resultado = *multiplicando * *multipicador;
        pila_apilar(pila_operaciones, resultado);
        free(multiplicando);
        free(multipicador);
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

bool logaritmo(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 2) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* valor = pila_desapilar(pila_operaciones);
        int* base = pila_desapilar(pila_operaciones);
        if (*base > 1) {
            *resultado = calcular_logaritmo(*base, *valor);
            pila_apilar(pila_operaciones, resultado);
            free(valor);
            free(base);
        } else {
            free(valor);
            free(base);
            free(resultado);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool ternario(pila_t* pila_operaciones) {
    if (pila_largo(pila_operaciones) >= 3) {
        int* resultado = malloc(sizeof(int));
        if(resultado == NULL) {
            return false;
        }
        int* comparacion = pila_desapilar(pila_operaciones);
        int* valor_si_verdadero = pila_desapilar(pila_operaciones);
        int* valor_si_falso = pila_desapilar(pila_operaciones);
        *resultado = *comparacion != 0 ? *valor_si_verdadero : *valor_si_falso;
        pila_apilar(pila_operaciones, resultado);
        free(comparacion);
        free(valor_si_verdadero);
        free(valor_si_falso);

    } else {
        return false;
    }
    return true;
}

int dc() {
    pila_t* pila_operaciones = pila_crear();
    if (pila_operaciones == NULL) {
        return 1;
    }
    char* linea = NULL;
    size_t capacidad = 0;
    while (getline(&linea, &capacidad, stdin) != EOF) {
        bool resultado_ok = true;
        char** lista = split(linea, ' ');
        size_t indice_lista = 0;
        while (lista[indice_lista] != NULL && resultado_ok) {
            void* elemento = lista[indice_lista];
            if((atoi((char*)elemento) == 0 && (strcmp((char*)elemento,"0") == 0 || strcmp((char*)elemento,"0\\n") == 0)) || (atoi((char*)elemento) != 0)) {
                int* numero = malloc(sizeof(int));
                if(numero == NULL) {
                    fprintf(stdout, "ERROR\n");
                    return 1;
                }
                *numero = atoi(elemento);
                pila_apilar(pila_operaciones, numero);
            } else if (*(char*)elemento == SUMA) {
                resultado_ok = suma(pila_operaciones);
            } else if (*(char*)elemento == RESTA) {
                resultado_ok = resta(pila_operaciones);
            } else if (*(char*)elemento == POTENCIA) {
                resultado_ok = potencia(pila_operaciones);
            } else if (*(char*)elemento == DIVISION) {
                resultado_ok = division(pila_operaciones);
            } else if (*(char*)elemento == MULTIPLICACION) {
                resultado_ok = multiplicacion(pila_operaciones);
            } else if (*(char*)elemento == TERNARIO) {
                resultado_ok = ternario(pila_operaciones);
            } else if (strcmp((char*)elemento, RAIZ) == 0 || strcmp((char*)elemento, RAIZ_FINAL_LINEA) == 0) {
                resultado_ok = raiz(pila_operaciones);
            } else if (strcmp((char*)elemento, LOG) == 0 || strcmp((char*)elemento, LOG_FINAL_LINEA) == 0) {
                resultado_ok = logaritmo(pila_operaciones);
            } else if (strlen((char*)elemento) > 0 && strcmp((char*)elemento, "\\n") != 0 && strcmp((char*)elemento, "\\n\n") != 0 && strcmp((char*)elemento, "\n") != 0) {
                resultado_ok = false;
            }
            indice_lista++;
        }
        if (pila_largo(pila_operaciones) > 1 || indice_lista == 1) {
            resultado_ok = false;
            while (pila_largo(pila_operaciones) > 1) {
                int* valor = pila_desapilar(pila_operaciones);
                free(valor);
            }
        }
        int* valor = pila_desapilar(pila_operaciones);
        if (resultado_ok) {
            fprintf(stdout, "%i\n", *valor);
        } else {
            fprintf(stdout, "ERROR\n");
        }
        free(valor);
        free_strv(lista);
    }
    pila_destruir(pila_operaciones);
    free(linea);
    return 0;
}

int main() {
    dc();
    return 0;
}
