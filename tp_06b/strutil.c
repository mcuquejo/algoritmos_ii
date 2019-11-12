#ifndef STRUTIL_H
#define STRUTIL_H
#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#define CANT_MINIMA_SEP 2
#define CHAR_CORTE 1
void inicializar_datos(char* string, size_t n) {
    for (size_t i = 0; i < sizeof(char) * n + 1; i++) {
        string[i] = '\0';
    }
}

char *substr(const char *str, size_t n) {
    char* salida = malloc(sizeof(char) * n + CHAR_CORTE);    
    if (salida == NULL) {
        return NULL;
    }
    inicializar_datos(salida, n);
    strncpy(salida, str, n);
    return salida;
}

size_t contar_cant_elem_arreglo(const char *str, char sep) {
    size_t cant_elementos = CANT_MINIMA_SEP;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == sep) {
            cant_elementos++;
        }
    }
    return cant_elementos;
}

char **split(const char *str, char sep) {
    size_t cant_elementos = contar_cant_elem_arreglo(str, sep);    
    char** arreglo = malloc(sizeof(str) * cant_elementos);
    if (arreglo == NULL) {
        return NULL;
    }
    size_t i_arreglo = 0;
    size_t i_actual = 0;
    for (size_t i = 0; i <= strlen(str); i++) {
        if (str[i] == sep || str[i] == '\0') {
            size_t tam = i - i_actual;
            arreglo[i_arreglo] = substr(&str[i_actual], tam);
            if (i_arreglo < cant_elementos - 1) {
                i_arreglo++;
            }
            if (i < strlen(str)) {
                i_actual = i + 1;
            }
        }
    }
    arreglo[i_arreglo] = NULL;
    return arreglo;
}

size_t contar_cant_elem_str(char **strv) {
    size_t pos = 0;
    size_t contador = 0;
    while (strv[pos] != NULL) {
        contador++;
        pos++;
    }
    return contador;
}

size_t contar_largo_str(char **strv) {
    size_t pos = 0;
    size_t len = 0;
    while (strv[pos] != NULL) {
        len = len + strlen(strv[pos]) + CHAR_CORTE;
        pos++;
    }
    return len;
}

char *join(char **strv, char sep) {
    char separador[1] = "";
    separador[0] = sep;
    size_t pos = 0;
    size_t cant_sep = contar_cant_elem_str(strv);
    size_t len_strv = contar_largo_str(strv);    
    char* salida = malloc(sizeof(char) * len_strv + CHAR_CORTE);
    if (salida == NULL) {        
        return NULL;        
    }
    inicializar_datos(salida, len_strv);
    size_t final = 0;    
    while (strv[pos] != NULL) {
        if (strlen(strv[pos]) > 0) {
            strncpy(salida + final, strv[pos], strlen(strv[pos]));            
            final = final + strlen(strv[pos]);
        }        
        if(pos < cant_sep - 1) {
            strncpy(salida + final, &separador[0], strlen(&separador[0]));
            final = final + strlen(&separador[0]);
        }
        pos++;
    }    
    return salida;
}

void free_strv(char *strv[]){
    size_t pos = 0;
    while (strv[pos] != NULL) {
        free(strv[pos]);
        pos++;
    }
    free(strv);
}

#endif  // STRUTIL_H
