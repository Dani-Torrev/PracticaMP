#ifndef GESTION_DE_FICHEROS_H
#define GESTION_DE_FICHEROS_H

#include "logica.h"

/**
 * Función: inicializar_datos
 * Descripción: Inicializa el estado del juego antes de cargar datos
 * 
 * Precondiciones:
 *   - juego debe ser un puntero válido a una estructura EstadoJuego
 * 
 * Postcondiciones:
 *   - El estado del juego queda inicializado en valores por defecto
 *   - La estructura juego queda lista para cargar datos adicionales
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
 *   - Se liberan los recursos asociados a juego
 *   - La estructura juego queda en un estado no válido para uso posterior sin reinicialización
 */
void liberar_datos(EstadoJuego *juego);

/**
 * Función: cargar_ficheros_juego
 * Descripción: Carga los datos del juego desde los ficheros correspondientes
 * 
 * Precondiciones:
 *   - juego debe ser un puntero válido a una estructura EstadoJuego inicializada
 *   - Los ficheros de datos deben existir en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - El estado del juego se actualiza con los datos leídos
 *   - Devuelve control al llamador después de completar la carga o detectar un error
 */
void cargar_ficheros_juego(EstadoJuego *juego);

#endif
