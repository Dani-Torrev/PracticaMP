// Includes para entrada/salida, memoria dinámica, strings y header de objetos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Objetos.h"

// Función para cargar la lista de objetos desde el archivo Objetos.txt
Objeto* cargarObjetos(int *numObjetos) {
    FILE *f; // Puntero al archivo
    Objeto *lista = NULL; // Lista de objetos
    char linea[200]; // Buffer para leer líneas
    *numObjetos = 0; // Inicializamos contador

    // Abrimos el archivo en modo lectura
    f = fopen("Objetos.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir Objetos.txt [2]\n");
        return NULL;
    }

    // Leemos línea por línea
    while (fgets(linea, sizeof(linea), f) != NULL) {
        // Redimensionamos la lista para añadir un objeto
        Objeto *aux = (Objeto *)realloc(lista, (*numObjetos + 1) * sizeof(Objeto));
        if (aux == NULL) {
            printf("Error de memoria dinámica [1]\n");
            fclose(f);
            return lista;
        }
        lista = aux;

        // Parseamos la línea usando '-' como delimitador
        char *token = strtok(linea, "-");
        if (token != NULL) {
            // Copiamos el ID del objeto
            strncpy(lista[*numObjetos].id_obj, token, MAX_ID_OBJ - 1);
            
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numObjetos].nomb_obj, token, MAX_NOMB_OBJ - 1); // Nombre
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numObjetos].descrip, token, MAX_DESC_OBJ - 1); // Descripción
            token = strtok(NULL, "-\n"); // Localización
            if (token != NULL) strncpy(lista[*numObjetos].localiz, token, MAX_LOCALIZ - 1);
            (*numObjetos)++; // Incrementamos contador
        }
    }

    fclose(f); // Cerramos el archivo
    return lista; // Devolvemos la lista
}

// Función para listar los objetos presentes en una sala específica
void listarObjetosEnSala(Objeto *lista, int n, char *id_sala) {
    int i;
    int encontrados = 0; // Contador de objetos encontrados

    printf("Objetos presentes en esta sala:\n");
    // Recorremos la lista de objetos
    for (i = 0; i < n; i++) {
        // Comprobamos si la localización coincide con el ID de la sala actual
        if (strcmp(lista[i].localiz, id_sala) == 0) {
            printf("- %s (%s)\n", lista[i].nomb_obj, lista[i].id_obj);
            encontrados++; // Incrementamos contador
        }
    }

    if (encontrados == 0) {
        printf("No hay objetos en esta sala.\n");
    }
}

// Función para listar los objetos en el inventario del jugador
void listarInventario(Objeto *lista, int n) {
    int i;
    int tieneObjetos = 0; // Flag para saber si hay objetos

    printf("\n--- TU INVENTARIO ---\n");
    // Recorremos la lista de objetos
    for (i = 0; i < n; i++) {
        // Según las reglas, un objeto está en el inventario si su localización es "Inventario"
        if (strcmp(lista[i].localiz, "Inventario") == 0) {
            printf("[%s] %s: %s\n", lista[i].id_obj, lista[i].nomb_obj, lista[i].descrip);
            tieneObjetos = 1; // Marcamos que hay objetos
        }
    }

    if (!tieneObjetos) {
        printf("Tu inventario está vacío.\n");
    }
}

// Función para coger un objeto de la sala y añadirlo al inventario
int cogerObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual) {
    // Buscamos el objeto por ID
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id_obj, id_obj) == 0) {
            // Si está en la sala actual, lo movemos al inventario
            if (strcmp(lista[i].localiz, id_sala_actual) == 0) {
                strcpy(lista[i].localiz, "Inventario");
                printf("\n[+] ¡Has metido '%s' en tu mochila!\n", lista[i].nomb_obj);
                return 1; // Éxito
            } else if (strcmp(lista[i].localiz, "Inventario") == 0) {
                printf("\n[X] Ya tienes ese objeto en tu inventario.\n");
                return 0; // Ya lo tiene
            } else {
                printf("\n[X] Ese objeto no esta en esta sala.\n");
                return 0; // No está en la sala
            }
        }
    }
    printf("\n[X] No existe ningun objeto con ese ID.\n");
    return 0; // No existe
}

// Función para soltar un objeto del inventario a la sala actual
int soltarObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual) {
    // Buscamos el objeto en el inventario
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id_obj, id_obj) == 0 && strcmp(lista[i].localiz, "Inventario") == 0) {
            // Movemos el objeto a la sala actual
            strcpy(lista[i].localiz, id_sala_actual);
            return 1; // Éxito
        }
    }
    return 0; // No encontrado o no en inventario
}

// Función para verificar si el jugador tiene un objeto necesario en el inventario
int verificarUsoObjeto(Objeto *lista, int n, char *id_obj_necesario) {
    // Buscamos el objeto en el inventario
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id_obj, id_obj_necesario) == 0 && strcmp(lista[i].localiz, "Inventario") == 0) {
            return 1; // Lo tiene en el inventario
        }
    }
    return 0; // No lo tiene
}

// Función para liberar la memoria de la lista de objetos
void liberarObjetos(Objeto *lista) {
    if (lista != NULL) {
        free(lista); // Liberamos la memoria
    }
}

// Función para guardar la lista de objetos en el archivo Objetos.txt
void guardarObjetos(Objeto *lista, int n) {
    // Abrimos el archivo en modo escritura
    FILE *f = fopen("Objetos.txt", "w");
    if (f != NULL) {
        // Escribimos cada objeto en formato ID-Nombre-Descripción-Localización
        for (int i = 0; i < n; i++) {
            fprintf(f, "%s-%s-%s-%s\n", lista[i].id_obj, lista[i].nomb_obj, lista[i].descrip, lista[i].localiz);
        }
        fclose(f); // Cerramos el archivo
    }
}