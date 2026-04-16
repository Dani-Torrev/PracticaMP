// Includes para entrada/salida, memoria dinámica, strings y header del jugador
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"

// Función para inicializar un jugador con ID, nombre y sala de inicio
void inicializarJugador(Jugador *j, int id, char *nombre, char *sala_inicio) {
    j->id_jugador = id; // Asignamos el ID del jugador
    // Copiamos el nombre asegurando que no exceda el límite
    strncpy(j->nombre, nombre, MAX_NOMBRE_J - 1);
    j->nombre[MAX_NOMBRE_J - 1] = '\0'; // Aseguramos terminación nula
    // Copiamos la sala actual
    strncpy(j->sala_actual, sala_inicio, MAX_ID_SALA - 1);
    j->sala_actual[MAX_ID_SALA - 1] = '\0'; // Aseguramos terminación nula
    
    j->inventario = NULL; // Inicializamos inventario vacío
    j->num_objetos = 0; // Contador de objetos a cero
}

// Función para actualizar la posición del jugador a una nueva sala
void actualizarPosicion(Jugador *j, char *nueva_sala) {
    // Copiamos la nueva sala asegurando límites
    strncpy(j->sala_actual, nueva_sala, MAX_ID_SALA - 1);
    j->sala_actual[MAX_ID_SALA - 1] = '\0'; // Aseguramos terminación nula
}

/* Recuerda que en tu jugador.h cambiamos la 'ñ' por una 'n' */
// Función para añadir un objeto al inventario del jugador
int anadirObjeto(Jugador *j, char *id_obj) {
    // Redimensionamos el inventario para añadir un nuevo objeto
    char **aux = (char **)realloc(j->inventario, (j->num_objetos + 1) * sizeof(char *));
    if (aux == NULL) {
        return 0; // Fallo de memoria
    }
    j->inventario = aux;
    
    // Asignamos memoria para el ID del objeto
    j->inventario[j->num_objetos] = (char *)malloc(MAX_ID_OBJ * sizeof(char));
    // Copiamos el ID asegurando límites
    strncpy(j->inventario[j->num_objetos], id_obj, MAX_ID_OBJ - 1);
    j->inventario[j->num_objetos][MAX_ID_OBJ - 1] = '\0'; // Terminación nula
    
    j->num_objetos++; // Incrementamos el contador
    return 1; // Éxito
}

// Función para quitar un objeto del inventario del jugador
int quitarObjeto(Jugador *j, char *id_obj) {
    int i, k;
    // Buscamos el objeto en el inventario
    for (i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            free(j->inventario[i]); // Liberamos la memoria del objeto
            // Desplazamos los objetos restantes hacia atrás
            for (k = i; k < j->num_objetos - 1; k++) {
                j->inventario[k] = j->inventario[k + 1];
            }
            j->num_objetos--; // Decrementamos el contador
            
            // Si no quedan objetos, liberamos el inventario
            if (j->num_objetos == 0) {
                free(j->inventario);
                j->inventario = NULL;
            } else {
                // Redimensionamos el inventario
                j->inventario = (char **)realloc(j->inventario, j->num_objetos * sizeof(char *));
            }
            return 1; // Éxito
        }
    }
    return 0; // No se encontró el objeto en el inventario
}

// Función para comprobar si el jugador tiene un objeto específico en el inventario
int tieneObjeto(Jugador *j, char *id_obj) {
    // Recorremos el inventario buscando el objeto
    for (int i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {
            return 1; // Encontrado
        }
    }
    return 0; // No encontrado
}

// Función para liberar la memoria dinámica del inventario del jugador
void liberarMemoriaJugador(Jugador *j) {
    if (j->inventario != NULL) {
        // Liberamos cada objeto del inventario
        for (int i = 0; i < j->num_objetos; i++) {
            free(j->inventario[i]);
        }
        // Liberamos el array de punteros
        free(j->inventario);
        j->inventario = NULL; // Ponemos a NULL para evitar dangling pointers
    }
    j->num_objetos = 0; // Reseteamos el contador
}