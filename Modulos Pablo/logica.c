// Includes para entrada/salida, memoria, strings y header de lógica
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"

// Función para inicializar los datos del estado del juego a valores por defecto
void inicializar_datos(EstadoJuego *juego) {
    juego->salas = NULL; // Inicializa punteros a NULL
    juego->num_salas = 0; // Inicializa contadores a 0
    juego->conexiones = NULL;
    juego->num_conexiones = 0;
    juego->objetos = NULL;
    juego->num_objetos = 0;
    juego->puzles = NULL;
    juego->num_puzles = 0;
    juego->jugadores_bd = NULL;
    juego->num_jugadores_bd = 0;
    juego->jugador_actual = NULL; // Jugador actual a NULL
    strcpy(juego->sala_actual_id, ""); // Sala actual vacía
}

// Función para liberar la memoria dinámica asignada al estado del juego
void liberar_datos(EstadoJuego *juego) {
    int i, j;

    // Libera las listas principales si no son NULL
    if ((juego->salas != NULL)) free(juego->salas);
    if ((juego->conexiones != NULL)) free(juego->conexiones);
    if ((juego->objetos != NULL)) free(juego->objetos);
    if ((juego->puzles != NULL)) free(juego->puzles);

    if ((juego->jugadores_bd != NULL)) {
        free(juego->jugadores_bd); // Libera base de datos de jugadores
    }

    // Libera el jugador actual y su inventario
    if (juego->jugador_actual != NULL) {
        if (juego->jugador_actual->inventario != NULL) {
            // Libera cada objeto del inventario
            for (j = 0; j < juego->jugador_actual->num_objetos; j++) {
                free(juego->jugador_actual->inventario[j]);
            }
            free(juego->jugador_actual->inventario); // Libera el array de inventario
        }
        free(juego->jugador_actual); // Libera el jugador actual
    }
}