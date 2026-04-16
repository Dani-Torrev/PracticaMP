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

/**
 * Función: inicializar_datos
 * Descripción: Inicializa la estructura de estado del juego
 * 
 * Precondiciones:
 *   - juego debe ser un puntero válido a una estructura EstadoJuego
 * 
 * Postcondiciones:
 *   - Se inicializan los campos de juego con valores por defecto
 *   - El estado queda listo para cargar datos y usarse en el juego
 */
void inicializar_datos(EstadoJuego *juego);

/**
 * Función: liberar_datos
 * Descripción: Libera la memoria y recursos asociados al estado del juego
 * 
 * Precondiciones:
 *   - juego debe ser un puntero válido a una estructura EstadoJuego previamente inicializada
 * 
 * Postcondiciones:
 *   - Se liberan los recursos dinámicos asociados a juego
 *   - La estructura juego queda en un estado no válido para uso posterior sin reinicialización
 */
void liberar_datos(EstadoJuego *juego);

#endif