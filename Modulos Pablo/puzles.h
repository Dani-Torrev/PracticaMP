#ifndef PUZLES_H
#define PUZLES_H

#include "stdbool.h"

typedef struct {
    char id_puzzle[4];
    char nomb_puzle[16];
    char id_sala[5];
    char tipo[20];
    char descrip[151];
    char solucion[51];
    bool resuelto;
} Puzle;

struct EstadoJuego_s;

void resolver_puzzle_actual(struct EstadoJuego_s *juego);

#endif
