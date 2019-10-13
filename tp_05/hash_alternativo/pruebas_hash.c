#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_INICIAL 4
#define CARGA_MAX 0.7
#define CARGA_MIN 0.3
#define FACTOR_REDIMENSION 2

enum estado {VACIO = 0, OCUPADO = 1, BORRADO = 2};

typedef void (*hash_destruir_dato_t)(void *);

typedef struct hash_campo {
    char* clave;
    void* valor;
    size_t estado;
} hash_campo_t;

typedef struct hash {
    size_t capacidad;
    size_t cantidad;
    hash_destruir_dato_t funcion_destruccion;
    hash_campo_t* campo;
} hash_t;

typedef struct hash_iter {
    const hash_t* hash;
    hash_campo_t* campo_act;
    hash_campo_t* campo_ant;
} hash_iter_t;


size_t fhash(const char *clave, size_t largo){
    size_t suma;

    for (suma = 0; *clave != '\0'; clave++)
        suma = (size_t)*clave + 31 * suma;
    return suma % largo;
}

size_t fnv_hash(const char *clave, size_t largo){
    size_t h = 14695981039346656037U;
    size_t n = strlen(clave);
    for (size_t i = 0; i < n; i++){
        h *= 1099511628211;
        h ^= (size_t)clave[i];
    }
    return h % largo;
}

char* strdup (const char* s) {
	char* dup = malloc(strlen (s)+1);
	if (dup == NULL)
		return NULL;
  strcpy(dup,s);
	return dup;
}

void inicializar_campos(hash_campo_t* campo, size_t tam) {
    for (size_t i = 0; i < tam; i++) {
        campo[i].clave = NULL;
        campo[i].valor = NULL;
        campo[i].estado = VACIO;
    }
}

void actualizar_campo(hash_campo_t* campo, const char* clave, void* dato, size_t estado,hash_destruir_dato_t funcion_destruccion){
	if (clave != NULL) {
		campo->clave = strdup(clave);
	} else {
		campo->clave = NULL;
	}
	if (funcion_destruccion != NULL) {
		funcion_destruccion(campo->valor);
	}
	campo->valor = dato;
	campo->estado = estado;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato);

//para redimensionar segun factor de carga.
bool hash_redimensionar(hash_t* hash, size_t tam) {
    hash_campo_t* campos_nuevo = calloc(tam, sizeof(hash_campo_t));
    if (campos_nuevo == NULL) {
		return false;
	}
    hash_campo_t* campos_act = hash->campo;
	size_t tam_actual = hash->capacidad;
	hash->capacidad = tam;
	hash->cantidad = 0;
    hash->campo = campos_nuevo;
    inicializar_campos(hash->campo, hash->capacidad);
	
    for (size_t i = 0; i < tam_actual; i++) {
        if (campos_act[i].estado == OCUPADO) {
			bool r_exitoso = hash_guardar(hash, campos_act[i].clave, campos_act[i].valor);
			if (!r_exitoso) {
				return false;
			}
			if (hash->funcion_destruccion != NULL) {
				hash->funcion_destruccion(campos_act[i].valor);
			}			
        }
        free(campos_act[i].clave);
    }
    free(campos_act);
    return true;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) {
        return NULL;
    }
    hash->cantidad = 0;
    hash->capacidad = TAM_INICIAL;
    hash->funcion_destruccion = destruir_dato;
    hash->campo = calloc(TAM_INICIAL, sizeof(hash_campo_t));
    if (hash->campo == NULL) {
        return NULL;
    }
    inicializar_campos(hash->campo, TAM_INICIAL);
    return hash;
}

//para evitar colisiones.
int funcion_dispersion(size_t pos_ini, const hash_t* hash, const char *clave, bool insercion) {
	int pos = (int) pos_ini;
	while (true) {
		pos = (pos + 1) % (int)hash->capacidad;
		if (insercion) {
			if (hash->campo[pos].estado == VACIO) {
				return pos;
			}
		} else {
			if (hash->campo[pos].estado == VACIO) {
				break;
			}			
			if (strcmp(hash->campo[pos].clave, clave) == 0) {
				return pos;
			}
		}
		if (pos == pos_ini) {
			break;
		}
	}
	return -1;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    size_t pos = fnv_hash(clave, hash->capacidad);
    
    if (hash->campo[pos].estado == VACIO || hash->campo[pos].estado == BORRADO) {
		free(hash->campo[pos].clave);
        actualizar_campo(&hash->campo[pos], clave, dato, OCUPADO, hash->funcion_destruccion);
    } else if (hash->campo[pos].estado == OCUPADO && strcmp(hash->campo[pos].clave, clave) == 0) {
		actualizar_campo(&hash->campo[pos], NULL, dato, OCUPADO, hash->funcion_destruccion);
	} else {
		int pos_nueva = funcion_dispersion(pos, hash, clave, true);
		if (pos_nueva < 0) {
			return false;
		}
		free(hash->campo[pos_nueva].clave);
		actualizar_campo(&hash->campo[pos_nueva], clave, dato, OCUPADO, hash->funcion_destruccion);
		
	}
	hash->cantidad++;
	if (((double)hash->cantidad)/(double)hash->capacidad >= CARGA_MAX) {
		hash_redimensionar(hash, hash->capacidad * FACTOR_REDIMENSION);
	}
    return true;
}

