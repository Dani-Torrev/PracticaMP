#ifndef UTILIDADES_H
#define UTILIDADES_H

/**
 * Función: limpiarPantalla
 * Descripción: Limpia el contenido mostrado en la consola
 * 
 * Precondiciones:
 *   - Ninguna
 * 
 * Postcondiciones:
 *   - La pantalla de la consola queda limpia
 */
void limpiarPantalla();

/**
 * Función: limpiarBuffer
 * Descripción: Limpia el buffer de entrada de teclado
 * 
 * Precondiciones:
 *   - Ninguna
 * 
 * Postcondiciones:
 *   - El buffer de entrada queda vacío
 */
void limpiarBuffer();

/**
 * Función: pausa
 * Descripción: Pausa la ejecución hasta que el usuario presione una tecla
 * 
 * Precondiciones:
 *   - Ninguna
 * 
 * Postcondiciones:
 *   - Se espera la interacción del usuario
 *   - La ejecución continúa tras pulsar una tecla
 */
void pausa();

#endif