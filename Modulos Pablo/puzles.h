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

/**
 * Función: resolver_puzzle_actual
 * Descripción: Resuelve el puzzle en la sala actual del juego
 * 
 * Precondiciones:
 *   - juego debe ser un puntero válido a una estructura EstadoJuego_s
 *   - El estado del juego debe contener una sala actual válida
 *   - Debe existir un puzzle asociado a la sala actual
 * 
 * Postcondiciones:
 *   - Se actualiza el estado del puzzle correspondiente en juego
 *   - El campo resuelto del puzzle se marca según el resultado
 *   - El estado del juego puede modificarse para reflejar el avance
 */
void resolver_puzzle_actual(struct EstadoJuego_s *juego);

#endif