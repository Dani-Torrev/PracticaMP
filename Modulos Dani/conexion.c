// Includes para entrada/salida, strings y header de conexiones
#include <stdio.h>
#include <string.h>
#include "conexion.h"

// Función para comprobar si el estado de la conexión es "Activa"
int esta_abierta(Conexion c) {
    // strcmp devuelve 0 si las cadenas son iguales
    if (strcmp(c.estado, "Activa") == 0) {
        return 1; // Está abierta
    }
    return 0; // No está abierta
}

// Función para cambiar el estado de la conexión a "Activa" mediante un puntero
void abrir_paso(Conexion *c) {
    if (c != NULL) {
        strcpy(c->estado, "Activa"); // Cambiamos el estado
        printf("[INFO] La conexion %s ahora esta Activa.\n", c->id_conexion);
    }
}

// Función para comparar si la condición de la conexión coincide con un ID de objeto
int requiere_objeto(Conexion c, char* id_objeto) {
    if (strcmp(c.condicion, id_objeto) == 0) {
        return 1; // Requiere ese objeto
    }
    return 0; // No requiere ese objeto
}

// Función para comparar si la condición coincide con un ID de puzzle
int tiene_puzzle(Conexion c, char* id_puzzle) {
    if (strcmp(c.condicion, id_puzzle) == 0) {
        return 1; // Tiene ese puzzle
    }
    return 0; // No tiene ese puzzle
}