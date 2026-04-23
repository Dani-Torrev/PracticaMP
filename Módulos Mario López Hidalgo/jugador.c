#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"

// Inicializa un jugador con los datos básicos
void inicializarJugador(Jugador *j, int id, char *nombre, char *sala_inicio) {
    // Asigna el ID del jugador
    j->id_jugador = id;
    // Copia el nombre con límite de seguridad
    strncpy(j->nombre, nombre, MAX_NOMBRE_J - 1);
    j->nombre[MAX_NOMBRE_J - 1] = '\0';
    // Asigna la sala inicial
    strncpy(j->sala_actual, sala_inicio, MAX_ID_SALA - 1);
    j->sala_actual[MAX_ID_SALA - 1] = '\0';
    
    // Inicializa el inventario vacío
    j->inventario = NULL;
    j->num_objetos = 0;
}

// Actualiza la sala actual donde se encuentra el jugador
void actualizarPosicion(Jugador *j, char *nueva_sala) {
    // Copia la nueva sala con límite de seguridad
    strncpy(j->sala_actual, nueva_sala, MAX_ID_SALA - 1);
    j->sala_actual[MAX_ID_SALA - 1] = '\0';
}


int anadirObjeto(Jugador *j, char *id_obj) {
     // Expande el inventario para un nuevo objeto
    char *aux = (char *)realloc(j->inventario,
                  (j->num_objetos + 1) * sizeof(char *));
    if (aux == NULL) {
        return 0;
    }
    j->inventario = aux;

      // Asigna memoria para el ID del objeto
    j->inventario[j->num_objetos] = (char *)malloc(MAX_ID_OBJ * sizeof(char));
      // Copia el ID del objeto
    if (j->inventario[j->num_objetos] == NULL) {   /* ← línea añadida */
        return 0;
    }

    strncpy(j->inventario[j->num_objetos], id_obj, MAX_ID_OBJ - 1);
    j->inventario[j->num_objetos][MAX_ID_OBJ - 1] = '\0';

    j->num_objetos++;
    return 1;
}

// Quita un objeto del inventario del jugador
int quitarObjeto(Jugador *j, char *id_obj) {
    int i, k;
    // Busca el objeto a eliminar
    for (i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            // Libera la memoria del objeto encontrado
            free(j->inventario[i]);
            // Desplaza los objetos siguientes una posición atrás
            for (k = i; k < j->num_objetos - 1; k++) {
                j->inventario[k] = j->inventario[k + 1];
            }
            j->num_objetos--;
            
            // Si el inventario quedó vacío, libera el array
            if (j->num_objetos == 0) {
                free(j->inventario);
                j->inventario = NULL;
            } else {
                // Redimensiona el inventario
                j->inventario = (char **)realloc(j->inventario, j->num_objetos * sizeof(char *));
            }
            return 1; // Éxito
        }
    }
    return 0; // No encontrado
}

// Verifica si el jugador tiene un objeto específico
int tieneObjeto(Jugador *j, char *id_obj) {
    // Recorre todo el inventario buscando el objeto
    for (int i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            return 1; // Objeto encontrado
        }
    }
    return 0; // Objeto no encontrado
}

// Libera toda la memoria del jugador incluyendo su inventario
void liberarMemoriaJugador(Jugador *j) {
    if (j->inventario != NULL) {
        // Libera cada objeto del inventario
        for (int i = 0; i < j->num_objetos; i++) {
            free(j->inventario[i]);
        }
        // Libera el array del inventario
        free(j->inventario);
        j->inventario = NULL;
    }
    j->num_objetos = 0;
}
