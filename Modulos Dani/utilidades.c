// Includes para entrada/salida, strings, memoria y header de utilidades
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lee y descarta caracteres hasta nueva línea o EOF
}

// Función para limpiar la pantalla de la consola
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Comando para Windows
    #else
        system("clear"); // Comando para Unix/Linux
    #endif
}

// Función para pausar la ejecución hasta que el usuario presione ENTER
void pausa() {
    printf("\n[Presiona ENTER para continuar...]");
    limpiarBuffer(); // Espera a que se presione ENTER
}