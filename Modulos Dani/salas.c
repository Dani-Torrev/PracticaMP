#include <stdio.h>
#include <string.h>
#include "salas.h"

void imprimir_datos_sala(Sala s) {
 printf("\n[%s]- %s\n", s.id_sala, s.nombre);
 printf("Tipo: %s\n", s.tipo);
 printf("Descripcion: %s\n", s.descripcion);
}

int es_sala_final(Sala s)
{
      return (strcmp(s.tipo, "SALIDA") == 0);
}
