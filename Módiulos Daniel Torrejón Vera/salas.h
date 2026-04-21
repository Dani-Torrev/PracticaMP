#ifndef SALAS_H
#define SALAS_H

// Hemos duplicado el espacio de memoria para descripciones largas
typedef struct {
    char id_sala[5];       
    char nombre[50];       
    char tipo[20];         
    char descripcion[200]; 
} Sala;

/*
 * Cabecera: Imprime los datos de una sala en pantalla
 * Pre-condición: Ninguna (estructura por valor)
 * Post-condición: Los datos de la sala se muestran en pantalla
 */
void imprimir_datos_sala(Sala s);

/*
 * Cabecera: Verifica si una sala es la sala final del juego
 * Pre-condición: Ninguna (estructura por valor)
 * Post-condición: Retorna 1 si es la sala final, 0 en caso contrario
 */
int es_sala_final(Sala s);

#endif