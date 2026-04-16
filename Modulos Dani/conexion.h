#ifndef CONEXION_H
#define CONEXION_H

// Estructura para las conexiones 
typedef struct {
    char id_conexion[4];   
    char id_origen[3];     
    char id_destino[3];    
    char estado[10];      
    char condicion[10];   
} Conexion; 

// Prototipos de funciones

/**
 * Función: esta_abierta
 * Descripción: Comprueba si una conexión está abierta
 * 
 * Precondiciones:
 *   - c debe ser una estructura Conexion válida
 * 
 * Postcondiciones:
 *   - Devuelve 1 si la conexión está abierta, 0 en caso contrario
 *   - La estructura c no se modifica
 */
int esta_abierta(Conexion c);

/**
 * Función: abrir_paso
 * Descripción: Abre una conexión para permitir el paso
 * 
 * Precondiciones:
 *   - c debe ser un puntero válido a una estructura Conexion
 * 
 * Postcondiciones:
 *   - El estado de la conexión en c se actualiza a abierto
 *   - Se modifica la estructura apuntada por c
 */
void abrir_paso(Conexion *c);

/**
 * Función: requiere_objeto
 * Descripción: Comprueba si una conexión requiere un objeto específico
 * 
 * Precondiciones:
 *   - c debe ser una estructura Conexion válida
 *   - id_objeto debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Devuelve 1 si la conexión requiere el objeto, 0 en caso contrario
 *   - La estructura c no se modifica
 */
int requiere_objeto(Conexion c, char* id_objeto);

/**
 * Función: tiene_puzzle
 * Descripción: Comprueba si una conexión tiene un puzzle asociado
 * 
 * Precondiciones:
 *   - c debe ser una estructura Conexion válida
 *   - id_puzzle debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Devuelve 1 si la conexión está ligada al puzzle, 0 en caso contrario
 *   - La estructura c no se modifica
 */
int tiene_puzzle(Conexion c, char* id_puzzle);

#endif