#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"

void inicializar_datos(EstadoJuego *juego){

    juego->salas = NULL;
    juego->num_salas = 0;
    juego->conexiones = NULL;
    juego->num_conexiones = 0;
    juego->objetos = NULL;
    juego->num_objetos = 0;
    juego->puzles = NULL;
    juego->num_puzles = 0;
    juego->jugadores_bd = NULL;
    juego->num_jugadores_bd = 0;
    juego->jugador_actual =NULL;
    strcpy(juego->sala_actual_id, "");

}

void liberar_datos(EstadoJuego *juego){

    int i, j;

    if((juego->salas !=NULL)) free(juego->salas);
    if((juego->conexiones !=NULL)) free(juego->conexiones);
    if((juego->objetos !=NULL)) free(juego->objetos);
    if((juego->puzles !=NULL)) free(juego->puzles);

    if((juego->jugadores_bd !=NULL)){
        free(juego->jugadores_bd);
    }


    if (juego->jugador_actual != NULL){
        if (juego->jugador_actual->inventario != NULL){
            for (j = 0; j < juego->jugador_actual->num_objetos; j++){
                free(juego->jugador_actual->inventario[j]);
            }
            free(juego->jugador_actual->inventario);
        }
        free(juego->jugador_actual);
    }
}