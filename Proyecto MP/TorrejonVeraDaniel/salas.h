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
void imprimir_datos_sala(Sala s);
int es_sala_final(Sala s);

#endif