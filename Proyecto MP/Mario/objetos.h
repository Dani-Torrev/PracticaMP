#ifndef OBJETOS_H
#define OBJETOS_H

#define MAX_ID_OBJ 5     
#define MAX_NOMB_OBJ 16   
#define MAX_DESC_OBJ 51   
#define MAX_LOCALIZ 11    

typedef struct {
    char id_obj[MAX_ID_OBJ];
    char nomb_obj[MAX_NOMB_OBJ];
    char descrip[MAX_DESC_OBJ];
    char localiz[MAX_LOCALIZ]; 
} Objeto;

// Prototipos de las funciones

/**
 * Función: cargarObjetos
 * Descripción: Carga la lista de objetos desde un archivo de texto
 * 
 * Precondiciones:
 *   - numObjetos debe ser un puntero válido a un entero inicializado en 0
 *   - El archivo de objetos debe existir en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - Devuelve un puntero a un array dinámico de Objeto
 *   - numObjetos se actualiza con la cantidad de objetos cargados
 *   - En caso de error, devuelve NULL y numObjetos permanece sin cambios
 */
Objeto* cargarObjetos(int *numObjetos);

/**
 * Función: listarObjetosEnSala
 * Descripción: Lista los objetos disponibles en una sala específica
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Objeto (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de objetos en la lista
 *   - id_sala debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Se imprime por pantalla la lista de objetos en la sala especificada
 *   - La lista no se modifica
 */
void listarObjetosEnSala(Objeto *lista, int n, char *id_sala);

/**
 * Función: listarInventario
 * Descripción: Lista todos los objetos en el inventario
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Objeto (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de objetos en la lista
 * 
 * Postcondiciones:
 *   - Se imprime por pantalla la lista de objetos en el inventario
 *   - La lista no se modifica
 */
void listarInventario(Objeto *lista, int n);

/**
 * Función: cogerObjeto
 * Descripción: Permite coger un objeto de la sala actual y añadirlo al inventario
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Objeto
 *   - n debe ser la cantidad válida de objetos en la lista
 *   - id_obj debe ser una cadena válida (no NULL)
 *   - id_sala_actual debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Si el objeto existe en la sala, su localización se actualiza
 *   - Devuelve 1 si se coge correctamente, 0 si no se encuentra o hay error
 *   - La lista se modifica si se realiza la acción
 */
int cogerObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual);

/**
 * Función: soltarObjeto
 * Descripción: Permite soltar un objeto del inventario a la sala actual
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Objeto
 *   - n debe ser la cantidad válida de objetos en la lista
 *   - id_obj debe ser una cadena válida (no NULL)
 *   - id_sala_actual debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Si el objeto está en el inventario, su localización se actualiza a la sala actual
 *   - Devuelve 1 si se suelta correctamente, 0 si no se encuentra o hay error
 *   - La lista se modifica si se realiza la acción
 */
int soltarObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual);

/**
 * Función: verificarUsoObjeto
 * Descripción: Verifica si un objeto necesario está disponible para su uso
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Objeto (puede ser NULL si n=0)
 *   - n debe ser la cantidad válida de objetos en la lista
 *   - id_obj_necesario debe ser una cadena válida (no NULL)
 * 
 * Postcondiciones:
 *   - Devuelve 1 si el objeto está disponible para uso, 0 si no
 *   - La lista no se modifica
 */
int verificarUsoObjeto(Objeto *lista, int n, char *id_obj_necesario);

/**
 * Función: liberarObjetos
 * Descripción: Libera la memoria dinámica asignada a la lista de objetos
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array dinámico de Objeto (puede ser NULL)
 * 
 * Postcondiciones:
 *   - La memoria asignada a la lista se libera
 *   - lista queda inválida y no debe usarse después
 */
void liberarObjetos(Objeto *lista);

/**
 * Función: guardarObjetos
 * Descripción: Guarda la lista de objetos en un archivo de texto
 * 
 * Precondiciones:
 *   - lista debe ser un puntero válido a un array de Objeto
 *   - n debe ser la cantidad válida de objetos en la lista
 *   - Se tiene permiso de escritura en el directorio de trabajo
 * 
 * Postcondiciones:
 *   - El archivo de objetos se crea o sobrescribe con los datos actuales
 *   - Se imprime un mensaje confirmando el guardado o indicando error
 */
void guardarObjetos(Objeto *lista, int n); 

#endif