size_t hash_cantidad(const hash_t *hash){
	return hash->cantidad;
}

int hash_obtener_posicion(const hash_t *hash, const char *clave){
	size_t pos = fnv_hash(clave, hash->capacidad);    
    if (hash->campo[pos].estado == VACIO) {
		return -1;
    }
    if (hash->campo[pos].estado == OCUPADO && strcmp(hash->campo[pos].clave, clave) == 0) {
		return (int)pos;
	}
	return funcion_dispersion(pos, hash, clave, false);
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	return hash_obtener_posicion(hash, clave) > 0 ? true : false;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	int pos = hash_obtener_posicion(hash, clave);
	return pos > 0 ? hash->campo[pos].valor : NULL;
}

void *hash_borrar(hash_t *hash, const char *clave){
	int pos = hash_obtener_posicion(hash, clave);
	if (pos < 0) {
		return NULL;
	}
	
	void* dato = hash->campo[pos].valor;
	free(hash->campo[pos].clave);
	actualizar_campo(&hash->campo[pos], NULL, NULL, BORRADO, hash->funcion_destruccion);
	return dato;
}

void hash_destruir(hash_t *hash) {
  for (size_t i = 0; i < hash->capacidad; i++) {
    if (hash->campo[i].estado != OCUPADO) continue;
    if (hash->funcion_destruccion != NULL){
      hash->funcion_destruccion(hash->campo[i].valor);
    }
    free(hash->campo[i].clave);
  }
  free(hash->campo);
  free(hash);
}

