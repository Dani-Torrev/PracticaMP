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

Usuario* cargarJugadores(int *numJugadores); 
int verificarAcceso(Usuario *lista, int n, char *user, char *pass); 
void registrarJugador(Usuario **lista, int *n);  
void guardarJugadores(Usuario *lista, int n); 
void liberarJugadores(Usuario *lista); 
Usuario* obtenerJugadorPorId(Usuario *lista, int n, int id); 
int esIdUnico(Usuario *lista, int n, int id); 

#endif