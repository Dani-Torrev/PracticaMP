#ifndef AUTENTIFICADOR_H
#define AUTENTIFICADOR_H

// Constantes basadas en los requerimientos del fichero Jugadores.txt [4, 5]
#define MAX_NOMBRE 21
#define MAX_USER 11
#define MAX_PASS 9

// Definición del tipo Jugador para que coincida con los prototipos
typedef struct {
    int id_jugador;                // Identificador de 2 dígitos [4]
    char nomb_jugador[MAX_NOMBRE]; // Máximo 20 caracteres [4]
    char usuario[MAX_USER];        // Máximo 10 caracteres [4]
    char contrasena[MAX_PASS];     // Máximo 8 caracteres [4]
} Jugador;

// Prototipos de las funciones (Interfaz del módulo)

/**
 * Función: cargarJugadores
 * Descripción: Carga la lista de jugadores desde un archivo de texto
 * 
 * Precondiciones:
 *   - numJugadores debe ser un puntero válido a un entero inicializado en 0
 *   - El archivo "Jugadores.txt" debe existir en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - Devuelve un puntero a un array dinámico de Jugador
 *   - numJugadores se actualiza con la cantidad de jugadores cargados
 *   - En caso de error, devuelve NULL y numJugadores permanece sin cambios
 */
Jugador* cargarJugadores(int *numJugadores);

/**
 * Función: verificarAcceso
 * Descripción: Verifica las credenciales de un usuario en la lista de jugadores
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Jugador (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de jugadores en la lista
 *   - user debe ser una cadena válida (no NULL)
 *   - pass debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Devuelve el ID del jugador si se encuentran credenciales válidas
 *   - Devuelve -1 si las credenciales no coinciden o no se encuentra el usuario
 *   - La lista no se modifica
 */
int verificarAcceso(Jugador *lista, int n, char *user, char *pass);

/**
 * Función: registrarJugador
 * Descripción: Registra un nuevo jugador solicitando sus datos por teclado
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un puntero de Jugador
 *   - n debe ser un puntero válido a un entero con la cantidad actual de jugadores
 *   - *lista debe ser memoria válida (puede ser NULL inicialmente)
 * 
 * Postcondiciones:
 *   - Se crea un nuevo Jugador con datos ingresados por el usuario
 *   - Se realoca memoria para añadir el nuevo jugador
 *   - Se incrementa el valor de *n en 1
 *   - Los datos se guardan automáticamente en el archivo Jugadores.txt
 *   - En caso de error de memoria, se imprime un mensaje y no se realiza cambio
 */
void registrarJugador(Jugador **lista, int *n);

/**
 * Función: guardarJugadores
 * Descripción: Guarda la lista de jugadores en el archivo Jugadores.txt
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Jugador
 *   - n debe ser la cantidad válida de jugadores en la lista
 *   - Se tiene permiso de escritura en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - El archivo Jugadores.txt se crea o sobrescribe con los datos actuales
 *   - Cada jugador se guarda con formato: ID-nombre-usuario-contraseña
 *   - El archivo se cierra correctamente después de escribir
 *   - Se imprime un mensaje confirmando el guardado o indicando error
 */
void guardarJugadores(Jugador *lista, int n); 

/**
 * Función: liberarJugadores
 * Descripción: Libera la memoria dinámica asignada a la lista de jugadores
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array dinámico de Jugador (puede ser NULL)
 * 
 * Postcondiciones:
 *   - La memoria asignada a la lista se libera
 *   - lista queda inválida y no debe usarse después
 */
void liberarJugadores(Jugador *lista);

/**
 * Función: obtenerJugadorPorId
 * Descripción: Busca y devuelve un puntero al jugador con el ID especificado
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Jugador (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de jugadores en la lista
 *   - id debe ser un entero positivo válido
 * 
 * Postcondiciones:
 *   - Devuelve un puntero al Jugador si se encuentra el ID
 *   - Devuelve NULL si no se encuentra el ID o la lista está vacía
 *   - La lista no se modifica
 */
Jugador* obtenerJugadorPorId(Jugador *lista, int n, int id);

/**
 * Función: esIdUnico
 * Descripción: Verifica si un ID de jugador es único en la lista
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Jugador (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de jugadores en la lista
 *   - id debe ser un entero positivo válido
 * 
 * Postcondiciones:
 *   - Devuelve 1 si el ID es único (no existe en la lista)
 *   - Devuelve 0 si el ID ya existe en la lista
 *   - La lista no se modifica
 */
int esIdUnico(Jugador *lista, int n, int id); 

#endif