#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include "lista.h"
#define CANT_ELEMENTOS 100000

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
    print_test("Lista 1: Si esta vacia no tiene ultimo elemento", lista_ver_ultimo(lista_1) == NULL);
    print_test("Lista 1: Si esta vacia no se puede eliminar un elemento", lista_borrar_primero(lista_1) == NULL);
    lista_destruir(lista_1, NULL);
    print_test("Lista 1: Destruida correctamente", true);
}

/* Pruebas guardando algunos elementos en la lista. */
void pruebas_lista_insertar_algunos_elementos() {
    lista_t* lista_2 = lista_crear();
    print_test("Lista 2: Creada correctamente", lista_2 != NULL);
    int valor = 5;
    print_test("Lista 2: Permite agregar primero un int", lista_insertar_primero(lista_2, &valor));
    print_test("Lista 2: El primer elemento de la lista es 5", lista_ver_primero(lista_2) == &valor);    
    print_test("Lista 2: El ultimo elemento de la lista es 5", lista_ver_ultimo(lista_2) == &valor);    
    char valor2 = 'a';
    print_test("Lista 2: Permite agregar al final un char", lista_insertar_ultimo(lista_2, &valor2));
    print_test("Lista 2: El primer elemento de la lista sigue siendo 5", lista_ver_primero(lista_2) == &valor);
    print_test("Lista 2: El ultimo elemento de la lista es \'a\'", lista_ver_ultimo(lista_2) == &valor2);    
    print_test("Lista 2: Permite desenlistar un int", lista_borrar_primero(lista_2));
    print_test("Lista 2: El primer elemento de la lista es \'a\'", lista_ver_primero(lista_2) == &valor2);
    print_test("Lista 2: Permite desenlistar un char", lista_borrar_primero(lista_2));
    print_test("Lista 2: Si esta vacia no tiene primer elemento", lista_ver_primero(lista_2) == NULL);
    print_test("Lista 2: Si esta vacia no tiene ultimo elemento", lista_ver_ultimo(lista_2) == NULL);
    print_test("Lista 2: Si esta vacia no se puede eliminar un elemento", lista_borrar_primero(lista_2) == NULL);
    int* valor3 = NULL;
    print_test("Lista 2: Permite insertar primero un NULL", lista_insertar_primero(lista_2, &valor3));
    print_test("Lista 2: El primer elemento de la lista es NULL", lista_ver_primero(lista_2) == &valor3);
    int* valor5 = NULL;
    print_test("Lista 2: Permite insertar ultimo un NULL", lista_insertar_ultimo(lista_2, &valor5));
    print_test("Lista 2: El primer elemento de la lista sigue siendo el primer NULL insertado", lista_ver_primero(lista_2) == &valor3);
    print_test("Lista 2: El ultimo elemento de la lista sigue siendo el ultimo NULL insertado", lista_ver_ultimo(lista_2) == &valor5);
    print_test("Lista 2: Permite borrar un NULL", lista_borrar_primero(lista_2));
    print_test("Lista 2: El primer elemento de la lista es el segundo NULL enlistado", lista_ver_primero(lista_2) == &valor5);
    print_test("Lista 2: El ultimo elemento de la lista sigue siendo el ultimo NULL insertado", lista_ver_ultimo(lista_2) == &valor5);
    lista_destruir(lista_2,NULL);
    print_test("Lista 2: Destruida correctamente (Parametro en NULL. Se deja un elemento enlistado para verificar por valgrind que no se pierda memoria)", true);
}

void destruir_datos(void* elemento) {
    lista_destruir((lista_t*) elemento, NULL);
}

