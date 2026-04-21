#ifndef PUZLES_H
#define PUZLES_H

#include "stdbool.h"

typedef struct {
    char id_puzzle[5];
    char nomb_puzle[30];
    char id_sala[5];
    char tipo[20];
    char descrip[200];
    char solucion[51]; // 50 letras para la respuesta
    bool resuelto;
} Puzle;

struct EstadoJuego_s;

/*
 * Cabecera: Resuelve el puzle actual del juego
 * Pre-condición: juego no debe ser NULL y debe tener un estado válido
 * Post-condición: Si la solución es correcta, el puzle se marca como resuelto
 */
void resolver_puzzle_actual(struct EstadoJuego_s *juego);

#endif