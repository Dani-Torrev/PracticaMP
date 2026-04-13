#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Objetos.h" 
#include "utilidades.h"

Objeto* cargarObjetos(int *numObjetos) {
    FILE *f;
    Objeto *lista = NULL;
    char linea[256];
    *numObjetos = 0;
    f = fopen("Objetos.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir Objetos.txt [2]\n");
        return NULL;
    }
    while (fgets(linea, sizeof(linea), f) != NULL) {
        Objeto *aux = (Objeto *)realloc(lista, (*numObjetos + 1) * sizeof(Objeto));
        if (aux == NULL) {
            printf("Error de memoria dinámica [1]\n");
            fclose(f);
            return lista;
        }
        lista = aux;
        char *token = strtok(linea, "-");
        if (token != NULL) {
            strncpy(lista[*numObjetos].id_obj, token, MAX_ID_OBJ - 1);
            
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numObjetos].nomb_obj, token, MAX_NOMB_OBJ - 1);
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numObjetos].descrip, token, MAX_DESC_OBJ - 1);
            token = strtok(NULL, "-\n"); 
            if (token != NULL) strncpy(lista[*numObjetos].localiz, token, MAX_LOCALIZ - 1);
            (*numObjetos)++;
        }
    }
    fclose(f);
    return lista;
}

void listarObjetosEnSala(Objeto *lista, int n, char *id_sala) {
    int i;
    int encontrados = 0;

    printf("Objetos presentes en esta sala:\n");
    for (i = 0; i < n; i++) {
        if (strcmp(lista[i].localiz, id_sala) == 0) {
            printf("- %s (%s)\n", lista[i].nomb_obj, lista[i].id_obj);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No hay objetos en esta sala.\n");
    }
}

void listarInventario(Objeto *lista, int n) {
    int i;
    int tieneObjetos = 0;

    printf("\n--- TU INVENTARIO ---\n");
    for (i = 0; i < n; i++) {
        if (strcmp(lista[i].localiz, "Inventario") == 0) {
            printf("[%s] %s: %s\n", lista[i].id_obj, lista[i].nomb_obj, lista[i].descrip);
            tieneObjetos = 1;
        }
    }

    if (!tieneObjetos) {
        printf("Tu inventario está vacío.\n");
    }
}

int cogerObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual) {
    for (int i = 0; i < n; i++) {
        // Validamos que el objeto existe y está en la sala actual [7]
        if (strcmp(lista[i].id_obj, id_obj) == 0 && strcmp(lista[i].localiz, id_sala_actual) == 0) {
            strcpy(lista[i].localiz, "Inventario"); // Mantenemos coherencia de estado [2]
            printf("Has recogido: %s\n", lista[i].nomb_obj);
            return 1;
        }
    }
    printf("Ese objeto no está aquí o no existe [7].\n");
    return 0;
}

int soltarObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id_obj, id_obj) == 0 && strcmp(lista[i].localiz, "Inventario") == 0) {
            strcpy(lista[i].localiz, id_sala_actual); // Pasa a la sala actual [2, 6]
            printf("Has soltado: %s\n", lista[i].nomb_obj);
            return 1;
        }
    }
    printf("No tienes ese objeto en tu inventario [6].\n");
    return 0;
}

int verificarUsoObjeto(Objeto *lista, int n, char *id_obj_necesario) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id_obj, id_obj_necesario) == 0 && strcmp(lista[i].localiz, "Inventario") == 0) {
            return 1; // El objeto está disponible para su uso [9]
        }
    }
    return 0;
}

void guardarObjetos(Objeto *lista, int n) {
    FILE *f = fopen("Objetos.txt", "w");
    if (f == NULL) return;

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s-%s-%s-%s\n", 
                lista[i].id_obj, lista[i].nomb_obj, 
                lista[i].descrip, lista[i].localiz);
    }
    fclose(f);
}

void liberarObjetos(Objeto *lista) {
    if (lista != NULL) {
        free(lista);
    }
}