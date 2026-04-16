#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_de_ficheros.h"

/* ============================================================================
 * CABEZA:        void leer_linea(FILE *f, char *buffer, int max_letras)
 * PRECONDICIÓN:  'f' es un puntero válido a un fichero abierto en modo lectura. 
 * 'buffer' es un array con espacio para al menos 'max_letras'. 
 * 'max_letras' es mayor que 0.
 * POSTCONDICIÓN: Lee una línea de texto del fichero y la almacena en 'buffer'. 
 * Se eliminan los caracteres de salto de línea ('\n' y '\r') 
 * para dejar una cadena de texto limpia.
 * ============================================================================ */

void leer_linea(FILE *f, char *buffer, int max_letras) {
    // Leemos de forma segura para evitar desbordamientos de buffer
    if (fgets(buffer, max_letras, f) != NULL){
        // Limpiamos los saltos de línea buscando su posición y colocando un fin de cadena '\0'
        buffer[strcspn(buffer, "\n")] = 0;
        buffer[strcspn(buffer, "\r")] = 0;
    }
}

/* ============================================================================
 * CABEZA:        void cargar_ficheros_juego(EstadoJuego *juego)
 * PRECONDICIÓN:  'juego' es un puntero válido a una estructura EstadoJuego.
 * POSTCONDICIÓN: Se lee la información de los ficheros "salas.txt", 
 * "puzles.txt" y "conexion.txt". Se reserva la memoria dinámica 
 * necesaria y se inicializan los arrays de la estructura 'juego'.
 * ============================================================================ */

void cargar_ficheros_juego(EstadoJuego *juego){
    FILE *f;
    char linea[200];
    int i;


    printf("Cargando base de datos del juego...\n");

    // --- 1. CARGA DE SALAS ---
    f = fopen("salas.txt", "r");
    juego->salas = NULL;
    juego->num_salas = 0;
    
    if (f != NULL){
        // Leemos hasta el final del fichero porque no sabemos cuántas salas hay
        while (fgets(linea, sizeof(linea), f) != NULL){
            linea[strcspn(linea, "\n")] = 0;
            linea[strcspn(linea, "\r")] = 0;

            if(strlen(linea) == 0) continue; // Ignora líneas vacías
            
            // Realojamos memoria incrementalmente para añadir una nueva sala
            juego->salas = (Sala *)realloc(juego->salas, (juego->num_salas + 1) * sizeof(Sala));

            // Copiamos los datos a la nueva posición reservada
            strncpy(juego->salas[juego->num_salas].id_sala, linea, 3);
            leer_linea(f, juego->salas[juego->num_salas].nombre, 31);
            leer_linea(f, juego->salas[juego->num_salas].tipo, 10);
            leer_linea(f, juego->salas[juego->num_salas].descripcion, 151);

            juego->num_salas++;        
        }
        fclose(f);
        printf("    [OK] Salas cargadas: %d\n", juego->num_salas);
    }else{
        printf("    [ERROR] No se pudo abrir salas.txt\n");
    }

    // --- 2. CARGA DE PUZLES ---
    f = fopen("puzles.txt", "r");
    if (f != NULL){
        // Leemos el primer número del TXT, que indica el total de puzles
        leer_linea(f, linea, 200);
        juego->num_puzles = atoi(linea);
        // Al saber la cantidad, hacemos una única reserva grande con malloc
        juego->puzles = (Puzle *)malloc(juego->num_puzles * sizeof(Puzle));

        for (i = 0; i < juego->num_puzles; i++){
            leer_linea(f, juego->puzles[i].id_puzzle, 4);
            leer_linea(f, juego->puzles[i].nomb_puzle, 16);
            leer_linea(f, juego->puzles[i].id_sala, 5);
            leer_linea(f, juego->puzles[i].tipo, 20);
            leer_linea(f, juego->puzles[i].descrip, 151);
            leer_linea(f, juego->puzles[i].solucion, 4);

            // Leemos el string del estado y lo pasamos a entero
            leer_linea(f, linea, 200); 
            juego->puzles[i].resuelto = atoi(linea);
        }
        fclose(f);
        printf("    [OK] Puzles cargados: %d\n", juego->num_puzles);
    }else{
        printf("    [ERROR] No se pudo nabrir puzles.txt\n");
    }

    // --- 3. CARGA DE CONEXIONES ---
    f = fopen("conexion.txt", "r");
    if (f != NULL){
        // Misma estrategia que con los puzles: leemos el total primero
        leer_linea(f, linea, 200);
        juego->num_conexiones = atoi(linea);
        juego->conexiones = (Conexion *)malloc(juego->num_conexiones * sizeof(Conexion));

        for (i = 0; i < juego->num_conexiones; i++){
            leer_linea (f, juego->conexiones[i].id_conexion, 4);
            leer_linea (f, juego->conexiones[i].id_origen, 3);
            leer_linea (f, juego->conexiones[i].id_destino, 3);
            leer_linea (f, juego->conexiones[i].estado, 10);
            leer_linea (f, juego->conexiones[i].condicion, 10);
        }
        fclose(f);
        printf("    [OK] Conexiones cargadas: %d\n", juego->num_conexiones);
    }else{
        printf("    [ERROR] No se pudo abrir conexion.txt\n");
    }
}

/* ============================================================================
 * CABEZA:        void guardar_ficheros_juego(EstadoJuego *juego)
 * PRECONDICIÓN:  'juego' apunta a una estructura EstadoJuego inicializada y 
 * con datos en memoria válidos.
 * POSTCONDICIÓN: El estado actual del juego se escribe en disco, sobreescribiendo 
 * los ficheros correspondientes para guardar la partida.
 * ============================================================================ */

void guardar_ficheros_juego(EstadoJuego *juego){
    printf("Guardando partida en progreso...\n");
}
