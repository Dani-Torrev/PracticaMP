#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jugador.h"
#include "utilidades.h"

void inicializarJugador(JugadorActivo *j, int id, char *nombre, char *sala_inicio) {
    j->id_jugador = id;
    strncpy(j->nombre, nombre, MAX_NOMBRE_J - 1);
    strncpy(j->sala_actual, sala_inicio, MAX_ID_SALA - 1);
    j->inventario = NULL; 
    j->num_objetos = 0;
}

void actualizarPosicion(JugadorActivo *j, char *nueva_sala) {
    if (nueva_sala != NULL) {
        strncpy(j->sala_actual, nueva_sala, MAX_ID_SALA - 1);
    }
}

int añadirObjeto(JugadorActivo *j, char *id_obj) {
    char **aux = (char **)realloc(j->inventario, (j->num_objetos + 1) * sizeof(char *));
    
    if (aux != NULL) {
        j->inventario = aux;
        j->inventario[j->num_objetos] = (char *)malloc(MAX_ID_OBJ * sizeof(char));
        strncpy(j->inventario[j->num_objetos], id_obj, MAX_ID_OBJ - 1);
        j->num_objetos++;
        return 1;
    }
    return 0;
}

int quitarObjeto(JugadorActivo *j, char *id_obj) {
    int i, encontrado = -1;
    for (i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        free(j->inventario[encontrado]);
        for (i = encontrado; i < j->num_objetos - 1; i++) {
            j->inventario[i] = j->inventario[i + 1];
        }
        j->num_objetos--;
        j->inventario = (char **)realloc(j->inventario, j->num_objetos * sizeof(char *));
        return 1;
    }
    return 0;
}

int tieneObjeto(JugadorActivo *j, char *id_obj) {
    for (int i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) return 1;
    }
    return 0;
}

void liberarMemoriaJugador(JugadorActivo *j) {
    if (j->inventario != NULL) {
        for (int i = 0; i < j->num_objetos; i++) {
            free(j->inventario[i]);
        }
        free(j->inventario);
        j->inventario = NULL;
    }
}