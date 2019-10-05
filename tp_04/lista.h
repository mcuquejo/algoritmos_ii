#include <stdbool.h>
#include <stdio.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una cola de punteros genéricos. */
struct lista;
typedef struct lista lista_t;

/*El iterador externo apunta a una lista de punteros genéricos*/
struct lista_iter;
typedef struct lista_iter lista_iter_t;



/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al inicio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Borra el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);


// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);


// Devuelve la cantidad de elementos que contiene la lista.
// Pre: la lista fue creada.
// Post: se devolvió la cantidad de elementos de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));



/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador de listas.
// Post: devuelve una nuevo iterador de listas apuntando al primer elemento de la lista.
lista_iter_t* lista_iter_crear(lista_t* lista);

//Si la lista está vacía, o el iterador se encuentra al final de la misma, devuelve false, 
//sino, el iterador se posiciona sobre el siguiente elemento en la lista y devuelve true.
//Pre: La lista fue creada. 
bool lista_iter_avanzar(lista_iter_t *iter);

//Retorna el elemento actual de la lista en donde se encuentre posicionado el iterador. Si la lista está vacía o el iterador está al final de la misma, devuelve NULL.
//Pre: La lista fue creada. 
//Post: Devuelve el elemento actual de la lista, a menos que la misma esté vacía.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Retorna true si el iterador se encuentra al final de la lista. Es decir, cuando el iterador ya no apunta a un elemento de la lista. Retorna false, si el iterador está posicionado sobre un elemento de la lista.
//Pre: La lista fue creada. 
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador de la lista. No libera la memoria de la lista.
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un elemento en la posicion de la lista sobre la que apunte el iterador. Si está al principio, actualiza el valor del primer elemento de la lista, si se encuentra al final, actualiza el valor del último elemento de la lista. Si se encuentra posicionado en cualquier otro elemento, inserta un elemento a la izquierda de donde se encuentre posicionado el iterador. Si la lista está vacia, inserta un elemento y actualiza el valor tanto del ultimo elemento como del primero de la lista.
//Pre: La lista fue creada.
//Post: inserta un elemento en la posicion de la lista en que se encuentre el iterador.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra un elemento en la posicion de la lista sobre la que apunte el iterador. Si está al principio, actualiza el valor del primer elemento de la lista. Si se encuentra al final, actualiza el valor del último elemento de la lista. En cualquier otra posición, elimina el elemento sobre el que se encuentre posicionado el iterador. Si la lista está vacía, retorna NULL.
//Pre: La lista fue creada.
//Post: borra un elemento en la posicion de la lista en que se encuentre el iterador. Si la lista está vacia retorna NULL.
void *lista_iter_borrar(lista_iter_t *iter);



/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

//recorre la lista hasta el final, ejecutando la funcion visitar para cada elemento.
//Pre: La lista está creada
//post: La lista es recorrida hasta el final.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);
