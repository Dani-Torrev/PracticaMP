#include <stdio.h>
#include <stdlib.h>
#include "logica.h"

void inicializar_datos(estadoJuego *juego){

    juego->salas = NULL
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
    juego->sala_actual_id = 0;

}

void liberar_datos(EstadoJuego *juego){

    int i, j;

    if((juego->salas !=NULL)) free(juego->salas);
    if((juego->conexiones !=NULL)) free(juego->conexiones);
    if((juego->objetos !=NULL)) free(juego->objetos);
    if((juego->puzles !=NULL)) free(juego->puzles);

    if((juego->jugadores_bd !=NULL)){

        for (i = 0; i < juego->num_jugadores_bd; i++){
            if(juego->jugadores_bd[i].inventario !=NULL){
                for (j= 0; j < juego->jugadores_bd[i].num_objetos; j++){
                    free(juego->jugadores_bd[i].inventario[j]);
                }
                free(juego->jugadores_bd[i].inventario);
            }
        }
        free(juego->jugadores_bd);
    }

}