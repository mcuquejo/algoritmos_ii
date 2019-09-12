#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
pila_t* pila_crear(void) {
    pila_t* pila = malloc(sizeof(*pila));
    if (pila == NULL) {
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = 2;
    pila->datos = malloc(pila->capacidad * sizeof(*pila->datos));
    if (pila->datos == NULL) {
        return NULL;
    }
    return pila;
}

void pila_destruir(pila_t *pila) {
    if (pila->datos != NULL) {
        free(pila->datos);
    }
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
    return (pila->cantidad == 0);
}

bool pila_apilar(pila_t *pila, void* valor) {
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    if (pila->cantidad == pila->capacidad) {
        size_t tam_nuevo = pila->capacidad * 2;
        void** datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(pila->datos));
        if(datos_nuevo == NULL) {
            return false;
        }
        pila->capacidad = tam_nuevo;
        pila->datos = datos_nuevo;
    }
    return true;
}

void* pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }
    void* valor = pila_ver_tope(pila);
    pila->cantidad--;
    if(pila->cantidad*4 <= pila->capacidad) {
        size_t tam_nuevo = pila->capacidad/2;
        void** datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(pila->datos));
        if(datos_nuevo == NULL) {
            return false;
        }
        pila->capacidad = tam_nuevo;
        pila->datos = datos_nuevo;
    }
    return valor;
}