/*pruebas guardando elementos que hayan solicitado memoria dinamica*/
void pruebas_lista_insertar_con_malloc() {
    int* p_entero_1 = malloc(sizeof(int));
    *p_entero_1 = 5;    
    lista_t* lista_3 = lista_crear();
    print_test("Lista 3: Creada correctamente", lista_3 != NULL);    
    print_test("Lista 3: Permite insertar primero un int (pruebas memoria dinamica)", lista_insertar_primero(lista_3, p_entero_1));
    print_test("Lista 3: El primer elemento de la lista es 5", lista_ver_primero(lista_3) == p_entero_1);    
    print_test("Lista 3: El ultimo elemento de la lista es 5", lista_ver_ultimo(lista_3) == p_entero_1);    
    char* p_char_1 = malloc(sizeof(char));
    *p_char_1 = 'a';
    print_test("Lista 3: Permite insertar al final un char (pruebas memoria dinamica)", lista_insertar_ultimo(lista_3, p_char_1));
    print_test("Lista 3: El primer elemento de la lista sigue siendo 5", lista_ver_primero(lista_3) == p_entero_1);
    print_test("Lista 3: El ultimo elemento de la lista es \'a\'", lista_ver_ultimo(lista_3) == p_char_1);
    void* valor = lista_borrar_primero(lista_3);
    print_test("Lista 3: Permite desenlistar un int", valor);
    free(valor);
    print_test("Lista 3: El primer elemento de la lista es \'a\'", lista_ver_primero(lista_3) == p_char_1);
    print_test("Lista 3: El ultimo elemento de la lista es \'a\'", lista_ver_ultimo(lista_3) == p_char_1);
    valor = lista_borrar_primero(lista_3);
    print_test("Lista 3: Permite desenlistar un char", valor);
    free(valor);
    print_test("Lista 3: Si esta vacia no tiene primer elemento", lista_ver_primero(lista_3) == NULL);
    print_test("Lista 3: Si esta vacia no tiene ultimo elemento", lista_ver_ultimo(lista_3) == NULL);
    print_test("Lista 3: Si esta vacia no se puede borrar un elemento", lista_borrar_primero(lista_3) == NULL);
    lista_destruir(lista_3,NULL);
    print_test("Lista 3: Destruida correctamente (Parametro en NULL porque la lista no tenia elementos en memoria dinámica)", true);
    lista_3 = lista_crear();
    print_test("Lista 3: Creada correctamente por segunda vez", lista_3 != NULL);  
    p_entero_1 = malloc(sizeof(int));
    *p_entero_1 = 5;
    p_char_1 = malloc(sizeof(char));
    *p_char_1 = 'a';
    print_test("Lista 3: Permite insertar primero un int (pruebas memoria dinamica)", lista_insertar_primero(lista_3, p_entero_1));
    print_test("Lista 3: Permite insertar primero un char (pruebas memoria dinamica)", lista_insertar_primero(lista_3, p_char_1));
    print_test("Lista 3: El primer elemento de la lista es \'a\'", lista_ver_primero(lista_3) == p_char_1);
    print_test("Lista 3: El ultimo elemento de la lista es 5", lista_ver_ultimo(lista_3) == p_entero_1);
    lista_destruir(lista_3,free);
    print_test("Lista 3: Destruida correctamente (Parametro en free porque la lista tenia elementos en memoria dinámica)", true);
    lista_3 = lista_crear();
    print_test("Lista 3: Creada correctamente por segunda vez", lista_3 != NULL);
    lista_t* sub_lista_3 = lista_crear();
    print_test("SubLista 3: Creada correctamente (se insertará primero como elemento de la Lista 3)", sub_lista_3 != NULL);
    int vector[10];
    bool resultado_exitoso = true;
    for(int i = 0; i < 10; i++) {
        vector[i] = i;
        resultado_exitoso &= lista_insertar_ultimo(sub_lista_3, &vector[i]);
    }
    print_test("SubLista 3: Se pudieron insertar ultimos todos los elementos correctamente", resultado_exitoso);
    resultado_exitoso = true;    
    resultado_exitoso &= lista_insertar_primero(lista_3, sub_lista_3);
    print_test("Lista 3: Se pudo insertar primero el elemento SubLista 3 correctamente", resultado_exitoso);
    lista_destruir(lista_3, destruir_datos);
    print_test("Lista 3: Destruida correctamente (Parametro funcion destruir_datos() porque la lista tenia un elemento de tipo lista en memoria dinámica)", true);   
}

