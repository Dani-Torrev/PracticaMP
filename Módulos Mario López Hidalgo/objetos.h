#ifndef OBJETOS_H
#define OBJETOS_H

// ¡LIMITES AMPLIADOS!
#define MAX_ID_OBJ 20     
#define MAX_NOMB_OBJ 50   
#define MAX_DESC_OBJ 100   
#define MAX_LOCALIZ 20    

typedef struct {
    char id_obj[MAX_ID_OBJ];
    char nomb_obj[MAX_NOMB_OBJ];
    char descrip[MAX_DESC_OBJ];
    char localiz[MAX_LOCALIZ]; 
} Objeto;

/*
 * Cabecera: Carga todos los objetos desde el archivo Objetos.txt
 * Pre-condición: numObjetos no debe ser NULL
 * Post-condición: Retorna un arreglo con los objetos cargados, 
 *                 numObjetos contiene la cantidad de objetos leídos
 */
Objeto* cargarObjetos(int *numObjetos); 

/*
 * Cabecera: Lista todos los objetos disponibles en una sala específica
 * Pre-condición: lista no debe ser NULL, n >= 0, id_sala no debe ser NULL
 * Post-condición: Se muestran en pantalla los objetos de la sala indicada
 */
void listarObjetosEnSala(Objeto *lista, int n, char *id_sala); 

/*
 * Cabecera: Lista todos los objetos del inventario del jugador
 * Pre-condición: lista no debe ser NULL, n >= 0
 * Post-condición: Se muestran en pantalla los objetos del inventario
 */
void listarInventario(Objeto *lista, int n); 

/*
 * Cabecera: Permite coger un objeto de la sala actual
 * Pre-condición: lista no debe ser NULL, n >= 0, id_obj no debe ser NULL, 
 *                id_sala_actual no debe ser NULL
 * Post-condición: Retorna 1 si el objeto se cogió exitosamente, 0 si falla
 */
int cogerObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual); 

/*
 * Cabecera: Permite soltar un objeto en la sala actual
 * Pre-condición: lista no debe ser NULL, n >= 0, id_obj no debe ser NULL,
 *                id_sala_actual no debe ser NULL
 * Post-condición: Retorna 1 si el objeto se soltó exitosamente, 0 si falla
 */
int soltarObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual); 

/*
 * Cabecera: Verifica si un objeto es necesario para algo (uso válido)
 * Pre-condición: lista no debe ser NULL, n >= 0, id_obj_necesario no debe ser NULL
 * Post-condición: Retorna 1 si el objeto es necesario, 0 en caso contrario
 */
int verificarUsoObjeto(Objeto *lista, int n, char *id_obj_necesario); 

/*
 * Cabecera: Libera la memoria dinámica asignada a la lista de objetos
 * Pre-condición: lista puede ser NULL o apuntar a memoria dinámica válida
 * Post-condición: La memoria es liberada
 */
void liberarObjetos(Objeto *lista); 

/*
 * Cabecera: Guarda la lista de objetos en el archivo Objetos.txt
 * Pre-condición: lista no debe ser NULL, n > 0
 * Post-condición: El archivo Objetos.txt contiene todos los objetos actualizados
 */
void guardarObjetos(Objeto *lista, int n); 

#endif