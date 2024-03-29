#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
/* Pruebas para una cola nula. */
void pruebas_cola_nula() {
    cola_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
}

/* Pruebas para una cola vacia */
void pruebas_cola_vacia() {
    cola_t* cola_1 = cola_crear();
    print_test("Cola 1: Creada correctamente", cola_1 != NULL);
    print_test("Cola 1: Esta vacia", cola_esta_vacia(cola_1));
    print_test("Cola 1: Si esta vacia no tiene primer elemento", cola_ver_primero(cola_1) == NULL);
    print_test("Cola 1: Si esta vacia no se puede desencolar", cola_desencolar(cola_1) == NULL);
    cola_destruir(cola_1, NULL);
    print_test("Cola 1: Destruida correctamente", true);
}

/* Pruebas guardando algunos elementos en la cola. */
void pruebas_cola_encolar_algunos_elementos() {
    cola_t* cola_2 = cola_crear();
    print_test("Cola 2: Creada correctamente", cola_2 != NULL);
    int valor = 5;
    print_test("Cola 2: Permite encolar un int", cola_encolar(cola_2, &valor));
    print_test("Cola 2: El primer elemento de la cola es 5", cola_ver_primero(cola_2) == &valor);    
    char valor2 = 'a';
    print_test("Cola 2: Permite encolar un char", cola_encolar(cola_2, &valor2));
    print_test("Cola 2: El primer elemento de la cola sigue siendo 5", cola_ver_primero(cola_2) == &valor);
    print_test("Cola 2: Permite desencolar un int", cola_desencolar(cola_2));
    print_test("Cola 2: El primer elemento de la cola es \'a\'", cola_ver_primero(cola_2) == &valor2);
    print_test("Cola 2: Permite desencolar un char", cola_desencolar(cola_2));
    print_test("Cola 2: Si esta vacia no tiene primer elemento", cola_ver_primero(cola_2) == NULL);
    print_test("Cola 2: Si esta vacia no se puede desencolar", cola_desencolar(cola_2) == NULL);
    int* valor3 = NULL;
    print_test("Cola 2: Permite encolar un NULL", cola_encolar(cola_2, &valor3));
    print_test("Cola 2: El primer elemento de la cola es NULL", cola_ver_primero(cola_2) == &valor3);
    int* valor4 = NULL;
    print_test("Cola 2: Permite encolar un NULL", cola_encolar(cola_2, &valor4));
        print_test("Cola 2: El primer elemento de la cola sigue siendo el primer NULL encolado", cola_ver_primero(cola_2) == &valor3);
    print_test("Cola 2: Permite desencolar un NULL", cola_desencolar(cola_2));
    print_test("Cola 2: El primer elemento de la cola es el segundo NULL encolado", cola_ver_primero(cola_2) == &valor4);
    cola_destruir(cola_2,NULL);
    print_test("Cola 2: Destruida correctamente (Parametro en NULL. Se deja un elemento encolado para verificar por valgrind que no se pierda memoria)", true);    
}

void destruir_datos(void* elemento) {
    cola_destruir((cola_t*) elemento, NULL);
}

