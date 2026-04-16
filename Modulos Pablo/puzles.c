#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzles.h"
#include "logica.h"

void resolver_puzzle_actual(EstadoJuego *juego) {
    int i;
    int puzle_encontrado = 0;
    char respuesta[50];

    for (i = 0; i < juego->num_puzles; i++) {
        // Comprobamos si el puzle pertenece a la sala actual
        if (strcmp(juego->puzles[i].id_sala, juego->sala_actual_id) == 0) {
            puzle_encontrado = 1;
            
            if (juego->puzles[i].resuelto == 1) {
                printf("\nYa has resuelto el puzle de esta sala: %s\n", juego->puzles[i].nomb_puzle);
                return;
            }

            printf("\n--- PUZLE: %s ---\n", juego->puzles[i].nomb_puzle);
            printf("%s\n", juego->puzles[i].descrip);
            printf("Tu respuesta: ");
            
            fgets(respuesta, 50, stdin);
            respuesta[strcspn(respuesta, "\n")] = 0;
            respuesta[strcspn(respuesta, "\r")] = 0;

            // Comprobamos la solución
            if (strcmp(respuesta, juego->puzles[i].solucion) == 0) {
                printf("\n[+] ¡Correcto! Has resuelto el puzle.\n");
                juego->puzles[i].resuelto = 1;
                
                // Magia: ¡Abrimos todas las puertas Cerradas de esta sala!
                for (int j = 0; j < juego->num_conexiones; j++) {
                    if (strcmp(juego->conexiones[j].id_origen, juego->sala_actual_id) == 0) {
                        strcpy(juego->conexiones[j].estado, "Abierta");
                    }
                }
                printf("[!] Has escuchado el sonido de una puerta desbloqueandose...\n");
            } else {
                printf("\n[X] Respuesta incorrecta. Sigue intentandolo.\n");
            }
            return;
        }
    }

    if (puzle_encontrado == 0) {
        printf("\nNo hay ningun puzle en esta sala.\n");
    }
}