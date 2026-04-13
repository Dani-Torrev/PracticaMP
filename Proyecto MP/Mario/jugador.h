#ifndef JUGADOR_H
#define JUGADOR_H
#define MAX_ID_SALA 3
#define MAX_ID_OBJ 5
#define MAX_NOMBRE_J 21

typedef struct {
    int id_jugador;
    char nombre[MAX_NOMBRE_J];
    char sala_actual[MAX_ID_SALA]; 
    char **inventario;        
    int num_objetos;
} JugadorActivo;

/**
 * Función: inicializarJugador
 * Descripción: Inicializa un jugador activo con los datos proporcionados
 * 
 * Precondiciones:
 *   - j debe ser un puntero válido a una estructura JugadorActivo
 *   - id debe ser un entero positivo válido
 *   - nombre debe ser una cadena válida (no NULL) de máximo 20 caracteres
 *   - sala_inicio debe ser una cadena válida (no NULL) de máximo 2 caracteres
 * 
 * Postcondiciones:
 *   - La estructura j se inicializa con los valores proporcionados
 *   - El inventario se inicializa vacío (NULL)
 *   - num_objetos se establece en 0
 */
void inicializarJugador(JugadorActivo *j, int id, char *nombre, char *sala_inicio);

/**
 * Función: actualizarPosicion
 * Descripción: Actualiza la sala actual del jugador
 * 
 * Precondiciones:
 *   - j debe ser un puntero válido a una estructura JugadorActivo inicializada
 *   - nueva_sala debe ser una cadena válida (no NULL) de máximo 2 caracteres
 * 
 * Postcondiciones:
 *   - El campo sala_actual de j se actualiza con nueva_sala
 *   - El resto de la estructura permanece sin cambios
 */
void actualizarPosicion(JugadorActivo *j, char *nueva_sala);

/**
 * Función: añadirObjeto
 * Descripción: Añade un objeto al inventario del jugador
 * 
 * Precondiciones:
 *   - j debe ser un puntero válido a una estructura JugadorActivo inicializada
 *   - id_obj debe ser una cadena válida (no NULL) de máximo 4 caracteres
 * 
 * Postcondiciones:
 *   - Si hay memoria disponible y el objeto no está duplicado, se añade al inventario
 *   - num_objetos se incrementa en 1
 *   - Devuelve 1 si se añade correctamente, 0 en caso de error
 *   - En caso de error, la estructura no se modifica
 */
int añadirObjeto(JugadorActivo *j, char *id_obj);

/**
 * Función: quitarObjeto
 * Descripción: Quita un objeto del inventario del jugador
 * 
 * Precondiciones:
 *   - j debe ser un puntero válido a una estructura JugadorActivo inicializada
 *   - id_obj debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Si el objeto existe en el inventario, se elimina
 *   - num_objetos se decrementa en 1
 *   - Devuelve 1 si se quita correctamente, 0 si no se encuentra el objeto
 *   - En caso de no encontrar el objeto, la estructura no se modifica
 */
int quitarObjeto(JugadorActivo *j, char *id_obj);

/**
 * Función: tieneObjeto
 * Descripción: Verifica si el jugador tiene un objeto específico en su inventario
 * 
 * Precondiciones:
 *   - j debe ser un puntero válido a una estructura JugadorActivo inicializada
 *   - id_obj debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Devuelve 1 si el objeto está en el inventario, 0 si no
 *   - La estructura no se modifica
 */
int tieneObjeto(JugadorActivo *j, char *id_obj);

/**
 * Función: liberarMemoriaJugador
 * Descripción: Libera la memoria dinámica asignada al jugador
 * 
 * Precondiciones:
 *   - j debe ser un puntero válido a una estructura JugadorActivo (puede estar inicializada o no)
 * 
 * Postcondiciones:
 *   - Toda la memoria dinámica asignada al inventario se libera
 *   - La estructura j queda en un estado no válido para uso posterior
 */
void liberarMemoriaJugador(JugadorActivo *j);

#endif