/*pruebas guardando elementos que hayan solicitado memoria dinamica*/
void pruebas_cola_encolar_con_malloc() {
    int* p_entero_1 = malloc(sizeof(int));
    *p_entero_1 = 5;    
    cola_t* cola_3 = cola_crear();
    print_test("Cola 3: Creada correctamente", cola_3 != NULL);    
    print_test("Cola 3: Permite encolar un int (pruebas memoria dinamica)", cola_encolar(cola_3, p_entero_1));
    print_test("Cola 3: El primer elemento de la cola es 5", cola_ver_primero(cola_3) == p_entero_1);    
    char* p_char_1 = malloc(sizeof(char));
    *p_char_1 = 'a';
    print_test("Cola 3: Permite encolar un char (pruebas memoria dinamica)", cola_encolar(cola_3, p_char_1));
    print_test("Cola 3: El primer elemento de la cola sigue siendo 5", cola_ver_primero(cola_3) == p_entero_1);
    void* valor = cola_desencolar(cola_3);
    print_test("Cola 3: Permite desencolar un int", valor);
    free(valor);
    print_test("Cola 3: El primer elemento de la cola es \'a\'", cola_ver_primero(cola_3) == p_char_1);
    valor = cola_desencolar(cola_3);
    print_test("Cola 3: Permite desencolar un char", valor);
    free(valor);
    print_test("Cola 3: Si esta vacia no tiene primer elemento", cola_ver_primero(cola_3) == NULL);
    print_test("Cola 3: Si esta vacia no se puede desencolar", cola_desencolar(cola_3) == NULL);
    cola_destruir(cola_3,NULL);
    print_test("Cola 3: Destruida correctamente (Parametro en NULL porque la cola no tenia elementos en memoria dinámica)", true);
    cola_3 = cola_crear();
    print_test("Cola 3: Creada correctamente por segunda vez", cola_3 != NULL);  
    p_entero_1 = malloc(sizeof(int));
    *p_entero_1 = 5;
    p_char_1 = malloc(sizeof(char));
    *p_char_1 = 'a';
    print_test("Cola 3: Permite encolar un int (pruebas memoria dinamica)", cola_encolar(cola_3, p_entero_1));
    print_test("Cola 3: Permite encolar un char (pruebas memoria dinamica)", cola_encolar(cola_3, p_char_1));
    cola_destruir(cola_3,free);
    print_test("Cola 3: Destruida correctamente (Parametro en free porque la cola tenia elementos en memoria dinámica)", true);
    cola_3 = cola_crear();
    print_test("Cola 3: Creada correctamente por segunda vez", cola_3 != NULL);
    cola_t* sub_cola_3 = cola_crear();
    print_test("SubCola 3: Creada correctamente (se encolará como elemento de la Cola 3)", sub_cola_3 != NULL);
    int vector[10];
    bool resultado_exitoso = true;
    for(int i = 0; i < 10; i++) {
        vector[i] = i;
        resultado_exitoso &= cola_encolar(sub_cola_3, &vector[i]);
    }
    print_test("SubCola 3: Se pudieron encolar todos los elementos correctamente", resultado_exitoso);
    resultado_exitoso = true;    
    resultado_exitoso &= cola_encolar(cola_3, sub_cola_3);
    print_test("Cola 3: Se pudo encolar el elemento SubCola 3 correctamente", resultado_exitoso);
    cola_destruir(cola_3, destruir_datos);
    print_test("Cola 3: Destruida correctamente (Parametro funcion destruir_datos() porque la cola tenia un elemento de tipo cola en memoria dinámica)", true);   
}

/* Pruebas de cola con un volumen grande de elementos */
void pruebas_cola_volumen() {
    size_t cant_cola = 100000;    
    cola_t* cola_4 = cola_crear();
    print_test("Cola 4: Creada correctamente", cola_4 != NULL);    
    int vector[cant_cola];
    bool resultado_exitoso = true;
    for (int i = 0; i < cant_cola; i++) {
        vector[i] = i;
        resultado_exitoso &= cola_encolar(cola_4, &vector[i]);
    }
    print_test("Cola 4: Se pudieron encolar todos los elementos correctamente", resultado_exitoso);
    print_test("Cola 4: El primer elemento de la cola 3 es correcto", cola_ver_primero(cola_4) == &vector[0]);    
    resultado_exitoso = true;
    void* dato = NULL;
    for (int i = 0; i < cant_cola; i++) {
        dato = cola_desencolar(cola_4);
        resultado_exitoso &= (dato == NULL)? false : true;
        }
    print_test("Cola 4: se pudieron desencolar todos los elementos correctamente", resultado_exitoso);    
    resultado_exitoso = true;
    for (int i = 0; i < cant_cola; i++) {
        resultado_exitoso &= cola_esta_vacia(cola_4);
    }
    print_test("Cola 4: No permite desencolar la cola estando vacia (se realizaron numerosos intentos)", resultado_exitoso);    
    cola_destruir(cola_4, NULL);
    print_test("Cola 4: Destruida correctamente", true);
}

void pruebas_cola_alumno() {
    pruebas_cola_nula();
    pruebas_cola_vacia();
    pruebas_cola_encolar_algunos_elementos();
    pruebas_cola_encolar_con_malloc();
    pruebas_cola_volumen();
}
