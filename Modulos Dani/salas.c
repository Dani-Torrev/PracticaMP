// Includes para entrada/salida, strings y header de salas
#include <stdio.h>
#include <string.h>
#include "salas.h"

// Función para imprimir los datos de una sala
void imprimir_datos_sala(Sala s) {
    printf("\n[%s]- %s\n", s.id_sala, s.nombre); // Imprime ID y nombre
    printf("Tipo: %s\n", s.tipo); // Imprime el tipo
    printf("Descripcion: %s\n", s.descripcion); // Imprime la descripción
}

// Función para comprobar si una sala es la sala final (tipo "SALIDA")
int es_sala_final(Sala s) {
    return (strcmp(s.tipo, "SALIDA") == 0); // Devuelve 1 si es SALIDA, 0 si no
}