int main() {
	char* clave = "pepe";
	char* clave2 = "pepa";
	char* clave3 = "pepo";
	char* clave4 = "adamantio";

	printf("hash devuelto: %zu\n", fhash(clave, TAM_INICIAL));
	printf("hash devuelto: %zu\n", fhash(clave2, TAM_INICIAL));
	printf("hash devuelto: %zu\n", fhash(clave3, TAM_INICIAL));
	printf("hash devuelto: %zu\n", fhash(clave4, TAM_INICIAL));

	printf("\n\nhash devuelto con fnv: %zu\n", fnv_hash(clave, TAM_INICIAL));
	printf("hash devuelto con fnv: %zu\n", fnv_hash(clave2, TAM_INICIAL));
	printf("hash devuelto con fnv: %zu\n", fnv_hash(clave3, TAM_INICIAL));
	printf("hash devuelto con fnv: %zu\n", fnv_hash(clave4, TAM_INICIAL));

	hash_t* diccionario_prueba = hash_crear(NULL);
	printf("\n\ndiccionario_prueba.capacidad: %zu\n", diccionario_prueba->capacidad);
	printf("diccionario_prueba.cantidad: %zu\n", hash_cantidad(diccionario_prueba));
	printf("diccionario_prueba.funcion_destruccion: %s\n", (diccionario_prueba->funcion_destruccion == NULL) ? "NULL" : "FUNCION NO NULA");

	printf("\n\n");
	for (size_t i = 0; i < TAM_INICIAL; i++){
		printf("diccionario_prueba.campo[%zu].clave: %s\n", i, (diccionario_prueba->campo[i].clave == NULL) ? "NULL" : diccionario_prueba->campo[i].clave);
	}
/*
 * lo comento para poder probar lo mismo con la funcion guardar.
	diccionario_prueba->campo[fnv_hash(clave, TAM_INICIAL)].clave = clave;
	diccionario_prueba->campo[fnv_hash(clave2, TAM_INICIAL)].clave = clave2;
	diccionario_prueba->campo[fnv_hash(clave3, TAM_INICIAL)].clave = clave3;
	diccionario_prueba->campo[fnv_hash(clave4, TAM_INICIAL)].clave = clave4;
*/
	hash_guardar(diccionario_prueba, clave, "clave 1");
	hash_guardar(diccionario_prueba, clave2, "clave 2");
	hash_guardar(diccionario_prueba, clave3, "clave 3");
	hash_guardar(diccionario_prueba, clave4, "clave 4");

	printf("\n\nPRUEBA PERTENECE:\n");
	printf("pepe es una clave?: %s\n", hash_pertenece(diccionario_prueba, "pepe") ? "TRUE" : "FALSE");
	printf("pepa es una clave?: %s\n", hash_pertenece(diccionario_prueba, "pepa") ? "TRUE" : "FALSE");
	printf("pepo es una clave?: %s\n", hash_pertenece(diccionario_prueba, "pepo") ? "TRUE" : "FALSE");
	printf("adamantio es una clave?: %s\n", hash_pertenece(diccionario_prueba, "adamantio") ? "TRUE" : "FALSE");
	printf("pipo es una clave?: %s\n", hash_pertenece(diccionario_prueba, "pipo") ? "TRUE" : "FALSE");

	printf("\n\nPRUEBA OBTENER:\n");
	void* valor_campo_diccionario = hash_obtener(diccionario_prueba, "pepe");
	printf("valor pepe: %s\n", (char*)valor_campo_diccionario);
	valor_campo_diccionario = hash_obtener(diccionario_prueba, "pipo");
	printf("valor pipo (no existe la clave): %s\n", valor_campo_diccionario == NULL ? "NULL" : (char*)valor_campo_diccionario);
	
	
	printf("\n\ndiccionario_prueba.capacidad: %zu\n", diccionario_prueba->capacidad);
	printf("diccionario_prueba.cantidad: %zu\n", hash_cantidad(diccionario_prueba));
	printf("diccionario_prueba.funcion_destruccion: %s\n", (diccionario_prueba->funcion_destruccion == NULL) ? "NULL" : "FUNCION NO NULA");
	printf("\n\n");
	for (size_t i = 0; i < diccionario_prueba->capacidad; i++){
		printf("**************\n");
		printf("diccionario_prueba.campo[%zu].clave: %s\n", i, (diccionario_prueba->campo[i].clave == NULL) ? "NULL" : diccionario_prueba->campo[i].clave);
		printf("diccionario_prueba.campo[%zu].valor: %s\n", i, (diccionario_prueba->campo[i].valor == NULL) ? "NULL" : (char*)diccionario_prueba->campo[i].valor);
		char* convertir_estado;
		if (diccionario_prueba->campo[i].estado == 0) {
			convertir_estado = "VACIO";
		} else if (diccionario_prueba->campo[i].estado == 1) {
			convertir_estado = "OCUPADO";
		} else if (diccionario_prueba->campo[i].estado == 2) {
			convertir_estado = "BORRADO";
		} else {
			convertir_estado = "EL CAMPO POR ALGUN MOTIVO ESTA VACIO";
		}
		printf("diccionario_prueba.campo[%zu].estado: %s\n", i, convertir_estado);
		printf("**************\n");
	}
	printf("\n\nPRUEBA BORRAR:\n");
	void* dato_borrado = hash_borrar(diccionario_prueba, "adamantio");
	printf("valor adamantio borrado: %s\n", (char*)dato_borrado);
	dato_borrado = hash_obtener(diccionario_prueba, "pipo");
	printf("valor pipo borrado (no existe la clave): %s\n", dato_borrado == NULL ? "NULL" : (char*)dato_borrado);

	printf("\n\n");
	for (size_t i = 0; i < diccionario_prueba->capacidad; i++){
		printf("**************\n");
		printf("diccionario_prueba.campo[%zu].clave: %s\n", i, (diccionario_prueba->campo[i].clave == NULL) ? "NULL" : diccionario_prueba->campo[i].clave);
		printf("diccionario_prueba.campo[%zu].valor: %s\n", i, (diccionario_prueba->campo[i].valor == NULL) ? "NULL" : (char*)diccionario_prueba->campo[i].valor);
		char* convertir_estado;
		if (diccionario_prueba->campo[i].estado == 0) {
			convertir_estado = "VACIO";
		} else if (diccionario_prueba->campo[i].estado == 1) {
			convertir_estado = "OCUPADO";
		} else if (diccionario_prueba->campo[i].estado == 2) {
			convertir_estado = "BORRADO";
		} else {
			convertir_estado = "EL CAMPO POR ALGUN MOTIVO ESTA VACIO";
		}
		printf("diccionario_prueba.campo[%zu].estado: %s\n", i, convertir_estado);
		printf("**************\n");
	}

	hash_destruir(diccionario_prueba);
	
return 0;
}
