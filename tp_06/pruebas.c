#include <stdio.h>
#include "strutil.h"
#include <stdlib.h>
#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <string.h>

int main(){
    char* cadena = "mauro";
    char* cadena2 = substr(cadena, 2);    
    printf("%s, %s\n", cadena, cadena2);
    free(cadena2);
    
    
    char* hola_mundo = substr("Hola mundo", 6);
    printf("%s\n", hola_mundo);
    free(hola_mundo);
    
    const char* ejemplo = "Ejemplo";
    char* ejemplo2 = substr(ejemplo + 2, 2);
    printf("prueba %s\n", ejemplo2);
    free(ejemplo2);
    char* prueba_nulo = substr("", 2);
    printf("%s\n", prueba_nulo);
    free(prueba_nulo);
    char* prueba_algoritmos = substr("Algoritmos", 30);
    printf("%s\n", prueba_algoritmos);
    free(prueba_algoritmos);
    
    char* cadena_split = "Ahora estoy probando cómo levanta una cadena";
    printf("%s\n",cadena_split);
    char* cadena_split2 = substr(&cadena_split[1], 3);
    printf("%s\n", cadena_split2);    
    printf("%c\n",cadena_split[1]);
    printf("%c\n",cadena_split[3]);
    free(cadena_split2);
 char sep = ',';   
    char** arreglo = split("abc,def,ghi", sep);    
    printf("arreglo\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", arreglo[i] == NULL ? "NULL" : arreglo[i]);
    }    
    
    char** arreglo2 = split("abc,,def", ',');  //→  ["abc", "", "def"]
    printf("arreglo2\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", arreglo2[i] == NULL ? "NULL" : arreglo2[i]);
    }
    char** arreglo3 = split("abc,def,", ',');  //→  ["abc", "def", ""]
    printf("arreglo3\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", arreglo3[i] == NULL ? "NULL" : arreglo3[i]);
    }
    char** arreglo4 = split(",abc,def", ',');  //→  ["", "abc", "def"]
    printf("arreglo4\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", arreglo4[i] == NULL ? "NULL" : arreglo4[i]);
    }
    char** arreglo5 = split("abc", '\0');      //→  ["abc"]
    printf("arreglo5\n");
    for (int i = 0; i < 2; i++) {
        printf("%s\n", arreglo5[i] == NULL ? "NULL" : arreglo5[i]);
    }
    
    char** arreglo6 = split("", ',');  //→  [""]
    printf("arreglo6\n");
    for (int i = 0; i < 2; i++) {
        printf("%s\n", arreglo6[i] == NULL ? "NULL" : arreglo6[i]);
    }
    char** arreglo7 = split(",", ','); //→  ["", ""]
    printf("arreglo7\n");
    for (int i = 0; i < 3; i++) {
        printf("%s\n", arreglo7[i] == NULL ? "NULL" : arreglo7[i]);
    }
    
    size_t pos = 0;
    while (arreglo7[pos]) {
        printf("con un while: %s\n", arreglo7[pos] == NULL ? "NULL" : arreglo7[pos]);
        pos++;
    }
    sep = ';';
    char* arreglo_string = join(arreglo, sep);
    printf("%s\n", arreglo_string == NULL ? "NULL" : arreglo_string);
    free(arreglo_string);
    
    char* arreglo_string2 = join(arreglo2, ';');
    printf("%s\n", arreglo_string2 == NULL ? "NULL" : arreglo_string2);
    free(arreglo_string2);
    
    char* arreglo_string3 = join(arreglo3, ';');
    printf("%s\n", arreglo_string3 == NULL ? "NULL" : arreglo_string3);
    free(arreglo_string3);
    
    char* arreglo_string4 = join(arreglo4, ';');
    printf("%s\n", arreglo_string4 == NULL ? "NULL" : arreglo_string4);
    free(arreglo_string4);
    
    char* arreglo_string5 = join(arreglo5, ';');
    printf("%s\n", arreglo_string5 == NULL ? "NULL" : arreglo_string5);
    free(arreglo_string5);
    
    char* arreglo_string6 = join(arreglo6, ';');
    printf("%s\n", arreglo_string6 == NULL ? "NULL" : arreglo_string6);    
    free(arreglo_string6);
    
    char* arreglo_string7 = join(arreglo7, ';');
    printf("%s\n", arreglo_string7 == NULL ? "NULL" : arreglo_string7);
    free(arreglo_string7);
    
    free_strv(arreglo);    
    free_strv(arreglo2);
    free_strv(arreglo3);
    free_strv(arreglo4);
    free_strv(arreglo5);
    free_strv(arreglo6);
    free_strv(arreglo7);
    
    return 0;
}
