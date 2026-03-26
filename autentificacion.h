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
} Jugador;

Jugador* cargarJugadores(int *numJugadores); 
int verificarAcceso(Jugador *lista, int n, char *user, char *pass); 
void registrarJugador(Jugador **lista, int *n);  
void guardarJugadores(Jugador *lista, int n); 
void liberarJugadores(Jugador *lista); 
Jugador* obtenerJugadorPorId(Jugador *lista, int n, int id); 
int esIdUnico(Jugador *lista, int n, int id); 

#endif