/* Pruebas de lista con un volumen grande de elementos */
void pruebas_lista_volumen() {
    size_t cant_lista = CANT_ELEMENTOS;    
    lista_t* lista_4 = lista_crear();
    print_test("Lista 4: Creada correctamente", lista_4 != NULL);    
    int vector[cant_lista];
    bool resultado_exitoso = true;
    for (int i = 0; i < cant_lista; i++) {
        vector[i] = i;
        resultado_exitoso &= lista_insertar_primero(lista_4, &vector[i]);
    }
    print_test("Lista 4: Se pudieron insertar primero todos los elementos correctamente", resultado_exitoso);
    print_test("Lista 4: El ultimo elemento de la lista 4 es correcto", lista_ver_ultimo(lista_4) == &vector[0]);    
    print_test("Lista 4: El primer elemento de la lista 4 es correcto", lista_ver_primero(lista_4) == &vector[CANT_ELEMENTOS-1]);    
    resultado_exitoso = true;
    void* dato = NULL;
    for (int i = 0; i < cant_lista; i++) {
        dato = lista_borrar_primero(lista_4);
        resultado_exitoso &= (dato == NULL)? false : true;
        }
    print_test("Lista 4: se pudieron borrar todos los elementos correctamente", resultado_exitoso);    
    resultado_exitoso = true;
    for (int i = 0; i < cant_lista; i++) {
        resultado_exitoso &= lista_esta_vacia(lista_4);
    }
    print_test("Lista 4: No permite borrar elementos de la lista estando vacia (se realizaron numerosos intentos)", resultado_exitoso);    
    lista_destruir(lista_4, NULL);
    print_test("Lista 4: Destruida correctamente", true);
}

