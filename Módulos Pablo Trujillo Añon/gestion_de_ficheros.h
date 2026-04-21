#ifndef GESTION_DE_FICHEROS_H
#define GESTION_DE_FICHEROS_H

#include "logica.h"

/*
 * Cabecera: Inicializa todas las estructuras de datos del juego
 * Pre-condición: juego debe ser un puntero válido a EstadoJuego
 * Post-condición: Las estructuras están inicializadas y listas para usar
 */
void inicializar_datos(EstadoJuego *juego);

/*
 * Cabecera: Libera toda la memoria dinámica del estado del juego
 * Pre-condición: juego debe ser un puntero válido a EstadoJuego
 * Post-condición: Toda la memoria dinámica es liberada
 */
void liberar_datos(EstadoJuego *juego);

/*
 * Cabecera: Carga todos los ficheros necesarios para el juego
 * Pre-condición: juego debe ser un puntero válido a EstadoJuego
 * Post-condición: Los datos de salas, conexiones, objetos y puzles están cargados en juego
 */
void cargar_ficheros_juego(EstadoJuego *juego);

#endif