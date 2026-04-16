// Includes necesarios para entrada/salida, memoria, strings y headers personalizados
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzles.h"
#include "logica.h"

// Función para resolver el puzle de la sala actual
void resolver_puzzle_actual(EstadoJuego *juego) {
    // Variables locales: i para el índice del bucle, puzle_encontrado para indicar si hay puzle, respuesta para almacenar la entrada del usuario
    int i;
    int puzle_encontrado = 0;
    char respuesta[50];

    // Recorremos todos los puzles del juego para encontrar el de la sala actual
    for (i = 0; i < juego->num_puzles; i++) {
        // Comprobamos si el puzle pertenece a la sala actual
        if (strcmp(juego->puzles[i].id_sala, juego->sala_actual_id) == 0) {
            puzle_encontrado = 1; // Marcamos que se encontró un puzle en esta sala
            
            if (juego->puzles[i].resuelto == 1) {
                printf("\nYa has resuelto el puzle de esta sala: %s\n", juego->puzles[i].nomb_puzle);
                return; // Salimos ya que el puzle ya está resuelto
            }

            // Mostramos el nombre y descripción del puzle
            printf("\n--- PUZLE: %s ---\n", juego->puzles[i].nomb_puzle);
            printf("%s\n", juego->puzles[i].descrip);
            printf("Tu respuesta: ");
            
            // Leemos la respuesta del usuario desde la entrada estándar
            fgets(respuesta, 50, stdin);
            // Eliminamos el carácter de nueva línea y retorno de carro si existen
            respuesta[strcspn(respuesta, "\n")] = 0;
            respuesta[strcspn(respuesta, "\r")] = 0;

            // Comprobamos si la respuesta coincide con la solución
            if (strcmp(respuesta, juego->puzles[i].solucion) == 0) {
                printf("\n[+] ¡Correcto! Has resuelto el puzle.\n");
                juego->puzles[i].resuelto = 1; // Marcamos el puzle como resuelto
                
                // Al resolver el puzle, abrimos todas las conexiones (puertas) de la sala actual
                for (int j = 0; j < juego->num_conexiones; j++) {
                    if (strcmp(juego->conexiones[j].id_origen, juego->sala_actual_id) == 0) {
                        strcpy(juego->conexiones[j].estado, "Abierta"); // Cambiamos el estado a "Abierta"
                    }
                }
                printf("[!] Has escuchado el sonido de una puerta desbloqueandose...\n");
            } else {
                printf("\n[X] Respuesta incorrecta. Sigue intentandolo.\n");
            }
            return; // Salimos después de procesar el puzle
        }
    }

    // Si no se encontró ningún puzle en la sala actual
    if (puzle_encontrado == 0) {
        printf("\nNo hay ningun puzle en esta sala.\n");
    }
}