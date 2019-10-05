#include <stddef.h>
#include <stdlib.h>
#include "lista.h"

typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;

struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

struct lista_iter {
    lista_t* lista;
    nodo_t* anterior;
    nodo_t* actual;
};


nodo_t* crear_nodo(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;        
    }
    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

lista_t* lista_crear(void) {    
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL) {
        return NULL;
    }
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->primero == NULL;
}

bool lista_insertar_primero(lista_t *lista, void* dato) {
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL){
        return false;
    }
    if (lista_esta_vacia(lista)) {    
        lista->primero = nodo;
        lista->ultimo = lista->primero;
    } else {            
        nodo_t* nodo_aux = lista->primero;
        lista->primero = nodo;
        lista->primero->proximo = nodo_aux;
    }
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void* dato) {
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL) {
        return false;
    }
    if (lista_esta_vacia(lista)) {
        lista->ultimo = nodo;
        lista->primero = lista->ultimo;
    } else {
        nodo_t* nodo_aux = lista->ultimo;
        lista->ultimo = nodo;    
        nodo_aux->proximo = lista->ultimo;
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
    return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}


void *lista_ver_ultimo(const lista_t *lista) {
    return lista_esta_vacia(lista) ? NULL : lista->ultimo->dato;
}


size_t lista_largo(const lista_t *lista){
    return lista->largo;
}


void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
    while (!lista_esta_vacia(lista)) {
        void* elem = lista_borrar_primero(lista);
        if(destruir_dato != NULL) {
            destruir_dato(elem);
        }
    }
    free(lista);
}

lista_iter_t* lista_iter_crear(lista_t *lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) {
        return NULL;
    }
    iter->lista = lista;
    iter->anterior = NULL;
    iter->actual = lista->primero;    
    return iter;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return iter->actual == NULL;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) {
        return false;  
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->proximo;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
     return lista_iter_al_final(iter) ? NULL : iter->actual->dato;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL) {
        return false;
    }
    printf("iterador->actual: %i\n", *(int*)iter->actual);
    printf("lista_ver_primero(iter->lista): %i\n", *(int*)lista_ver_primero(iter->lista));
    if (lista_esta_vacia(iter->lista)) {
        printf("lista está vacia\n");
        iter->actual = nodo;
        iter->lista->primero = iter->actual;
        iter->lista->ultimo = iter->actual;
        
    } else if (iter->actual == lista_ver_primero(iter->lista)) {    
        printf("iterador en primera posicion\n");
        nodo_t* nodo_aux = iter->actual;
        iter->actual = nodo;
        iter->lista->primero = iter->actual;
        iter->lista->primero->proximo = nodo_aux;
    } else if (lista_iter_al_final(iter)) {
        printf("iterador al final\n");
        iter->actual = nodo;
        iter->lista->ultimo = iter->actual;
        iter->anterior->proximo = iter->actual;
    } else {
        printf("iterador en un caso no borde\n");
        nodo_t* nodo_aux = iter->actual;
        iter->actual = nodo;
        iter->actual->proximo = nodo_aux;
        iter->anterior->proximo = iter->actual;
    }
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {    
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) {
        return NULL;
    }    
    nodo_t* nodo_aux = iter->actual;
    void* dato_aux = nodo_aux->dato;    
    if (iter->actual == lista_ver_primero(iter->lista)) {
        iter->actual = iter->actual->proximo;        
        iter->lista->primero = iter->actual;
        if (iter->actual == NULL) {
            iter->lista->ultimo = iter->actual;
        }        
    } else if (iter->actual == lista_ver_ultimo(iter->lista)) {
        iter->actual = iter->actual->proximo;
        iter->anterior->proximo = iter->actual;
        iter->lista->ultimo = iter->anterior;
    } else {
       iter->actual = iter->actual->proximo;
    }
    iter->lista->largo--;
    free(nodo_aux);
    return dato_aux;
}

void *lista_iter_borrar2(lista_iter_t *iter){
    nodo_t* nodo_aux;
    void* dato_aux;
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) {
        return NULL;
    }
    if (iter->anterior == NULL) {
        nodo_aux = iter->lista->primero;
        dato_aux = nodo_aux->dato;
        iter->lista->primero = iter->lista->primero->proximo;
        if (iter->lista->primero == NULL) {
            iter->lista->ultimo = NULL;
        }
        iter->actual = iter->lista->primero;
    
    } else if (iter->actual->proximo == NULL) {
        nodo_aux = iter->actual;
        dato_aux = nodo_aux->dato;
        iter->lista->ultimo = iter->anterior;
        iter->actual = iter->actual->proximo;
       iter->anterior->proximo = iter->actual; //referencia anterior  actualizar al proximo.
    } else {
        nodo_aux = iter->actual;
        dato_aux = nodo_aux->dato;
        iter->actual = iter->actual->proximo;        
    }
    iter->lista->largo--;
    free(nodo_aux);
    return dato_aux;    
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t* nodo_actual = lista->primero;
    bool resultado = true;
    while (resultado) {
        resultado = visitar(nodo_actual->dato, extra);
        nodo_actual = nodo_actual->proximo;
        if (nodo_actual == NULL) {
            break;
        }
    }
}
