#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>

void pruebas_lista_nula() {
    lista_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
}

/* Pruebas para una lista vacia */
void pruebas_lista_vacia() {
    lista_t* lista_1 = lista_crear();
    print_test("Lista 1: Creada correctamente", lista_1 != NULL);
    print_test("Lista 1: Esta vacia", lista_esta_vacia(lista_1));
    print_test("Lista 1: Si esta vacia no tiene primer elemento", lista_ver_primero(lista_1) == NULL);
    print_test("Lista 1: Si esta vacia no se puede desenlistar", lista_desenlistar(lista_1) == NULL);
    lista_destruir(lista_1, NULL);
    print_test("Lista 1: Destruida correctamente", true);
}

/* Pruebas guardando algunos elementos en la lista. */
void pruebas_lista_enlistar_algunos_elementos() {
    lista_t* lista_2 = lista_crear();
    print_test("Lista 2: Creada correctamente", lista_2 != NULL);
    int valor = 5;
    print_test("Lista 2: Permite enlistar un int", lista_enlistar(lista_2, &valor));
    print_test("Lista 2: El primer elemento de la lista es 5", lista_ver_primero(lista_2) == &valor);    
    char valor2 = 'a';
    print_test("Lista 2: Permite enlistar un char", lista_enlistar(lista_2, &valor2));
    print_test("Lista 2: El primer elemento de la lista sigue siendo 5", lista_ver_primero(lista_2) == &valor);
    print_test("Lista 2: Permite desenlistar un int", lista_desenlistar(lista_2));
    print_test("Lista 2: El primer elemento de la lista es \'a\'", lista_ver_primero(lista_2) == &valor2);
    print_test("Lista 2: Permite desenlistar un char", lista_desenlistar(lista_2));
    print_test("Lista 2: Si esta vacia no tiene primer elemento", lista_ver_primero(lista_2) == NULL);
    print_test("Lista 2: Si esta vacia no se puede desenlistar", lista_desenlistar(lista_2) == NULL);
    int* valor3 = NULL;
    print_test("Lista 2: Permite enlistar un NULL", lista_enlistar(lista_2, &valor3));
    print_test("Lista 2: El primer elemento de la lista es NULL", lista_ver_primero(lista_2) == &valor3);
    int* valor4 = NULL;
    print_test("Lista 2: Permite enlistar un NULL", lista_enlistar(lista_2, &valor4));
        print_test("Lista 2: El primer elemento de la lista sigue siendo el primer NULL enlistado", lista_ver_primero(lista_2) == &valor3);
    print_test("Lista 2: Permite desenlistar un NULL", lista_desenlistar(lista_2));
    print_test("Lista 2: El primer elemento de la lista es el segundo NULL enlistado", lista_ver_primero(lista_2) == &valor4);
    lista_destruir(lista_2,NULL);
    print_test("Lista 2: Destruida correctamente (Parametro en NULL. Se deja un elemento enlistado para verificar por valgrind que no se pierda memoria)", true);    
}

void destruir_datos(void* elemento) {
    lista_destruir((lista_t*) elemento, NULL);
}

