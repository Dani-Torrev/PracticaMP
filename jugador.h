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

void inicializarJugador(JugadorActivo *j, int id, char *nombre, char *sala_inicio);
void actualizarPosicion(JugadorActivo *j, char *nueva_sala);
int añadirObjeto(JugadorActivo *j, char *id_obj);
int quitarObjeto(JugadorActivo *j, char *id_obj);
int tieneObjeto(JugadorActivo *j, char *id_obj);
void liberarMemoriaJugador(JugadorActivo *j);

#endif