#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilidades.h"

void limpiar_buffer() {
    while (getchar() != '\n');
}

void quitar_salto_linea(char* cadena) {
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

void a_mayusculas(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        cadena[i] = toupper(cadena[i]);
    }
}

void mostrar_error(char* mensaje) {
    printf("\n[!] ERROR: %s\n", mensaje);
}