void pruebas_lista_iterador_externo() {
    size_t cant_lista = 10;
    lista_t* lista_5 = lista_crear();
    print_test("Lista 5: Creada correctamente", lista_5 != NULL);    
    int vector[cant_lista];
    bool resultado_exitoso = true;
    
    for (int i = 0; i < cant_lista; i++) {
        vector[i] = i;
        resultado_exitoso &= lista_insertar_primero(lista_5, &vector[i]);
    }
    lista_iter_t* iter = lista_iter_crear(lista_5);
    print_test("Iterador 1 Lista 5: Creado correctamente", iter != NULL);    
    int num_items = 0;
    while (!lista_iter_al_final(iter)) {
        ++num_items;
        lista_iter_avanzar(iter);
    }    
    print_test("Iterador 1 Lista 5: La cantidad de items es 10", num_items == 10);
    print_test("Iterador 1 Lista 5: El largo de la lista se actualizó correctamente:", num_items == lista_largo(lista_5));
    lista_iter_destruir(iter);
    print_test("Iterador 1 Lista 5: iterador destruido correctamente", true);
    
    lista_iter_t *iter2 = lista_iter_crear(lista_5);
    print_test("Iterador 2 Lista 5: Creado correctamente", iter2 != NULL);    
    num_items = 0;    
    int dato = 103;
    lista_iter_insertar(iter2, &dato);
    print_test("Iterador 2 Lista 5: El primer elemento de la lista 5 es correcto (visto desde el iterador 2)", lista_iter_ver_actual(iter2) == &dato);    
    print_test("Iterador 2 Lista 5: El primer elemento de la lista 5 es correcto (visto desde la lista)", lista_ver_primero(lista_5) == &dato);    
    while (!lista_iter_al_final(iter2)) {
        ++num_items;
        lista_iter_avanzar(iter2);
    }
    print_test("Iterador 2 Lista 5: La cantidad de items es 11", num_items == 11);
    print_test("Iterador 2 Lista 5: El largo de la lista se actualizó correctamente:", num_items == lista_largo(lista_5));
    print_test("Iterador 2 Lista 5: Se avanzó hasta el final correctamente", lista_iter_al_final(iter2));
    
    char dato2 = 'F';
    lista_iter_insertar(iter2, &dato2);
    print_test("Iterador 2 Lista 5: Permitió insertar correctamente un elemento al final de la lista.",lista_ver_ultimo(lista_5) == &dato2);    
    print_test("Iterador 2 Lista 5: El iterador 2 ya no se encuentra posicionado al final de la lista.", !lista_iter_al_final(iter2));
    print_test("Iterador 2 Lista 5: El iterador 2 ahora apunta al nuevo elemento creado", lista_iter_ver_actual(iter2) == lista_ver_ultimo(lista_5));
    
    lista_iter_destruir(iter2);
    print_test("Iterador 2 Lista 5: iterador 2 destruido correctamente", true);
    
    lista_iter_t *iter3 = lista_iter_crear(lista_5);
    print_test("Iterador 3 Lista 5: Creado correctamente", iter3 != NULL);    
    num_items = 0;

    while (num_items < 5) {
        ++num_items;
        lista_iter_avanzar(iter3);
    }    
    int dato3 = 88;
    lista_iter_insertar(iter3, &dato3);
    print_test("Iterador 3 Lista 5: El elemento de la lista 5 se insertó correctamente en la mitad de la lista", lista_iter_ver_actual(iter3) == &dato3);
    resultado_exitoso = true;
    void* dato_null = NULL;
    lista_iter_destruir(iter3);
    print_test("Iterador 3 Lista 5: iterador 3 destruido correctamente", true);    
    lista_iter_t *iter4 = lista_iter_crear(lista_5);
    print_test("Iterador 4 Lista 5: Creado correctamente", iter4 != NULL);
    while (!lista_esta_vacia(lista_5)){
        dato_null = lista_iter_borrar(iter4);
        resultado_exitoso &= (dato_null == NULL)? false : true;
    }    
    print_test("Iterador 4 Lista 5: se pudieron borrar todos los elementos de la lista 5 correctamente utilizando el iterador 4", resultado_exitoso);
    print_test("Iterador 4 Lista 5: Ahora la lista 5 se encuentra vacía:", lista_esta_vacia(lista_5));
    lista_iter_destruir(iter4);
    print_test("Iterador 4 Lista 5: iterador 4 destruido correctamente", true);
    print_test("Lista 5: La lista aún sigue en memoria, pese a eliminar el iterador:", lista_5 != NULL);
    lista_destruir(lista_5, NULL);
    print_test("Lista 5: Destruida correctamente con parametro NULL, ya que no habia elementos en Heap", true);
    
    lista_t* lista_6 = lista_crear();
    print_test("Lista 6: Creada correctamente", lista_6 != NULL);
    lista_iter_t* iter5 = lista_iter_crear(lista_6);
    print_test("Iterador 5 Lista 6: Creado correctamente", iter != NULL); 
    char* dato4 = "prueba";
    lista_iter_insertar(iter5, &dato4);
    print_test("Iterador 5 Lista 6: El elemento de la lista 6 se insertó correctamente estando la lista vacía", lista_iter_ver_actual(iter5) == &dato4);
    print_test("Iterador 5 Lista 6: El primer elemento de la lista es \'prueba\'", lista_ver_primero(lista_6) == &dato4);
    print_test("Iterador 5 Lista 6: El ultimo elemento de la lista es \'prueba\'", lista_ver_ultimo(lista_6) == &dato4);    
    lista_iter_borrar(iter5);
    print_test("Iterador 5 Lista 6: El elemento de la lista 6 se borro correctamente para una lista con un solo elemento", lista_iter_ver_actual(iter5) == NULL);    
    print_test("Iterador 5 Lista 6: Si esta vacia no se puede eliminar un elemento", lista_iter_borrar(iter5) == NULL);
    int dato5 = 0;
    int dato6 = 1;
    int dato7 = 2;
    lista_iter_insertar(iter5, &dato5);
    lista_iter_insertar(iter5, &dato6);
    lista_iter_insertar(iter5, &dato7);
    print_test("Iterador 5 Lista 6: El primer elemento de la lista es 2", lista_ver_primero(lista_6) == &dato7);
    print_test("Iterador 5 Lista 6: El ultimo elemento de la lista es 0", lista_ver_ultimo(lista_6) == &dato5);  
    print_test("Iterador 5 Lista 6: El elemento actual del iterador, deberia ser 2", lista_iter_ver_actual(iter5) == &dato7); 
    lista_iter_avanzar(iter5);
    lista_iter_avanzar(iter5);
    print_test("Iterador 5 Lista 6: Se avanzaron dos nodos. El elemento actual, deberia ser 0", lista_iter_ver_actual(iter5) == &dato5);
    print_test("Iterador 5 Lista 6: permitió borrar correctamente el último elemento de la lista", lista_iter_borrar(iter5) != NULL);
    print_test("Iterador 5 Lista 6: Al El primer elemento de la lista es 2", lista_ver_primero(lista_6) == &dato7);
    print_test("Iterador 5 Lista 6: El ultimo elemento de la lista es 1", lista_ver_ultimo(lista_6) == &dato6);    
    print_test("Iterador 5 Lista 6: al estar al final de la lista, no debe permitir borrar elementos de la lista", lista_iter_borrar(iter5) == NULL);
    print_test("Iterador 5 Lista 6: El ultimo elemento de la lista 6 se borro correctamente para una lista con mas de un elemento", lista_iter_ver_actual(iter5) == NULL);    
    lista_iter_destruir(iter5);    
    print_test("Iterador 5 Lista 6: iterador 5 destruido correctamente", true);
    print_test("Lista 6: La lista aún sigue en memoria, pese a eliminar el iterador:", lista_6 != NULL);
    lista_destruir(lista_6, NULL);
    print_test("Lista 6: Destruida correctamente con parametro NULL, ya que no habia elementos en Heap", true);
    
    lista_t* lista_7 = lista_crear();
    print_test("Lista 7: Creada correctamente", lista_7 != NULL);
    int dato8 = 0;
    int dato9 = 1;
//     int dato10 = 2;
    lista_insertar_ultimo(lista_7, &dato8);
    lista_insertar_ultimo(lista_7, &dato9);
    //lista_insertar_ultimo(lista_7, &dato10);
    
    lista_iter_t* iter6 = lista_iter_crear(lista_7);
    print_test("Iterador 6 Lista 7: Creado correctamente", iter != NULL);
    
    lista_iter_avanzar(iter6);
    lista_iter_borrar(iter6);
//     lista_iter_borrar(iter6);
//     lista_iter_avanzar(iter6);
//     lista_iter_borrar(iter6);
    
    lista_iter_destruir(iter6);    
    print_test("Iterador 6 Lista 7: iterador 5 destruido correctamente", true);
    
    lista_iter_t* iter7 = lista_iter_crear(lista_7);
    print_test("Iterador 7 Lista 7: Creado correctamente", iter != NULL);
    
    printf("%p item actual antes de avanzar\n", lista_iter_ver_actual(iter7));
    
    lista_iter_avanzar(iter7);
    printf("%p item actual despues de avanzar\n", lista_iter_ver_actual(iter7));
    /*********************************************************************************/
    lista_iter_destruir(iter7);    
    print_test("Iterador 7 Lista 7: iterador 5 destruido correctamente", true);
    print_test("Lista 7: La lista aún sigue en memoria, pese a eliminar el iterador:", lista_7 != NULL);
    lista_destruir(lista_7, NULL);
    print_test("Lista 7: Destruida correctamente con parametro NULL, ya que no habia elementos en Heap", true);
    
}

