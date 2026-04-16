#ifndef SALAS_H
#define SALAS_H

// Estructura para las salas 
typedef struct {
    char id_sala[3];       
    char nombre[31];       
    char tipo[10];         
    char descripcion[151]; 
} Sala;

// Prototipos de funciones

/**
 * Función: imprimir_datos_sala
 * Descripción: Imprime la información de una sala
 * 
 * Precondiciones:
 *   - s debe ser una estructura Sala válida
 * 
 * Postcondiciones:
 *   - Se muestra por pantalla la información contenida en s
 *   - La estructura s no se modifica
 */
void imprimir_datos_sala(Sala s);

/**
 * Función: es_sala_final
 * Descripción: Comprueba si una sala es de tipo final
 * 
 * Precondiciones:
 *   - s debe ser una estructura Sala válida
 * 
 * Postcondiciones:
 *   - Devuelve 1 si s es una sala final, 0 en caso contrario
 *   - La estructura s no se modifica
 */
int es_sala_final(Sala s);

#endif