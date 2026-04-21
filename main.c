#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logica.h"
#include "gestion_de_ficheros.h"
#include "autentificacion.h"
#include "puzles.h"
#include "salas.h"
#include "conexion.h"
#include "objetos.h"
#include "jugador.h"
#include "utilidades.h"

void mirar_alrededor(EstadoJuego *juego) {
    for (int i = 0; i < juego->num_salas; i++) {
        if (atoi(juego->salas[i].id_sala) == atoi(juego->sala_actual_id)) {
            printf("\n=========================================\n");
            printf("  SALA ACTUAL: %s \n", juego->salas[i].nombre);
            printf("=========================================\n");
            printf("%s\n", juego->salas[i].descripcion);
            return;
        }
    }
}

int main() {
    EstadoJuego mi_partida;
    int jugando = 1;
    char opcion[10];
    int id_sesion = -1;
    char user[20], pass[20];

    inicializar_datos(&mi_partida);
    cargar_ficheros_juego(&mi_partida);
    mi_partida.jugadores_bd = cargarJugadores(&mi_partida.num_jugadores_bd);
    mi_partida.objetos = cargarObjetos(&mi_partida.num_objetos);

    limpiarPantalla();
    printf("=========================================\n");
    printf("        BIENVENIDO AL ESCAPE ROOM        \n");
    printf("=========================================\n\n");

    while (id_sesion == -1) {
        printf("[1] Iniciar Sesion\n");
        printf("[2] Registrar Nuevo Usuario\n");
        printf("> ");
        fgets(opcion, 10, stdin);
        opcion[strcspn(opcion, "\n")] = 0;

        if (strcmp(opcion, "1") == 0) {
            printf("Usuario: ");
            scanf("%19s", user);
            printf("Contrasena: ");
            scanf("%19s", pass);
            limpiarBuffer();
            id_sesion = verificarAcceso(mi_partida.jugadores_bd, mi_partida.num_jugadores_bd, user, pass);
            if (id_sesion == -1) printf("\n[X] Credenciales incorrectas.\n\n");
        } else if (strcmp(opcion, "2") == 0) {
            registrarJugador(&mi_partida.jugadores_bd, &mi_partida.num_jugadores_bd);
            limpiarBuffer(); 
        }
    }

    mi_partida.jugador_actual = (Jugador *)malloc(sizeof(Jugador));
    strcpy(mi_partida.sala_actual_id, mi_partida.num_salas > 0 ? mi_partida.salas[0].id_sala : "1");
    inicializarJugador(mi_partida.jugador_actual, id_sesion, user, mi_partida.sala_actual_id);

    while (jugando == 1) {
        limpiarPantalla();
        mirar_alrededor(&mi_partida);

        // ==========================================
        //  COMPROBACIÓN DE VICTORIA (¡EL GRAN FINAL!)
        // ==========================================
        int has_ganado = 0;
        for (int i = 0; i < mi_partida.num_salas; i++) {
            if (atoi(mi_partida.salas[i].id_sala) == atoi(mi_partida.sala_actual_id)) {
                if (es_sala_final(mi_partida.salas[i])) {
                    has_ganado = 1;
                }
            }
        }

        if (has_ganado) {
            printf("\n");
            printf("********************************************************\n");
            printf("* *\n");
            printf("* ¡ENHORABUENA! HAS ESCAPADO DE LA ESI CON EXITO       *\n");
            printf("* *\n");
            printf("********************************************************\n\n");
            printf("Has superado todos los puzles, desbloqueado las puertas,\n");
            printf("encontrado los objetos y demostrado ser un hacker en C.\n\n");
            printf("¡Gracias por jugar!\n");
            
            pausa();
            jugando = 0; // Apagamos el motor del juego
            continue;    // Saltamos el menú y vamos directo al final
        }
        // ==========================================

        printf("\n¿Que deseas hacer?\n [1] Buscar objetos\n [2] Inspeccionar puzle\n [3] Moverse\n [4] Coger objeto\n [5] Mochila\n [6] Salir\n> ");
        fgets(opcion, 10, stdin);
        opcion[strcspn(opcion, "\n")] = 0;

        if (strcmp(opcion, "1") == 0) {
            printf("\nRevisando los rincones...\n");
            listarObjetosEnSala(mi_partida.objetos, mi_partida.num_objetos, mi_partida.sala_actual_id);
            pausa();
        } else if (strcmp(opcion, "2") == 0) {
            resolver_puzzle_actual(&mi_partida);
            pausa();
        } else if (strcmp(opcion, "3") == 0) {
            printf("\nCaminos posibles:\n");
            for (int i = 0; i < mi_partida.num_conexiones; i++) {
                if (atoi(mi_partida.conexiones[i].id_origen) == atoi(mi_partida.sala_actual_id)) {
                    printf("-> Sala [%s] (%s) [Requiere: %s]\n", mi_partida.conexiones[i].id_destino, mi_partida.conexiones[i].estado, mi_partida.conexiones[i].condicion);
                }
            }
            char dest[5];
            printf("\nIr a la sala numero: ");
            scanf("%4s", dest); limpiarBuffer();
            
            for (int i = 0; i < mi_partida.num_conexiones; i++) {
                if (atoi(mi_partida.conexiones[i].id_origen) == atoi(mi_partida.sala_actual_id) && atoi(mi_partida.conexiones[i].id_destino) == atoi(dest)) {
                    char est[20], cond[20];
                    strcpy(est, mi_partida.conexiones[i].estado); est[strcspn(est, "\r\n ")] = 0;
                    strcpy(cond, mi_partida.conexiones[i].condicion); cond[strcspn(cond, "\r\n ")] = 0;

                    if (strcmp(est, "Abierta") == 0 || verificarUsoObjeto(mi_partida.objetos, mi_partida.num_objetos, cond)) {
                        if (strcmp(est, "Cerrada") == 0) printf("\n[!] Has usado %s para abrir la puerta.\n", cond);
                        strcpy(mi_partida.conexiones[i].estado, "Abierta");
                        strcpy(mi_partida.sala_actual_id, mi_partida.conexiones[i].id_destino);
                    } else {
                        printf("\n[X] Bloqueada. Necesitas: %s\n", cond);
                    }
                    break;
                }
            }
            pausa();
        } else if (strcmp(opcion, "4") == 0) {
            char id_obj[10];
            printf("\nID del objeto a coger (ej. O1): ");
            scanf("%9s", id_obj); limpiarBuffer();
            if (cogerObjeto(mi_partida.objetos, mi_partida.num_objetos, id_obj, mi_partida.sala_actual_id) == 1) {
                anadirObjeto(mi_partida.jugador_actual, id_obj);
            }
            pausa();
        } else if (strcmp(opcion, "5") == 0) {
            listarInventario(mi_partida.objetos, mi_partida.num_objetos);
            pausa();
        } else if (strcmp(opcion, "6") == 0) {
            jugando = 0;
        }
    }
    liberar_datos(&mi_partida);
    return 0;
}