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

// Función ayudante para imprimir la sala actual
void mirar_alrededor(EstadoJuego *juego) {
    int i;
    for (i = 0; i < juego->num_salas; i++) {
        if (strcmp(juego->salas[i].id_sala, juego->sala_actual_id) == 0) {
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

    /* --- 1. INICIALIZACION Y CARGA DEL MUNDO --- */
    inicializar_datos(&mi_partida);
    cargar_ficheros_juego(&mi_partida);
    
    // Cargamos los módulos de tus compañeros
    mi_partida.jugadores_bd = cargarJugadores(&mi_partida.num_jugadores_bd);
    mi_partida.objetos = cargarObjetos(&mi_partida.num_objetos);

    limpiarPantalla();
    printf("=========================================\n");
    printf("        BIENVENIDO AL ESCAPE ROOM        \n");
    printf("=========================================\n\n");

    /* --- 2. PANTALLA DE LOGIN --- */
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
            if (id_sesion != -1) {
                printf("\n¡Acceso concedido! Preparando partida...\n");
                pausa();
            } else {
                printf("\n[X] Credenciales incorrectas. Intentalo de nuevo.\n\n");
            }
        } else if (strcmp(opcion, "2") == 0) {
            registrarJugador(&mi_partida.jugadores_bd, &mi_partida.num_jugadores_bd);
            limpiarBuffer(); 
        }
    }

    /* --- 3. PREPARAR JUGADOR --- */
    mi_partida.jugador_actual = (Jugador *)malloc(sizeof(Jugador));
    
    // TRUCO DEFINITIVO: En lugar de forzar el "1", cogemos el ID exacto que haya 
    // leído el juego de la primera línea de salas.txt. Así evitamos fallos por espacios invisibles.
    if (mi_partida.num_salas > 0) {
        strcpy(mi_partida.sala_actual_id, mi_partida.salas[0].id_sala);
    } else {
        strcpy(mi_partida.sala_actual_id, "1"); // Por si acaso falla la lectura
    }
    inicializarJugador(mi_partida.jugador_actual, id_sesion, user, mi_partida.sala_actual_id);

    /* --- 4. EL BUCLE DEL VIDEOJUEGO --- */
    while (jugando == 1) {
        limpiarPantalla();
        mirar_alrededor(&mi_partida);
        
        printf("\n¿Que deseas hacer?\n");
        printf(" [1] Buscar objetos por la sala\n");
        printf(" [2] Inspeccionar puzle o puerta bloqueada\n");
        printf(" [3] Moverse a otra habitacion\n");
        printf(" [4] Coger un objeto del suelo\n");
        printf(" [5] Ver mi mochila (Inventario)\n");
        printf(" [6] Guardar y Salir\n");
        printf("> ");
        
        fgets(opcion, 10, stdin);
        opcion[strcspn(opcion, "\n")] = 0;

        // ---------- ACCIONES ----------
        if (strcmp(opcion, "1") == 0) {
            printf("\nRevisando los rincones...\n");
            listarObjetosEnSala(mi_partida.objetos, mi_partida.num_objetos, mi_partida.sala_actual_id);
            pausa();

        } else if (strcmp(opcion, "2") == 0) {
            resolver_puzzle_actual(&mi_partida);
            pausa();

        } else if (strcmp(opcion, "3") == 0) {
            printf("\nCaminos posibles:\n");
            int hay_camino = 0;
            // Listamos todas las conexiones que salgan de nuestra sala
            for (int i = 0; i < mi_partida.num_conexiones; i++) {
                if (strcmp(mi_partida.conexiones[i].id_origen, mi_partida.sala_actual_id) == 0) {
                    printf("-> Puerta hacia la sala [%s] (Estado actual: %s)\n", 
                           mi_partida.conexiones[i].id_destino, 
                           mi_partida.conexiones[i].estado);
                    hay_camino = 1;
                }
            }
            
            if (hay_camino) {
                char dest[5];
                printf("\nIntroduce el numero de la sala a la que quieres ir: ");
                scanf("%4s", dest);
                limpiarBuffer();
                
                int movido = 0;
                for (int i = 0; i < mi_partida.num_conexiones; i++) {
                    if (strcmp(mi_partida.conexiones[i].id_origen, mi_partida.sala_actual_id) == 0 && 
                        strcmp(mi_partida.conexiones[i].id_destino, dest) == 0) {
                        
                        // Si el estado es Activa, pasamos de sala
                        if (strcmp(mi_partida.conexiones[i].estado, "Abierta") == 0) {
                            strcpy(mi_partida.sala_actual_id, dest);
                            actualizarPosicion(mi_partida.jugador_actual, dest);
                            printf("\n[+] Caminando hacia la sala %s...\n", dest);
                            movido = 1;
                        } else {
                            printf("\n[X] La puerta esta %s. Busca un puzle para abrirla.\n", mi_partida.conexiones[i].estado);
                            movido = 1;
                        }
                    }
                }
                if (!movido) printf("\n[X] No hay ninguna puerta directa hacia ahi.\n");
            } else {
                printf("No parece haber salidas desde aqui.\n");
            }
            pausa();

        } else if (strcmp(opcion, "4") == 0) {
            char id_obj[5];
            printf("\nIntroduce el ID del objeto que quieres coger (ej. O01): ");
            scanf("%4s", id_obj);
            limpiarBuffer();
            
            // Llama a la funcion de tu compañero
            if (cogerObjeto(mi_partida.objetos, mi_partida.num_objetos, id_obj, mi_partida.sala_actual_id) == 1) {
                anadirObjeto(mi_partida.jugador_actual, id_obj); // Guardamos internamente
            }
            pausa();

        } else if (strcmp(opcion, "5") == 0) {
            listarInventario(mi_partida.objetos, mi_partida.num_objetos);
            pausa();

        } else if (strcmp(opcion, "6") == 0) {
            printf("\n¡Guardando tu progreso en la base de datos!\n");
            guardarJugadores(mi_partida.jugadores_bd, mi_partida.num_jugadores_bd);
            jugando = 0;

        } else {
            printf("\n[X] Esa no es una opcion del menu.\n");
            pausa();
        }
    }

    /* --- 5. FIN Y LIMPIEZA --- */
    printf("\nGracias por jugar al Escape Room.\n");
    liberar_datos(&mi_partida);
    return 0;
}