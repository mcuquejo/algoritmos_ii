#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include "ejemplo_iteradores.h"
#include "lista.h"

void pruebas_lista_nula() {
    lista_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
}

void pruebas_lista_alumno() {
    pruebas_lista_nula();
    ejemplo_iteradores();
}
