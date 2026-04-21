#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzles.h"
#include "logica.h"

// Resuelve el puzle actual del juego
void resolver_puzzle_actual(EstadoJuego *juego) {
    int i;
    char respuesta[50];

    // Busca el puzle en la sala actual
    for (i = 0; i < juego->num_puzles; i++) {
        if (atoi(juego->puzles[i].id_sala) == atoi(juego->sala_actual_id)) {
            
            // Comprueba si ya fue resuelto
            if (juego->puzles[i].resuelto == 1) {
                printf("\nEste puzle ya ha sido resuelto.\n");
                return;
            }

            // Muestra el puzle al jugador
            printf("\n--- PUZLE: %s ---\n", juego->puzles[i].nomb_puzle);
            printf("%s\n", juego->puzles[i].descrip);
            printf("Respuesta: ");
            
            // Lee la respuesta del jugador
            fgets(respuesta, 50, stdin);
            respuesta[strcspn(respuesta, "\r\n")] = 0;

            // Prepara la solución limpia
            char sol_limpia[50];
            strcpy(sol_limpia, juego->puzles[i].solucion);
            sol_limpia[strcspn(sol_limpia, " \r\n")] = 0;

            // Compara la respuesta con la solución
            if (strcmp(respuesta, sol_limpia) == 0) {
                printf("\n[+] ¡CORRECTO! Has resuelto el puzle.\n");
                juego->puzles[i].resuelto = 1;
                
                // Busca objetos ocultos relacionados con este puzle
                char etiqueta_oculta[20];
                sprintf(etiqueta_oculta, "Oculto%d", atoi(juego->sala_actual_id));
                
                int objeto_encontrado = 0;
                // Recorre los objetos buscando los ocultos
                for (int o = 0; o < juego->num_objetos; o++) {
                    char loc_obj[20];
                    strcpy(loc_obj, juego->objetos[o].localiz);
                    loc_obj[strcspn(loc_obj, " \r\n")] = 0;

                    // Si encuentra un objeto oculto, lo revela
                    if (strcmp(loc_obj, etiqueta_oculta) == 0) {
                        sprintf(juego->objetos[o].localiz, "%d", atoi(juego->sala_actual_id));
                        printf("[!] ¡CLANCK! Escuchas algo caer al suelo. ¡Usa la opcion [1] para buscar!\n");
                        objeto_encontrado = 1;
                    }
                }
                
                if(!objeto_encontrado) {
                    printf("[!] El puzle esta resuelto, pero no ha caido nada aqui.\n");
                }

            } else {
                printf("\n[X] Respuesta incorrecta. Sigue intentandolo.\n");
            }
            return;
        }
    }
    printf("\nNo hay ningun puzle en esta sala.\n");
}