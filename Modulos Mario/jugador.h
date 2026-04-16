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
} Jugador;

void inicializarJugador(Jugador *j, int id, char *nombre, char *sala_inicio);
void actualizarPosicion(Jugador *j, char *nueva_sala);
int anadirObjeto(Jugador *j, char *id_obj);
int quitarObjeto(Jugador *j, char *id_obj);
int tieneObjeto(Jugador *j, char *id_obj);
void liberarMemoriaJugador(Jugador *j);

#endif