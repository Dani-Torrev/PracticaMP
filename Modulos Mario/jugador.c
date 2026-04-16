#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"

void inicializarJugador(Jugador *j, int id, char *nombre, char *sala_inicio) {
    j->id_jugador = id;
    strncpy(j->nombre, nombre, MAX_NOMBRE_J - 1);
    j->nombre[MAX_NOMBRE_J - 1] = '\0';
    strncpy(j->sala_actual, sala_inicio, MAX_ID_SALA - 1);
    j->sala_actual[MAX_ID_SALA - 1] = '\0';
    
    j->inventario = NULL;
    j->num_objetos = 0;
}

void actualizarPosicion(Jugador *j, char *nueva_sala) {
    strncpy(j->sala_actual, nueva_sala, MAX_ID_SALA - 1);
    j->sala_actual[MAX_ID_SALA - 1] = '\0';
}

/* Recuerda que en tu jugador.h cambiamos la 'ñ' por una 'n' */
int anadirObjeto(Jugador *j, char *id_obj) {
    char **aux = (char **)realloc(j->inventario, (j->num_objetos + 1) * sizeof(char *));
    if (aux == NULL) {
        return 0; // Fallo de memoria
    }
    j->inventario = aux;
    
    // Asignamos memoria para la palabra (ID del objeto)
    j->inventario[j->num_objetos] = (char *)malloc(MAX_ID_OBJ * sizeof(char));
    strncpy(j->inventario[j->num_objetos], id_obj, MAX_ID_OBJ - 1);
    j->inventario[j->num_objetos][MAX_ID_OBJ - 1] = '\0';
    
    j->num_objetos++;
    return 1; // Éxito
}

int quitarObjeto(Jugador *j, char *id_obj) {
    int i, k;
    for (i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            free(j->inventario[i]); // Borramos el objeto
            // Desplazamos los demas objetos un espacio hacia atras
            for (k = i; k < j->num_objetos - 1; k++) {
                j->inventario[k] = j->inventario[k + 1];
            }
            j->num_objetos--;
            
            if (j->num_objetos == 0) {
                free(j->inventario);
                j->inventario = NULL;
            } else {
                j->inventario = (char **)realloc(j->inventario, j->num_objetos * sizeof(char *));
            }
            return 1; // Éxito
        }
    }
    return 0; // No lo tenía en el inventario
}

int tieneObjeto(Jugador *j, char *id_obj) {
    for (int i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            return 1;
        }
    }
    return 0;
}

void liberarMemoriaJugador(Jugador *j) {
    if (j->inventario != NULL) {
        for (int i = 0; i < j->num_objetos; i++) {
            free(j->inventario[i]);
        }
        free(j->inventario);
        j->inventario = NULL;
    }
    j->num_objetos = 0;
}