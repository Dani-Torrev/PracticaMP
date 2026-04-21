#include <stdio.h>
#include <string.h>
#include "conexion.h"

// Verifica si una conexión está abierta
int esta_abierta(Conexion c) {
    // Comprueba si el estado es "Activa"
    if (strcmp(c.estado, "Activa") == 0) {
        return 1; // Está abierta
    }
    return 0; // Está cerrada
}

// Abre una conexión entre salas
void abrir_paso(Conexion *c) {
    if (c != NULL) {
        // Cambia el estado a "Activa"
        strcpy(c->estado, "Activa");
        printf("[INFO] La conexion %s ahora esta Activa.\n", c->id_conexion);
    }
}

// Verifica si una conexión requiere un objeto específico para abrirse
int requiere_objeto(Conexion c, char* id_objeto) {
    // Compara la condición de la conexión con el ID del objeto
    if (strcmp(c.condicion, id_objeto) == 0) {
        return 1; // Requiere este objeto
    }
    return 0; // No requiere este objeto
}

// Verifica si una conexión tiene un puzle asociado
int tiene_puzzle(Conexion c, char* id_puzzle) {
    // Compara la condición de la conexión con el ID del puzle
    if (strcmp(c.condicion, id_puzzle) == 0) {
        return 1; // Tiene este puzle
    }
    return 0; // No tiene este puzle
}