/*pruebas guardando elementos que hayan solicitado memoria dinamica*/
void pruebas_lista_enlistar_con_malloc() {
    int* p_entero_1 = malloc(sizeof(int));
    *p_entero_1 = 5;    
    lista_t* lista_3 = lista_crear();
    print_test("Lista 3: Creada correctamente", lista_3 != NULL);    
    print_test("Lista 3: Permite enlistar un int (pruebas memoria dinamica)", lista_enlistar(lista_3, p_entero_1));
    print_test("Lista 3: El primer elemento de la lista es 5", lista_ver_primero(lista_3) == p_entero_1);    
    char* p_char_1 = malloc(sizeof(char));
    *p_char_1 = 'a';
    print_test("Lista 3: Permite enlistar un char (pruebas memoria dinamica)", lista_enlistar(lista_3, p_char_1));
    print_test("Lista 3: El primer elemento de la lista sigue siendo 5", lista_ver_primero(lista_3) == p_entero_1);
    void* valor = lista_desenlistar(lista_3);
    print_test("Lista 3: Permite desenlistar un int", valor);
    free(valor);
    print_test("Lista 3: El primer elemento de la lista es \'a\'", lista_ver_primero(lista_3) == p_char_1);
    valor = lista_desenlistar(lista_3);
    print_test("Lista 3: Permite desenlistar un char", valor);
    free(valor);
    print_test("Lista 3: Si esta vacia no tiene primer elemento", lista_ver_primero(lista_3) == NULL);
    print_test("Lista 3: Si esta vacia no se puede desenlistar", lista_desenlistar(lista_3) == NULL);
    lista_destruir(lista_3,NULL);
    print_test("Lista 3: Destruida correctamente (Parametro en NULL porque la lista no tenia elementos en memoria dinámica)", true);
    lista_3 = lista_crear();
    print_test("Lista 3: Creada correctamente por segunda vez", lista_3 != NULL);  
    p_entero_1 = malloc(sizeof(int));
    *p_entero_1 = 5;
    p_char_1 = malloc(sizeof(char));
    *p_char_1 = 'a';
    print_test("Lista 3: Permite enlistar un int (pruebas memoria dinamica)", lista_enlistar(lista_3, p_entero_1));
    print_test("Lista 3: Permite enlistar un char (pruebas memoria dinamica)", lista_enlistar(lista_3, p_char_1));
    lista_destruir(lista_3,free);
    print_test("Lista 3: Destruida correctamente (Parametro en free porque la lista tenia elementos en memoria dinámica)", true);
    lista_3 = lista_crear();
    print_test("Lista 3: Creada correctamente por segunda vez", lista_3 != NULL);
    lista_t* sub_lista_3 = lista_crear();
    print_test("SubLista 3: Creada correctamente (se enlistará como elemento de la Lista 3)", sub_lista_3 != NULL);
    int vector[10];
    bool resultado_exitoso = true;
    for(int i = 0; i < 10; i++) {
        vector[i] = i;
        resultado_exitoso &= lista_enlistar(sub_lista_3, &vector[i]);
    }
    print_test("SubLista 3: Se pudieron enlistar todos los elementos correctamente", resultado_exitoso);
    resultado_exitoso = true;    
    resultado_exitoso &= lista_enlistar(lista_3, sub_lista_3);
    print_test("Lista 3: Se pudo enlistar el elemento SubLista 3 correctamente", resultado_exitoso);
    lista_destruir(lista_3, destruir_datos);
    print_test("Lista 3: Destruida correctamente (Parametro funcion destruir_datos() porque la lista tenia un elemento de tipo lista en memoria dinámica)", true);   
}

/* Pruebas de lista con un volumen grande de elementos */
void pruebas_lista_volumen() {
    size_t cant_lista = 100000;    
    lista_t* lista_4 = lista_crear();
    print_test("Lista 4: Creada correctamente", lista_4 != NULL);    
    int vector[cant_lista];
    bool resultado_exitoso = true;
    for (int i = 0; i < cant_lista; i++) {
        vector[i] = i;
        resultado_exitoso &= lista_enlistar(lista_4, &vector[i]);
    }
    print_test("Lista 4: Se pudieron enlistar todos los elementos correctamente", resultado_exitoso);
    print_test("Lista 4: El primer elemento de la lista 3 es correcto", lista_ver_primero(lista_4) == &vector[0]);    
    resultado_exitoso = true;
    void* dato = NULL;
    for (int i = 0; i < cant_lista; i++) {
        dato = lista_desenlistar(lista_4);
        resultado_exitoso &= (dato == NULL)? false : true;
        }
    print_test("Lista 4: se pudieron desenlistar todos los elementos correctamente", resultado_exitoso);    
    resultado_exitoso = true;
    for (int i = 0; i < cant_lista; i++) {
        resultado_exitoso &= lista_esta_vacia(lista_4);
    }
    print_test("Lista 4: No permite desenlistar la lista estando vacia (se realizaron numerosos intentos)", resultado_exitoso);    
    lista_destruir(lista_4, NULL);
    print_test("Lista 4: Destruida correctamente", true);
}

void pruebas_lista_alumno() {
    pruebas_lista_nula();
    pruebas_lista_vacia();
    pruebas_lista_enlistar_algunos_elementos();
    pruebas_lista_enlistar_con_malloc();
    pruebas_lista_volumen();
}
