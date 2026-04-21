#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"

// Inicializa todas las estructuras de datos del juego
void inicializar_datos(EstadoJuego *juego){
    // Inicializa los punteros de salas
    juego->salas = NULL;
    juego->num_salas = 0;
    // Inicializa las conexiones
    juego->conexiones = NULL;
    juego->num_conexiones = 0;
    // Inicializa los objetos
    juego->objetos = NULL;
    juego->num_objetos = 0;
    // Inicializa los puzles
    juego->puzles = NULL;
    juego->num_puzles = 0;
    // Inicializa la base de datos de jugadores
    juego->jugadores_bd = NULL;
    juego->num_jugadores_bd = 0;
    // Inicializa el jugador actual
    juego->jugador_actual = NULL;
    // Inicializa la sala actual
    strcpy(juego->sala_actual_id, "");

}

// Libera toda la memoria dinámica del estado del juego
void liberar_datos(EstadoJuego *juego){
    int i, j;

    // Libera el array de salas
    if((juego->salas != NULL)) free(juego->salas);
    // Libera el array de conexiones
    if((juego->conexiones != NULL)) free(juego->conexiones);
    // Libera el array de objetos
    if((juego->objetos != NULL)) free(juego->objetos);
    // Libera el array de puzles
    if((juego->puzles != NULL)) free(juego->puzles);

    // Libera la base de datos de jugadores
    if((juego->jugadores_bd != NULL)){
        free(juego->jugadores_bd);
    }

    // Libera el jugador actual y su inventario
    if (juego->jugador_actual != NULL){
        if (juego->jugador_actual->inventario != NULL){
            // Libera cada objeto del inventario
            for (j = 0; j < juego->jugador_actual->num_objetos; j++){
                free(juego->jugador_actual->inventario[j]);
            }
            free(juego->jugador_actual->inventario);
        }
        free(juego->jugador_actual);
    }
}