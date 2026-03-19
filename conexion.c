#include <stdio.h>
#include <string.h>
#include "conexion.h"

// Comprueba si el estado de la conexión es "Activa"
int esta_abierta(Conexion c) {
    // strcmp devuelve 0 si las cadenas son iguales
    if (strcmp(c.estado, "Activa") == 0) {
        return 1; 
    }
    return 0; 
}
// Cambia el estado de la conexión mediante un puntero
void abrir_paso(Conexion *c) {
    if (c != NULL) {
        strcpy(c->estado, "Activa");
        printf("[INFO] La conexion %s ahora esta Activa.\n", c->id_conexion);
    }
}

// Compara si la condicion de la conexion coincide con un ID de objeto
int requiere_objeto(Conexion c, char* id_objeto) {
    if (strcmp(c.condicion, id_objeto) == 0) {
        return 1;
    }
    return 0; 
}

// Compara si la condicion coincide con un ID de puzzle
int tiene_puzzle(Conexion c, char* id_puzzle) {
    if (strcmp(c.condicion, id_puzzle) == 0) {
        return 1; 
    }
    return 0; 
}