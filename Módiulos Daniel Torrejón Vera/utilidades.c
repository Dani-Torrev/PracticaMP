#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"

// Limpia el buffer de entrada estándar
void limpiarBuffer() {
    int c;
    // Lee y descarta todos los caracteres hasta encontrar salto de línea
    while ((c = getchar()) != '\n' && c != EOF);
}

// Limpia la pantalla del terminal
void limpiarPantalla() {
    // Usa comando diferente según el sistema operativo
    #ifdef _WIN32
        system("cls");  // Comando Windows
    #else
        system("clear"); // Comando Unix/Linux
    #endif
}

// Pausa la ejecución del programa hasta que el usuario presione Enter
void pausa(){
    printf("\n[Presiona ENTER para continuar...]");
    // Limpia el buffer y espera entrada del usuario
    limpiarBuffer();
}
