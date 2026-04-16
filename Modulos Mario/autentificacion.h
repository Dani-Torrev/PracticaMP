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

/**
 * Función: cargarJugadores
 * Descripción: Carga la lista de usuarios desde un archivo de texto
 * 
 * Precondiciones:
 *   - numJugadores debe ser un puntero válido a un entero inicializado en 0
 *   - El archivo "Jugadores.txt" debe existir en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - Devuelve un puntero a un array dinámico de Usuario
 *   - numJugadores se actualiza con la cantidad de usuarios cargados
 *   - En caso de error, devuelve NULL y numJugadores permanece sin cambios
 */
Usuario* cargarJugadores(int *numJugadores); 

/**
 * Función: verificarAcceso
 * Descripción: Verifica las credenciales de un usuario en la lista de usuarios
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Usuario (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de usuarios en la lista
 *   - user debe ser una cadena válida (no NULL)
 *   - pass debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Devuelve el ID del usuario si se encuentran credenciales válidas
 *   - Devuelve -1 si las credenciales no coinciden o no se encuentra el usuario
 *   - La lista no se modifica
 */
int verificarAcceso(Usuario *lista, int n, char *user, char *pass); 

/**
 * Función: registrarJugador
 * Descripción: Registra un nuevo usuario en la lista
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un puntero de Usuario
 *   - n debe ser un puntero válido a un entero con la cantidad actual de usuarios
 * 
 * Postcondiciones:
 *   - Se añade un nuevo usuario a la lista si es válido
 *   - n se incrementa si se registra correctamente
 *   - La lista se redimensiona dinámicamente
 */
void registrarJugador(Usuario **lista, int *n);  

/**
 * Función: guardarJugadores
 * Descripción: Guarda la lista de usuarios en un archivo de texto
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Usuario
 *   - n debe ser la cantidad válida de usuarios en la lista
 *   - Se tiene permiso de escritura en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - El archivo de usuarios se crea o sobrescribe con los datos actuales
 *   - Se imprime un mensaje confirmando el guardado o indicando error
 */
void guardarJugadores(Usuario *lista, int n); 

/**
 * Función: liberarJugadores
 * Descripción: Libera la memoria dinámica asignada a la lista de usuarios
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array dinámico de Usuario (puede ser NULL)
 * 
 * Postcondiciones:
 *   - La memoria asignada a la lista se libera
 *   - lista queda inválida y no debe usarse después
 */
void liberarJugadores(Usuario *lista); 

/**
 * Función: obtenerJugadorPorId
 * Descripción: Obtiene un usuario de la lista por su ID
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Usuario
 *   - n debe ser la cantidad válida de usuarios en la lista
 *   - id debe ser un ID válido
 * 
 * Postcondiciones:
 *   - Devuelve un puntero al usuario si se encuentra
 *   - Devuelve NULL si no se encuentra el usuario
 *   - La lista no se modifica
 */
Usuario* obtenerJugadorPorId(Usuario *lista, int n, int id); 

/**
 * Función: esIdUnico
 * Descripción: Verifica si un ID es único en la lista de usuarios
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Usuario (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de usuarios en la lista
 *   - id debe ser un entero
 * 
 * Postcondiciones:
 *   - Devuelve 1 si el ID es único, 0 si ya existe
 *   - La lista no se modifica
 */
int esIdUnico(Usuario *lista, int n, int id); 

#endif