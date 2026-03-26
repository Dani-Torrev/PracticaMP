#ifndef PUZLES_H
#define PUZLES_H

#include "stdbool.h"

typedef structu {
    char id_puzzle[4];
    char nomb_puzle[16];
    int id_sala;
    char tipo[20];
    char descrip[151];
    charsolucion[51];
    bool resuelto;
} Puzle;

struct EstadoJuego_s;

void resolver_puzzle_actual(struct EstadoJuego *juego);

#endif
