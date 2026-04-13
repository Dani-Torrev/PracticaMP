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
int esta_abierta(Conexion c);
void abrir_paso(Conexion *c);
int requiere_objeto(Conexion c, char* id_objeto);
int tiene_puzzle(Conexion c, char* id_puzzle);
Conexion* cargar_conexiones(int *num_conexiones);
#endif