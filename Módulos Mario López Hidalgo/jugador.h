#ifndef JUGADOR_H
#define JUGADOR_H

#include "objetos.h" // Heredamos el tamaño de 20 para que no choquen

#define MAX_ID_SALA 5 // Lo subimos a 5 para que coincida con el nuevo tamaño
#define MAX_NOMBRE_J 21

typedef struct {
    int id_jugador;
    char nombre[MAX_NOMBRE_J];
    char sala_actual[MAX_ID_SALA]; 
    char **inventario;        
    int num_objetos;
} Jugador;

/*
 * Cabecera: Inicializa un jugador con los datos básicos
 * Pre-condición: j no debe ser NULL, id >= 0, nombre y sala_inicio no deben ser NULL
 * Post-condición: El jugador es inicializado con inventario vacío
 */
void inicializarJugador(Jugador *j, int id, char *nombre, char *sala_inicio);

/*
 * Cabecera: Actualiza la sala actual donde se encuentra el jugador
 * Pre-condición: j no debe ser NULL, nueva_sala no debe ser NULL
 * Post-condición: El campo sala_actual del jugador es actualizado
 */
void actualizarPosicion(Jugador *j, char *nueva_sala);

/*
 * Cabecera: Añade un objeto al inventario del jugador
 * Pre-condición: j no debe ser NULL, id_obj no debe ser NULL
 * Post-condición: El objeto se añade al inventario si hay espacio, retorna 1 si éxito, 0 si falla
 */
int anadirObjeto(Jugador *j, char *id_obj);

/*
 * Cabecera: Quita un objeto del inventario del jugador
 * Pre-condición: j no debe ser NULL, id_obj no debe ser NULL
 * Post-condición: El objeto se elimina del inventario si existe, retorna 1 si éxito, 0 si falla
 */
int quitarObjeto(Jugador *j, char *id_obj);

/*
 * Cabecera: Verifica si el jugador tiene un objeto específico
 * Pre-condición: j no debe ser NULL, id_obj no debe ser NULL
 * Post-condición: Retorna 1 si el jugador tiene el objeto, 0 en caso contrario
 */
int tieneObjeto(Jugador *j, char *id_obj);

/*
 * Cabecera: Libera toda la memoria del jugador incluyendo su inventario
 * Pre-condición: j no debe ser NULL
 * Post-condición: El inventario y la estructura están liberados
 */
void liberarMemoriaJugador(Jugador *j);

#endif