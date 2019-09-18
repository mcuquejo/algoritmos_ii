#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;

struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};

nodo_t* crear_nodo(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

cola_t* cola_crear(void){    
    cola_t* cola = malloc(sizeof(cola_t));
    if (!cola) return NULL;
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
    void* elem;
    while (!cola_esta_vacia(cola)){
        elem = cola_desencolar(cola);
        if(destruir_dato != NULL) destruir_dato(elem);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return (cola->primero == NULL);
}

bool cola_encolar(cola_t *cola, void* valor){
    if (cola_esta_vacia(cola)){
        cola->ultimo = crear_nodo(valor);
        if (!cola->ultimo) return false;
        cola->primero = cola->ultimo;
    } else {
        nodo_t* nodo_aux = cola->ultimo;
        cola->ultimo = crear_nodo(valor);
        if (!cola->ultimo) return false;
        nodo_aux->proximo = cola->ultimo;
    }
    return true;
}

void* cola_ver_primero(const cola_t *cola){
    return (cola_esta_vacia(cola))? NULL : cola->primero->dato;
}

void* cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)) return NULL;
    nodo_t* nodo_aux = cola->primero;    
    void* dato_aux = nodo_aux->dato;
    cola->primero = cola->primero->proximo;
    free(nodo_aux);
    return dato_aux;
}
