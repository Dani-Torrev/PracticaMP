#include <stdio.h>
#include <string.h>
#include "puzles.h"
#include "logica.h"

void resolver_puzzle_actual(EstadoJuego *juego){
    int idx_puzle = -1;
    int i;
    int conexiones_desbloqueadas;
    char respuesta[51];
    int c;

    for(int i = 0; i < juego->num_puzles; i++){
        if(strcpy(juego->puzles[i].id_sala, juego->sala_actual_id) == 0){
            idx_puzle = i;
            break;
        }
    }

    if(idx_puzle == -1){
        printf("\nNo hay ningun puzle ni panel de codigo en esta sala.\n");
        return;
    }

    if (juego->puzles[idx_puzle].resuelto){
        printf("\nEl puzle de esta sala ya ha sido resuelto. ¡Buen trabajo!\n");
        return;
    }

    printf("\n=== PUZLE: %s ===\n", juego->puzles[idx_puzle].nomb_puzle);
    printf("%s\n", juego->puzles[idx_puzle].descrip);
    printf ("Introduce la solucion (%s): ", juego->puzles[idx_puzle].tipo);

    while ((c = getchar()) != '\n' && c != EOF);

    fgets(respuesta, 51, stdin);
    respuesta[strcspn(respuesta, "\n")] = 0;

    if (strcmp(respuesta, juego->puzles[idx_puzle].solucion) == 0){
        printf("\n>>> !Correcto¡ Has dado con la solucion.\n");

        juego->puzles[idx_puzle].resuelto = true;
        conexiones_desbloqueadas = 0;

        for (int i = 0; i < juego->num_conexiones; i++){
            if(strcmp(juego->conexiones[i].condicion, juego->puzles[idx_puzle].id_puzzle) == 0) {
                strcpy(juego->conexiones[i].estado, "Activa");
                printf("-> Has escuchado un mecanismo. Se ha desbloqueado el acceso a la sala %s.\n", juego->conexiones[i].id_destino);
                conexiones_desbloqueadas++;
            }
        }

        if(conexiones_desbloqueadas == 0){
            printf("-> Curioso... resolver esto no ha abierto ninguna puerta visible.\n");
        }
    } else{
        printf("\nRespuesta incorrecta. Parece que esa no es la clave. Sigue intentandolo.\n");
    }
}