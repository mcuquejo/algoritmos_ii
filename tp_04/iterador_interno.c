#include "iterador_interno.h"
#include <stddef.h>
#include <stdlib.h>

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);
