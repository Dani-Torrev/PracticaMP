#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_de_ficheros.h"


void leer_linea(FILE *f, char *buffer, int max_letras) {
    if (fgets(buffer, max_letras, f) != NULL){
        buffer[strcspn(buffer, "\n")] = 0;
        buffer[strcspn(buffer, "\r")] = 0;
    }
}

void cargar_ficheros_juego(EstadoJuego *juego){
    FILE *f;
    char linea[200];
    int i;


    printf("Cargando base de datos del juego...\n");

    f = fopen("salas.txt", "r");
    juego->salas = NULL;
    juego->num_salas = 0;
    
    if (f != NULL){
        while (fgets(linea, sizeof(linea), f) != NULL){
            linea[strcspn(linea, "\n")] = 0;
            linea[strcspn(linea, "\r")] = 0;

            if(strlen(linea) == 0) continue;

            juego->salas = (Sala *)realloc(juego->salas, (juego->num_salas + 1) * sizeof(Sala));

            strncpy(juego->salas[juego->num_salas].id_sala, linea, 3);
            leer_linea(f, juego->salas[juego->num_salas].nombre, 31);
            leer_linea(f, juego->salas[juego->num_salas].tipo, 10);
            leer_linea(f, juego->salas[juego->num_salas].descripcion, 151);

            juego->num_salas++;        
        }
        fclose(f);
        printf("    [OK] Salas cargadas: %d\n", juego->num_salas);
    }else{
        printf("    [ERROR] No se pudo abrir salas.txt\n");
    }

    f = fopen("puzles.txt", "r");
    if (f != NULL){
        leer_linea(f, linea, 200);
        juego->num_puzles = atoi(linea);
        juego->puzles = (Puzle *)malloc(juego->num_puzles * sizeof(Puzle));

        for (i = 0; i < juego->num_puzles; i++){
            leer_linea(f, juego->puzles[i].id_puzzle, 4);
            leer_linea(f, juego->puzles[i].nomb_puzle, 16);
            leer_linea(f, juego->puzles[i].id_sala, 5);
            leer_linea(f, juego->puzles[i].tipo, 20);
            leer_linea(f, juego->puzles[i].descrip, 151);
            leer_linea(f, juego->puzles[i].solucion, 4);
            leer_linea(f, linea, 200); juego->puzles[i].resuelto = atoi(linea);
        }
        fclose(f);
        printf("    [OK] Puzles cargados: %d\n", juego->num_puzles);
    }else{
        printf("    [ERROR] No se pudo nabrir puzles.txt\n");
    }


    f = fopen("conexion.txt", "r");
    if (f != NULL){
        leer_linea(f, linea, 200);
        juego->num_conexiones = atoi(linea);
        juego->conexiones = (Conexion *)malloc(juego->num_conexiones * sizeof(Conexion));

        for (i = 0; i < juego->num_conexiones; i++){
            leer_linea (f, juego->conexiones[i].id_conexion, 4);
            leer_linea (f, juego->conexiones[i].id_origen, 3);
            leer_linea (f, juego->conexiones[i].id_destino, 3);
            leer_linea (f, juego->conexiones[i].estado, 10);
            leer_linea (f, juego->conexiones[i].condicion, 10);
        }
        fclose(f);
        printf("    [OK] Conexiones cargadas: %d\n", juego->num_conexiones);
    }else{
        printf("    [ERROR] No se pudo abrir conexion.txt\n");
    }
}

void guardar_ficheros_juego(EstadoJuego *juego){
    printf("Guardando partida en progreso...\n");
}
