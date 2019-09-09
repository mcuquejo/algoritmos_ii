#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#define CANT_VECTOR 100000


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    
    pila_t* pila_1 = pila_crear();

    print_test("Pila creada", pila_1 != NULL);
    print_test("Pila está vacía", pila_esta_vacia(pila_1));
    print_test("Pila vacia no tiene tope", pila_ver_tope(pila_1) == NULL);
    print_test("Pila vacia no se puede desapilar", pila_desapilar(pila_1) == NULL);

	int valor = 5;
    print_test("Pila permite apilar un int", pila_apilar(pila_1, &valor));
    print_test("El tope de la pila es 5", pila_ver_tope(pila_1) == &valor);
    
    char valor2 = 'a';
    print_test("Pila permite apilar un char", pila_apilar(pila_1, &valor2));
    print_test("El tope de la pila es a", pila_ver_tope(pila_1) == &valor2);

    print_test("Pila permite desapilar un char", pila_desapilar(pila_1));
    print_test("El tope de la pila es 5", pila_ver_tope(pila_1) == &valor);
    print_test("Pila permite desapilar un int", pila_desapilar(pila_1));
    print_test("Pila vacia no tiene tope", pila_ver_tope(pila_1) == NULL);
    print_test("Pila vacia no se puede desapilar", pila_desapilar(pila_1) == NULL);

	int* valor3 = NULL;
	int* valor4 = NULL;
	print_test("Pila permite apilar un NULL", pila_apilar(pila_1, &valor3));
    print_test("El tope de la pila es NULL", pila_ver_tope(pila_1) == &valor3);
    print_test("Pila permite apilar un NULL", pila_apilar(pila_1, &valor4));
    print_test("El tope de la pila es NULL", pila_ver_tope(pila_1) == &valor4);
	print_test("Pila permite desapilar un NULL", pila_desapilar(pila_1));
	print_test("El tope de la pila es NULL", pila_ver_tope(pila_1) == &valor3);
    
    
    pila_destruir(pila_1);
    print_test("la pila 1 fue destruida", true);
    
    pila_t* pila_2 = pila_crear();
	print_test("Pila 2 creada", pila_2 != NULL);
    
    int vector[CANT_VECTOR];
    for (int i = 0; i < CANT_VECTOR; i++){
		pila_apilar(pila_2, &vector[i]);
		print_test("El tope de la pila 2 es el valor del vector", pila_ver_tope(pila_2) == &vector[i]);
	}
    print_test("El tope de la pila 2 es el valor del vector", pila_ver_tope(pila_2) == &vector[CANT_VECTOR-1]);

    for (int i = 0; i < CANT_VECTOR + 10; i++){
		pila_desapilar(pila_2);
		if (!pila_esta_vacia(pila_2)){
			print_test("El tope de la pila 2 es el valor del vector", pila_ver_tope(pila_2) == &vector[CANT_VECTOR - 2 - i]);
		}else {
			print_test("Pila 2 está vacía", pila_esta_vacia(pila_2));
		}
		
	}

	
    pila_destruir(pila_2);
    print_test("la pila 2 fue destruida", true);
}
