#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autentificacion.h"

// Carga los jugadores desde el archivo Jugadores.txt
Usuario* cargarJugadores(int *numJugadores) {
    FILE *f;
    char linea[256];
    Usuario *lista = NULL;
    *numJugadores = 0;

    // Intenta abrir el archivo de jugadores
    f = fopen("Jugadores.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir Jugadores.txt [2].\n");
        return NULL;
    }

    // Lee cada línea del archivo
    while (fgets(linea, sizeof(linea), f) != NULL) {
        // Elimina el salto de línea
        linea[strcspn(linea, "\n")] = 0;

        // Reserva memoria para un nuevo usuario
        Usuario *aux = (Usuario *)realloc(lista, (*numJugadores + 1) * sizeof(Usuario));
        if (aux == NULL) {
            printf("Error de memoria dinámica al cargar jugadores [1].\n");
            fclose(f);
            return lista; 
        }
        lista = aux;

        // Parsea la línea usando guiones como separador
        char *token = strtok(linea, "-");
        if (token != NULL) {
            // Extrae el ID del jugador
            lista[*numJugadores].id_jugador = atoi(token);

            // Extrae el nombre del jugador
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].nomb_jugador, token, MAX_NOMBRE - 1);

            // Extrae el nombre de usuario
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].usuario, token, MAX_USER - 1);

            // Extrae la contraseña
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].contrasena, token, MAX_PASS - 1);

            (*numJugadores)++;
        }
    }

    fclose(f);
    return lista;
}

// Verifica si las credenciales de usuario y contraseña son válidas
int verificarAcceso(Usuario *lista, int n, char *user, char *pass) {
    int i;
    // Recorre todos los usuarios registrados
    for (i = 0; i < n; i++) {
        // Compara usuario y contraseña con los de la base de datos
        if (strcmp(lista[i].usuario, user) == 0 && strcmp(lista[i].contrasena, pass) == 0) {
            // Credenciales válidas, devuelve el ID
            return lista[i].id_jugador;
        }
    }
    // No se encontraron credenciales válidas
    return -1;
}

// Registra un nuevo jugador en el sistema
void registrarJugador(Usuario **lista, int *n) {
    Usuario nuevo;
    printf("\n--- REGISTRO DE NUEVO JUGADOR ---\n");

    // Asigna un ID único basado en el número actual de usuarios
    nuevo.id_jugador = (*n) + 1;

    // Solicita el nombre completo del jugador
    printf("Introduce tu nombre completo (max 20 caracteres): ");
    scanf(" %20[^\n]", nuevo.nomb_jugador); 

    // Solicita el nombre de usuario
    printf("Introduce nombre de usuario (max 10 caracteres): ");
    scanf("%10s", nuevo.usuario);

    // Solicita la contraseña
    printf("Introduce contraseña (max 8 caracteres): ");
    scanf("%8s", nuevo.contrasena);

    // Intenta expandir la lista de usuarios
    Usuario *aux = (Usuario *)realloc(*lista, (*n + 1) * sizeof(Usuario));
    if (aux != NULL) {
        *lista = aux;
        (*lista)[*n] = nuevo; 
        (*n)++;               
        
        printf("\nRegistro completado. Bienvenido al sistema [5].\n");
        // Guarda inmediatamente para persistencia de datos
        guardarJugadores(*lista, *n);
    } else {
        printf("Error crítico: Fallo de memoria en el registro [1].\n");
    }
}

// Guarda la lista de jugadores en el archivo Jugadores.txt
void guardarJugadores(Usuario *lista, int n) {
    // Abre el archivo en modo escritura (sobrescribe si existe)
    FILE *f = fopen("Jugadores.txt", "w"); 

    if (f == NULL) {
        printf("Error: No se pudo guardar la información en Jugadores.txt [2].\n");
        return;
    }

    // Escribe cada usuario en una línea con formato ID-NOMBRE-USUARIO-CONTRASEÑA
    for (int i = 0; i < n; i++) {
        fprintf(f, "%02d-%s-%s-%s", 
                lista[i].id_jugador, 
                lista[i].nomb_jugador, 
                lista[i].usuario, 
                lista[i].contrasena);
        
        fprintf(f, "\n");
    }

    fclose(f);
}

// Libera la memoria dinámica asignada a la lista de jugadores
void liberarJugadores(Usuario *lista) {
    // Comprueba que la lista no sea nula antes de liberar
    if (lista != NULL) {
        free(lista);
    }
}

// Obtiene un jugador específico por su ID
Usuario* obtenerJugadorPorId(Usuario *lista, int n, int id) {
    int i;
    // Busca el usuario con el ID especificado
    for (i = 0; i < n; i++) {
        if (lista[i].id_jugador == id) {
            // Usuario encontrado, devuelve su dirección
            return &lista[i];
        }
    }
    // Usuario no encontrado
    return NULL;
}

// Verifica si un ID de jugador es único en la lista
int esIdUnico(Usuario *lista, int n, int id) {
    int i;
    // Recorre todos los usuarios
    for (i = 0; i < n; i++) {
        // Si encuentra un ID coincidente, no es único
        if (lista[i].id_jugador == id) {
            return 0;
        }
    }
    // ID no encontrado, es único
    return 1;
}