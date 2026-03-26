#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autentificacion.h"

Jugador* cargarJugadores(int *numJugadores) {
    FILE *f;
    char linea[256];
    Jugador *lista = NULL;
    *numJugadores = 0;

    f = fopen("Jugadores.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir Jugadores.txt [2].\n");
        return NULL;
    }

    while (fgets(linea, sizeof(linea), f) != NULL) {
        linea[strcspn(linea, "\n")] = 0;

        Jugador *aux = (Jugador *)realloc(lista, (*numJugadores + 1) * sizeof(Jugador));
        if (aux == NULL) {
            printf("Error de memoria dinámica al cargar jugadores [1].\n");
            fclose(f);
            return lista; 
        }
        lista = aux;

        char *token = strtok(linea, "-");
        if (token != NULL) {
            lista[*numJugadores].id_jugador = atoi(token); // ID de 2 dígitos

            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].nomb_jugador, token, MAX_NOMBRE - 1);

            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].usuario, token, MAX_USER - 1);

            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numJugadores].contrasena, token, MAX_PASS - 1);

            (*numJugadores)++;
        }
    }

    fclose(f);
    return lista;
}

int verificarAcceso(Jugador *lista, int n, char *user, char *pass) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(lista[i].usuario, user) == 0 && strcmp(lista[i].contrasena, pass) == 0) {
            return lista[i].id_jugador;
        }
    }
    return -1; // Indica que las credenciales no existen o son erróneas
}

void registrarJugador(Jugador **lista, int *n) {
    Jugador nuevo;
    printf("\n--- REGISTRO DE NUEVO JUGADOR ---\n");

    nuevo.id_jugador = (*n) + 1; // Asignación de ID único simple

    printf("Introduce tu nombre completo (max 20 caracteres): ");
    scanf(" %20[^\n]", nuevo.nomb_jugador); 

    printf("Introduce nombre de usuario (max 10 caracteres): ");
    scanf("%10s", nuevo.usuario);

    printf("Introduce contraseña (max 8 caracteres): ");
    scanf("%8s", nuevo.contrasena);

    Jugador *aux = (Jugador *)realloc(*lista, (*n + 1) * sizeof(Jugador));
    if (aux != NULL) {
        *lista = aux;
        (*lista)[*n] = nuevo; 
        (*n)++;               
        
        printf("\nRegistro completado. Bienvenido al sistema [5].\n");
        guardarJugadores(*lista, *n); // Persistencia inmediata
    } else {
        printf("Error crítico: Fallo de memoria en el registro [1].\n");
    }
}

void guardarJugadores(Jugador *lista, int n) {
    FILE *f = fopen("Jugadores.txt", "w"); 

    if (f == NULL) {
        printf("Error: No se pudo guardar la información en Jugadores.txt [2].\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        // Escribimos los campos básicos separados por guiones
        fprintf(f, "%02d-%s-%s-%s", 
                lista[i].id_jugador, 
                lista[i].nomb_jugador, 
                lista[i].usuario, 
                lista[i].contrasena);
        
        fprintf(f, "\n");
    }

    fclose(f);
}

void liberarJugadores(Jugador *lista) {
    if (lista != NULL) {
        free(lista);
    }
}