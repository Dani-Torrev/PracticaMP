#ifndef CONEXION_H
#define CONEXION_H

typedef struct {
    char id_conexion[5];   
    char id_origen[5];     
    char id_destino[5];    
    char estado[15];      
    char condicion[20]; // Espacio de sobra para objetos y puzles
} Conexion; 

/*
 * Cabecera: Verifica si una conexión está abierta
 * Pre-condición: Ninguna (estructura por valor)
 * Post-condición: Retorna 1 si la conexión está abierta, 0 en caso contrario
 */
int esta_abierta(Conexion c);

/*
 * Cabecera: Abre una conexión entre salas
 * Pre-condición: c no debe ser NULL
 * Post-condición: El estado de la conexión cambia a "abierta"
 */
void abrir_paso(Conexion *c);

/*
 * Cabecera: Verifica si una conexión requiere un objeto específico para abrirse
 * Pre-condición: id_objeto no debe ser NULL
 * Post-condición: Retorna 1 si la conexión requiere el objeto, 0 en caso contrario
 */
int requiere_objeto(Conexion c, char* id_objeto);

/*
 * Cabecera: Verifica si una conexión tiene un puzle asociado
 * Pre-condición: id_puzzle no debe ser NULL
 * Post-condición: Retorna 1 si la conexión tiene el puzle, 0 en caso contrario
 */
int tiene_puzzle(Conexion c, char* id_puzzle);

#endif