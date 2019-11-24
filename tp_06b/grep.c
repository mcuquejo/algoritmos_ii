#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cola.h"
#include "strutil.h"

char* strdup (const char* s) {
    char* dup = malloc(strlen (s) + 1);
    if (dup == NULL)
        return NULL;
    strcpy(dup,s);
    return dup;
}

size_t fnv_hash(const char *clave, size_t largo) {
    size_t h = 14695981039346656037U;
    size_t n = strlen(clave);
    for (size_t i = 0; i < n; i++) {
        h *= 1099511628211;
        h ^= (size_t)clave[i];
    }
    return h % largo;
}

void* rabin_karp(char* s, char* pattern) {
    size_t largo_s = strlen(s);
    size_t largo_pattern = strlen(pattern);
    size_t hpattern = fnv_hash(pattern, largo_pattern);
    char* tam = s + (largo_s - largo_pattern + 1);
    for (char* i = s; i < tam; ++i) {
        char* cadena = substr(i, largo_pattern);
        size_t hs = fnv_hash(cadena, largo_pattern);
        if (hs == hpattern) {
            if (strncmp(cadena, pattern, largo_pattern) == 0) {
                free(cadena);
                return i;
            }
        }
        free(cadena);
    }
    return NULL;
}

int procesar_archivo(char* cadena, int n, char* arch) {
    FILE* archivo = fopen(arch,"r");
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo\n");
        return 1;
    }
    cola_t* buffer = cola_crear();
    if (buffer == NULL) {
        fprintf(stderr, "Falló la creación del buffer\n");
        return 1;
    }
    char* linea = NULL;
    size_t capacidad = 0;
    size_t cont_contexto = 0;
    while (getline(&linea, &capacidad, archivo) != EOF) {
        if (strlen(linea) > 0) {
            char* linea_aux = strdup(linea);
            cola_encolar(buffer, linea_aux);
        }
        cont_contexto++;
        if (cont_contexto > n + 1) {
            void* linea_aux = cola_desencolar(buffer);
            free(linea_aux);
        }
        char* coincidencia = rabin_karp(linea, cadena);
        if (coincidencia != NULL) {
            while (cola_esta_vacia(buffer) == false) {
                void* linea_aux = cola_desencolar(buffer);
                fprintf(stdout, "%s", (char*)linea_aux);
                free(linea_aux);
                cont_contexto = 0;
            }
        }
    }
    cola_destruir(buffer, free);
    free(linea);
    fclose(archivo);
    return 0;
}

int procesar_stdin(char* cadena, int n) {
    cola_t* buffer = cola_crear();
    if (buffer == NULL) {
        fprintf(stderr, "Falló la creación del buffer\n");
        return 1;
    }
    char* linea = NULL;
    size_t capacidad = 0;
    size_t cont_contexto = 0;
    while (getline(&linea, &capacidad, stdin) != EOF) {
        if (strlen(linea) > 0) {
            char* linea_aux = strdup(linea);
            cola_encolar(buffer, linea_aux);
        }
        cont_contexto++;
        if (cont_contexto > n + 1) {
            void* linea_aux = cola_desencolar(buffer);
            free(linea_aux);
        }
        char* coincidencia = rabin_karp(linea, cadena);
        if (coincidencia != NULL) {
            while (cola_esta_vacia(buffer) == false) {
                void* linea_aux = cola_desencolar(buffer);
                fprintf(stdout, "%s", (char*)linea_aux);
                free(linea_aux);
                cont_contexto = 0;
            }
        }
    }
    cola_destruir(buffer, free);
    free(linea);
    return 0;
}

int grep(char* cadena, int n, char* archivo) {
    int resultado = 0;
    if(strncmp(archivo, "", 1) != 0) {
        resultado = procesar_archivo(cadena, n, archivo);
    } else {
        resultado = procesar_stdin(cadena, n);
    }
    if (resultado == 1) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc <= 2 || argc > 4) {
        fprintf(stderr, "Cantidad de parametros erronea\n");
        return 1;
    }
    if (argc == 4) {
        grep(argv[1], atoi(argv[2]), argv[3]);
    } else if (argc == 3) {
        grep(argv[1], atoi(argv[2]), "");
    }
    return 0;
}
