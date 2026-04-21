#ifndef autentificacion_h
#define autentificacion_h
#define MAX_NOMBRE 21
#define MAX_USER 11
#define MAX_PASS 9

typedef struct {
    int id_jugador;                
    char nomb_jugador[MAX_NOMBRE];
    char usuario[MAX_USER];        
    char contrasena[MAX_PASS];     
} Usuario;

/*
 * Cabecera: Carga los jugadores desde el archivo Jugadores.txt
 * Pre-condición: numJugadores no debe ser NULL
 * Post-condición: Retorna un arreglo con los usuarios cargados, 
 *                 numJugadores contiene la cantidad de usuarios leídos
 */
Usuario* cargarJugadores(int *numJugadores); 

/*
 * Cabecera: Verifica si las credenciales de usuario y contraseña son válidas
 * Pre-condición: lista no debe ser NULL, n >= 0, user y pass no deben ser NULL
 * Post-condición: Retorna el ID del jugador si es válido, -1 si no existe o fallan credenciales
 */
int verificarAcceso(Usuario *lista, int n, char *user, char *pass); 

/*
 * Cabecera: Registra un nuevo jugador en el sistema
 * Pre-condición: lista debe ser un puntero válido (puede ser NULL inicialmente), 
 *                n apunta a un entero con el número actual de usuarios
 * Post-condición: Se añade un nuevo usuario a la lista y se incrementa n
 */
void registrarJugador(Usuario **lista, int *n);  

/*
 * Cabecera: Guarda la lista de jugadores en el archivo Jugadores.txt
 * Pre-condición: lista no debe ser NULL, n > 0
 * Post-condición: El archivo Jugadores.txt contiene todos los usuarios actualizados
 */
void guardarJugadores(Usuario *lista, int n); 

/*
 * Cabecera: Libera la memoria dinámica asignada a la lista de jugadores
 * Pre-condición: lista puede ser NULL o apuntar a memoria dinámica válida
 * Post-condición: La memoria es liberada, lista queda no válida para usar
 */
void liberarJugadores(Usuario *lista); 

/*
 * Cabecera: Obtiene un jugador específico por su ID
 * Pre-condición: lista no debe ser NULL, n >= 0, id debe ser válido
 * Post-condición: Retorna puntero al usuario encontrado o NULL si no existe
 */
Usuario* obtenerJugadorPorId(Usuario *lista, int n, int id); 

/*
 * Cabecera: Verifica si un ID de jugador es único en la lista
 * Pre-condición: lista no debe ser NULL, n >= 0
 * Post-condición: Retorna 1 si el ID es único, 0 si ya existe en la lista
 */
int esIdUnico(Usuario *lista, int n, int id); 

#endif