#ifndef UTILIDADES_H
#define UTILIDADES_H

/*
 * Cabecera: Limpia la pantalla del terminal
 * Pre-condición: Ninguna
 * Post-condición: La pantalla se limpia y el cursor se posiciona en el inicio
 */
void limpiarPantalla();

/*
 * Cabecera: Limpia el buffer de entrada estándar
 * Pre-condición: Puede haber caracteres pendientes en stdin
 * Post-condición: El buffer de entrada es vaciado
 */
void limpiarBuffer();

/*
 * Cabecera: Pausa la ejecución del programa hasta que el usuario presione Enter
 * Pre-condición: Ninguna
 * Post-condición: El programa continúa su ejecución después de que el usuario presione Enter
 */
void pausa();

#endif