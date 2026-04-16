#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa(){
    printf("\n[Presiona ENTER para continuar...]");
    limpiarBuffer();
}
