// Includes para entrada/salida, memoria dinámica, strings y header de autenticación
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autentificacion.h"

// Función para cargar la lista de jugadores desde el archivo Jugadores.txt
Usuario* cargarJugadores(int *numJugadores) {
    // Declaración de variables: puntero al archivo, buffer para línea, lista de usuarios, contador
    FILE *f;
    char linea[256];
    Usuario *lista = NULL;
    *numJugadores = 0;

    // Abrimos el archivo en modo lectura
    f = fopen("Jugadores.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir Jugadores.txt [2].\n");
        return NULL;
    }

    // Leemos línea por línea del archivo
    while (fgets(linea, sizeof(linea), f) != NULL) {
        // Eliminamos el carácter de nueva línea
        linea[strcspn(linea, "\n")] = 0;

        // Redimensionamos la lista para añadir un nuevo usuario
        Usuario *aux = (Usuario *)realloc(lista, (*numJugadores + 1) * sizeof(Usuario));
        if (aux == NULL) {
            printf("Error de memoria dinámica al cargar jugadores [1].\n");
            fclose(f);
            return lista; 
        }
        lista = aux;

        // Parseamos la línea usando '-' como delimitador
        char *token = strtok(linea, "-");
        if (token != NULL) {
            lista[*numJugadores].id_jugador = atoi(token); // Convertimos el ID a entero

            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].nomb_jugador, token, MAX_NOMBRE - 1); // Copiamos el nombre

            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].usuario, token, MAX_USER - 1); // Copiamos el usuario

            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].contrasena, token, MAX_PASS - 1); // Copiamos la contraseña

            (*numJugadores)++; // Incrementamos el contador de jugadores
        }
    }

    fclose(f); // Cerramos el archivo
    return lista; // Devolvemos la lista cargada
}

// Función para verificar si las credenciales de usuario y contraseña son correctas
int verificarAcceso(Usuario *lista, int n, char *user, char *pass) {
    // Recorremos la lista de usuarios
    int i;
    for (i = 0; i < n; i++) {
        // Comprobamos si el usuario y contraseña coinciden
        if (strcmp(lista[i].usuario, user) == 0 && strcmp(lista[i].contrasena, pass) == 0) {
            return lista[i].id_jugador; // Devolvemos el ID del jugador si coincide
        }
    }
    return -1; // Indica que las credenciales no existen o son erróneas
}

// Función para registrar un nuevo jugador en el sistema
void registrarJugador(Usuario **lista, int *n) {
    Usuario nuevo; // Estructura para el nuevo usuario
    printf("\n--- REGISTRO DE NUEVO JUGADOR ---\n");

    nuevo.id_jugador = (*n) + 1; // Asignamos un ID único basado en el número actual de jugadores

    printf("Introduce tu nombre completo (max 20 caracteres): ");
    scanf(" %20[^\n]", nuevo.nomb_jugador); // Leemos el nombre completo

    printf("Introduce nombre de usuario (max 10 caracteres): ");
    scanf("%10s", nuevo.usuario); // Leemos el nombre de usuario

    printf("Introduce contraseña (max 8 caracteres): ");
    scanf("%8s", nuevo.contrasena); // Leemos la contraseña

    // Redimensionamos la lista para añadir el nuevo usuario
    Usuario *aux = (Usuario *)realloc(*lista, (*n + 1) * sizeof(Usuario));
    if (aux != NULL) {
        *lista = aux;
        (*lista)[*n] = nuevo; // Añadimos el nuevo usuario a la lista
        (*n)++; // Incrementamos el contador de usuarios
               
        printf("\nRegistro completado. Bienvenido al sistema [5].\n");
        guardarJugadores(*lista, *n); // Guardamos inmediatamente en el archivo para persistencia
    } else {
        printf("Error crítico: Fallo de memoria en el registro [1].\n");
    }
}

// Función para guardar la lista de jugadores en el archivo Jugadores.txt
void guardarJugadores(Usuario *lista, int n) {
    // Abrimos el archivo en modo escritura (sobrescribe el archivo)
    FILE *f = fopen("Jugadores.txt", "w"); 

    if (f == NULL) {
        printf("Error: No se pudo guardar la información en Jugadores.txt [2].\n");
        return;
    }

    // Recorremos la lista y escribimos cada usuario en formato ID-Nombre-Usuario-Contraseña
    for (int i = 0; i < n; i++) {
        // Escribimos los campos separados por guiones
        fprintf(f, "%02d-%s-%s-%s", 
                lista[i].id_jugador, 
                lista[i].nomb_jugador, 
                lista[i].usuario, 
                lista[i].contrasena);
        
        fprintf(f, "\n"); // Nueva línea para cada usuario
    }

    fclose(f); // Cerramos el archivo
}

// Función para liberar la memoria dinámica asignada a la lista de usuarios
void liberarJugadores(Usuario *lista) {
    if (lista != NULL) {
        free(lista); // Liberamos la memoria
    }
}