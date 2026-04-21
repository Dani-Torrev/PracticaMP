#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_de_ficheros.h"

// Lee una línea desde un archivo eliminando saltos de línea
void leer_linea(FILE *f, char *buffer, int max_letras) {
    // Intenta leer una línea del archivo
    if (fgets(buffer, max_letras, f) != NULL){
        // Elimina el character de salto de línea Unix
        buffer[strcspn(buffer, "\n")] = 0;
        // Elimina el caracter de salto de línea Windows
        buffer[strcspn(buffer, "\r")] = 0;
    }
}

// Carga todos los ficheros necesarios para el juego
void cargar_ficheros_juego(EstadoJuego *juego){
    FILE *f;
    char linea[256];
    int i;

    printf("Cargando base de datos del juego...\n");

    // ========== CARGAR SALAS ==========
    f = fopen("salas.txt", "r");
    juego->salas = NULL;
    juego->num_salas = 0;
    if (f != NULL){
        // Lee el número total de salas
        leer_linea(f, linea, 256);
        juego->num_salas = atoi(linea);
        // Reserva memoria para las salas
        juego->salas = (Sala *)malloc(juego->num_salas * sizeof(Sala));

        // Lee cada sala
        for (i = 0; i < juego->num_salas; i++){
            leer_linea(f, juego->salas[i].id_sala, 5);
            leer_linea(f, juego->salas[i].nombre, 50);
            leer_linea(f, juego->salas[i].tipo, 20);
            leer_linea(f, juego->salas[i].descripcion, 200);
        }
        fclose(f);
        printf("    [OK] Salas cargadas: %d\n", juego->num_salas);
    } else {
        printf("    [ERROR] No se pudo abrir salas.txt\n");
    }

    // ========== CARGAR PUZLES ==========
    f = fopen("puzles.txt", "r");
    if (f != NULL){
        // Lee el número total de puzles
        leer_linea(f, linea, 256);
        juego->num_puzles = atoi(linea);
        // Reserva memoria para los puzles
        juego->puzles = (Puzle *)malloc(juego->num_puzles * sizeof(Puzle));

        // Lee cada puzle
        for (i = 0; i < juego->num_puzles; i++){
            leer_linea(f, juego->puzles[i].id_puzzle, 5);
            leer_linea(f, juego->puzles[i].nomb_puzle, 30);
            leer_linea(f, juego->puzles[i].id_sala, 5);
            leer_linea(f, juego->puzles[i].tipo, 20);
            leer_linea(f, juego->puzles[i].descrip, 200);
            leer_linea(f, juego->puzles[i].solucion, 51);
            leer_linea(f, linea, 256); 
            // Lee si el puzle ya fue resuelto
            juego->puzles[i].resuelto = atoi(linea);
        }
        fclose(f);
        printf("    [OK] Puzles cargados: %d\n", juego->num_puzles);
    } else {
        printf("    [ERROR] No se pudo abrir puzles.txt\n");
    }

    // ========== CARGAR CONEXIONES ==========
    f = fopen("conexion.txt", "r");
    if (f != NULL){
        // Lee el número total de conexiones
        leer_linea(f, linea, 256);
        juego->num_conexiones = atoi(linea);
        // Reserva memoria para las conexiones
        juego->conexiones = (Conexion *)malloc(juego->num_conexiones * sizeof(Conexion));

        // Lee cada conexión
        for (i = 0; i < juego->num_conexiones; i++){
            leer_linea (f, juego->conexiones[i].id_conexion, 5);
            leer_linea (f, juego->conexiones[i].id_origen, 5);
            leer_linea (f, juego->conexiones[i].id_destino, 5);
            leer_linea (f, juego->conexiones[i].estado, 15);
            leer_linea (f, juego->conexiones[i].condicion, 20);
        }
        fclose(f);
        printf("    [OK] Conexiones cargadas: %d\n", juego->num_conexiones);
    } else {
        printf("    [ERROR] No se pudo abrir conexion.txt\n");
    }
}

void guardar_ficheros_juego(EstadoJuego *juego){
    printf("Guardando partida en progreso...\n");
}