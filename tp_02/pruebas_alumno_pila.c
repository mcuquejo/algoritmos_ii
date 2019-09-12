#include "pila.h"
#include "testing.h"
#include <stddef.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
/* Pruebas para una pila nula. */
void pruebas_pila_nula(){
    pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
}

/* Pruebas para una pila vacia */
void pruebas_pila_vacia(){
    pila_t* pila_1 = pila_crear();
    print_test("Pila 1: Creada correctamente", pila_1 != NULL);
    print_test("Pila 1: Esta vacia", pila_esta_vacia(pila_1));
    print_test("Pila 1: Si esta vacia no tiene tope", pila_ver_tope(pila_1) == NULL);
    print_test("Pila 1: Si esta vacia no se puede desapilar", pila_desapilar(pila_1) == NULL);
    pila_destruir(pila_1);
    print_test("Pila 1: Destruida correctamente", true);
}

/* Pruebas guardando algunos elementos en la pila. */
void pruebas_pila_apilar_algunos_elementos(){
    pila_t* pila_2 = pila_crear();
    print_test("Pila 2: Creada correctamente", pila_2 != NULL);
    int valor = 5;
    print_test("Pila 2: Permite apilar un int", pila_apilar(pila_2, &valor));
    print_test("Pila 2: El tope de la pila es 5", pila_ver_tope(pila_2) == &valor);    
    char valor2 = 'a';
    print_test("Pila 2: Permite apilar un char", pila_apilar(pila_2, &valor2));
    print_test("Pila 2: El tope de la pila es \'a\'", pila_ver_tope(pila_2) == &valor2);
    print_test("Pila 2: Permite desapilar un char", pila_desapilar(pila_2));
    print_test("Pila 2: El tope de la pila es 5", pila_ver_tope(pila_2) == &valor);
    print_test("Pila 2: Permite desapilar un int", pila_desapilar(pila_2));
    print_test("Pila 2: Si esta vacia no tiene tope", pila_ver_tope(pila_2) == NULL);
    print_test("Pila 2: Si esta vacia no se puede desapilar", pila_desapilar(pila_2) == NULL);
    int* valor3 = NULL;
    print_test("Pila 2: Permite apilar un NULL", pila_apilar(pila_2, &valor3));
    print_test("Pila 2: El tope de la pila es NULL", pila_ver_tope(pila_2) == &valor3);
    int* valor4 = NULL;
    print_test("Pila 2: Permite apilar un NULL", pila_apilar(pila_2, &valor4));
    print_test("Pila 2: El tope de la pila es NULL", pila_ver_tope(pila_2) == &valor4);
    print_test("Pila 2: Permite desapilar un NULL", pila_desapilar(pila_2));
    print_test("Pila 2: El tope de la pila es NULL", pila_ver_tope(pila_2) == &valor3);
    
    /*se destruye pila antes de eliminar ultimo elemento, para verificar que libere memoria correctamente. */
    pila_destruir(pila_2);
    print_test("Pila 2: Destruida correctamente (se deja un elemento apilado para verificar por valgrind que no se pierda memoria)", true);    
}

/* Pruebas de pila con un volumen grande de elementos */
void pruebas_pila_volumen(){
    size_t cant_pila = 100000;    
    pila_t* pila_3 = pila_crear();
    print_test("Pila 3: Creada correctamente", pila_3 != NULL);    
    int vector[cant_pila];
    bool resultado_exitoso = true;
    for (int i = 0; i < cant_pila; i++){
        resultado_exitoso &= pila_apilar(pila_3, &vector[i]);        
    }
    print_test("Pila 3: Se pudieron apilar todos los elementos correctamente", resultado_exitoso);
    print_test("Pila 3: El tope de la pila 3 es correcto", pila_ver_tope(pila_3) == &vector[cant_pila-1]);    
    
    resultado_exitoso = true;
    for (int i = 0; i < cant_pila; i++){
        resultado_exitoso &= (pila_desapilar(pila_3) == NULL)? false : true;
        }
    print_test("Pila 3: se pudieron desapilar todos los elementos correctamente", resultado_exitoso);
    
    resultado_exitoso = true;
    for (int i = 0; i < cant_pila; i++){
        resultado_exitoso &= pila_esta_vacia(pila_3);
    }
    print_test("Pila 3: No permite desapilar la pila estando vacia (se realizaron numerosos intentos)", resultado_exitoso);
    
    pila_destruir(pila_3);
    print_test("Pila 3: Destruida correctamente", true);
}

void pruebas_pila_alumno() {
    pruebas_pila_nula();
    pruebas_pila_vacia();
    pruebas_pila_apilar_algunos_elementos();
    pruebas_pila_volumen();
}
