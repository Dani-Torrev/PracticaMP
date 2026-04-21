#include <stdio.h>
#include <string.h>
#include "salas.h"

// Imprime los datos de una sala en pantalla
void imprimir_datos_sala(Sala s) {
 // Muestra el ID y nombre de la sala
 printf("\n[%s]- %s\n", s.id_sala, s.nombre);
 // Muestra el tipo de sala
 printf("Tipo: %s\n", s.tipo);
 // Muestra la descripción detallada
 printf("Descripcion: %s\n", s.descripcion);
}

// Verifica si una sala es la sala final del juego
int es_sala_final(Sala s)
{
      // Comprueba si el tipo de sala es "SALIDA"
      return (strcmp(s.tipo, "SALIDA") == 0);
}
