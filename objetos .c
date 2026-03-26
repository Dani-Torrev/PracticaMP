#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Objetos.h" 

Objeto* cargarObjetos(int *numObjetos) {
    FILE *f;
    Objeto *lista = NULL;
    char linea;
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
        // Comprobamos si la localización coincide con el ID de la sala actual [4, 5]
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
        // Según las reglas, un objeto está en el inventario si su localización es "Inventario" [4, 6]
        if (strcmp(lista[i].localiz, "Inventario") == 0) {
            printf("[%s] %s: %s\n", lista[i].id_obj, lista[i].nomb_obj, lista[i].descrip);
            tieneObjetos = 1;
        }
    }

    if (!tieneObjetos) {
        printf("Tu inventario está vacío.\n");
    }
}
