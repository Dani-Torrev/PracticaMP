#ifndef LOGICA_H
#define LOGICA_H

#include "salas.h"
#include "conexion.h"
#include "objetos.h"
#include "jugador.h"
#include "puzles.h"
#include "autentificacion.h"

typedef struct EstadoJuego_s {

    Sala *salas;
    int num_salas;
    Conexion *conexiones;
    int num_conexiones;
    Objeto *objetos;
    int num_objetos;
    Puzle *puzles;
    int num_puzles;
    Usuario *jugadores_bd;
    int num_jugadores_bd;
    Jugador *jugador_actual;
    char sala_actual_id[5];

} EstadoJuego;

void inicializar_datos(EstadoJuego *juego);
void liberar_datos(EstadoJuego *juego);

#endif