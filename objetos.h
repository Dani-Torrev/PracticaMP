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
Objeto* cargarObjetos(int *numObjetos); 
void listarObjetosEnSala(Objeto *lista, int n, char *id_sala); 
void listarInventario(Objeto *lista, int n); 
int cogerObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual); 
int soltarObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual); 
int verificarUsoObjeto(Objeto *lista, int n, char *id_obj_necesario); 
void liberarObjetos(Objeto *lista); 
void guardarObjetos(Objeto *lista, int n); 

#endif