bool imprimir_todo(void* dato, void* extra) {
    print_test("resultado_exitoso imprimir todos:", dato != NULL);
    return true;
} 

bool imprimir_algunos(void* dato, void* extra) { 
    if (*(size_t*) extra >= 5) { 
        return false; 
    }
    size_t *contador = extra;
    (*contador)++;
    print_test("resultado_exitoso imprimir algunos:", dato != NULL);
    return true;
} 

void pruebas_lista_iterador_interno() {
    size_t cant_lista = 10;
    lista_t* lista_7 = lista_crear();
    print_test("Lista 7: Creada correctamente", lista_7 != NULL);    
    int vector[cant_lista];
    bool resultado_exitoso = true;    
    for (int i = 0; i < cant_lista; i++) {
        vector[i] = i;
        resultado_exitoso &= lista_insertar_primero(lista_7, &vector[i]);
    }    
    lista_iterar(lista_7, imprimir_todo, NULL);    
    size_t contador = 0;
    lista_iterar(lista_7, imprimir_algunos, &contador);    
    lista_destruir(lista_7, NULL);
}

void pruebas_lista_alumno() {    
//     pruebas_lista_nula();
//     pruebas_lista_vacia();
//     pruebas_lista_insertar_algunos_elementos();
//     pruebas_lista_insertar_con_malloc();
//     pruebas_lista_volumen();
    pruebas_lista_iterador_externo();
//     pruebas_lista_iterador_interno();
}
