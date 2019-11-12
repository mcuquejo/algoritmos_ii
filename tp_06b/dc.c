#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "strutil.h"

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
