#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear(void);
bool lista_esta_vacia(const lista_t *lista);
bool lista_insertar_primero(lista_t *lista, void *dato);
bool lista_insertar_ultimo(lista_t *lista, void *dato);
void *lista_borrar_primero(lista_t *lista);
void *lista_ver_primero(const lista_t *lista);
void *lista_ver_ultimo(const lista_t* lista);
size_t lista_largo(const lista_t *lista);
void lista_destruir(lista_t *lista, void destruir_dato(void *));


typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;

typedef struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
} lista_t;

nodo_t* crear_nodo(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return NULL;        
    }
    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

lista_t* lista_crear(void) {    
    lista_t* cola = malloc(sizeof(lista_t));
    if (!lista) {
        return NULL;
    }
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}


void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
    void* elem;
    while (!lista_esta_vacia(lista)) {
        elem = lista_borrar_primero(lista);
        if(destruir_dato != NULL) {
            destruir_dato(elem);
        }
    }
    free(lista);
}

bool cola_esta_vacia(const cola_t *cola) {
    return (cola->primero == NULL);
}

bool cola_encolar(cola_t *cola, void* valor) {
    if (cola_esta_vacia(cola)) {
        cola->ultimo = crear_nodo(valor);
        if (!cola->ultimo) return false;
        cola->primero = cola->ultimo;
    } else {
        nodo_t* nodo_aux = cola->ultimo;
        cola->ultimo = crear_nodo(valor);
        if (!cola->ultimo) {
            return false;
        }
        nodo_aux->proximo = cola->ultimo;
    }
    return true;
}

void* cola_ver_primero(const cola_t *cola) {
    return (cola_esta_vacia(cola))? NULL : cola->primero->dato;
}

void* cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    nodo_t* nodo_aux = cola->primero;    
    void* dato_aux = nodo_aux->dato;
    cola->primero = cola->primero->proximo;
    if (cola->primero == NULL) {
        cola->ultimo = NULL;
    }
    free(nodo_aux);
    return dato_aux;
}
