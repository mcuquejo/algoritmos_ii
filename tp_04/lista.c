#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;


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
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    return (lista->primero == NULL);
}

bool lista_insertar_primero(lista_t *lista, void* dato) {
    if (lista_esta_vacia(lista)) {
        lista->primero = crear_nodo(dato);
        if (!lista->ultimo) {
            return false;
        }
        lista->ultimo = lista->primero;
    } else {
        nodo_t* nodo_aux = lista->primero;
        lista->primero = crear_nodo(dato);
        if (!lista->primero) {
            lista->primero = nodo_aux;
            return false;
        }
        nodo_aux->proximo = lista->ultimo;
    }
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void* dato) {
    if (lista_esta_vacia(lista)) {
        lista->ultimo = crear_nodo(dato);
        if (!lista->ultimo) {
            return false;
        }
        lista->primero = lista->ultimo;
    } else {
        nodo_t* nodo_aux = lista->ultimo;
        lista->ultimo = crear_nodo(dato);
        if (!lista->ultimo) {
            lista->ultimo = nodo_aux;
            return false;
        }
        nodo_aux->proximo = cola->ultimo;
    }
    lista->largo++;
    return true;
}


void* lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    nodo_t* nodo_aux = lista->primero;    
    void* dato_aux = nodo_aux->dato;
    lista->primero = lista->primero->proximo;
    if (lista->primero == NULL) {
        lista->ultimo = NULL;
    }
    free(nodo_aux);
    lista->largo--;
    return dato_aux;
}


void *lista_ver_primero(const lista_t *lista) {
    return (lista_esta_vacia(lista))? NULL : lista->primero->dato;
}


void *lista_ver_ultimo(const lista_t *lista) {
    return (lista_esta_vacia(lista))? NULL : lista->ultimo->dato;
}


size_t lista_largo(const lista_t *lista){
    return return (lista_esta_vacia(lista))? NULL : lista->largo;
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



