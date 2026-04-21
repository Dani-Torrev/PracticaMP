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

/*
 * Cabecera: Inicializa todas las estructuras de datos del juego
 * Pre-condición: juego debe ser un puntero válido a EstadoJuego
 * Post-condición: Las estructuras están inicializadas, todos los punteros establecidos
 */
void inicializar_datos(EstadoJuego *juego);

/*
 * Cabecera: Libera toda la memoria dinámica del estado del juego
 * Pre-condición: juego debe ser un puntero válido a EstadoJuego
 * Post-condición: Toda la memoria asociada al juego es liberada
 */
void liberar_datos(EstadoJuego *juego);

#endif