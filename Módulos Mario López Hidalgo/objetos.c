#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objetos.h" 

// Carga todos los objetos desde el archivo Objetos.txt
Objeto* cargarObjetos(int *numObjetos) {
    FILE *f;
    Objeto *lista = NULL;
    char linea[200];
    *numObjetos = 0;

    // Abre el archivo de objetos
    f = fopen("Objetos.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir Objetos.txt\n");
        return NULL;
    }

    // Lee la primera línea (encabezado o cantidad)
    if (fgets(linea, sizeof(linea), f) == NULL) {
        fclose(f);
        return NULL;
    }

    // Procesa cada línea del archivo
    while (fgets(linea, sizeof(linea), f) != NULL) {
        // Elimina caracteres de salto de línea
        linea[strcspn(linea, "\r\n")] = 0;
        // Salta líneas vacías
        if (strlen(linea) < 3) continue;

        // Expande el array de objetos
        Objeto *aux = (Objeto *)realloc(lista, (*numObjetos + 1) * sizeof(Objeto));
        if (aux == NULL) {
            fclose(f);
            return lista;
        }
        lista = aux;

        // Parsea la línea usando guiones como separador
        char *token = strtok(linea, "-");
        if (token != NULL) {
            // Extrae ID del objeto
            strncpy(lista[*numObjetos].id_obj, token, MAX_ID_OBJ - 1); 
            // Extrae nombre del objeto
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numObjetos].nomb_obj, token, MAX_NOMB_OBJ - 1);
            // Extrae descripción
            token = strtok(NULL, "-");
            if (token != NULL) strncpy(lista[*numObjetos].descrip, token, MAX_DESC_OBJ - 1);
            // Extrae localización
            token = strtok(NULL, "-"); 
            if (token != NULL) strncpy(lista[*numObjetos].localiz, token, MAX_LOCALIZ - 1);
            
            (*numObjetos)++;
        }
    }
    fclose(f);
    return lista;
}

// Lista todos los objetos disponibles en una sala específica
void listarObjetosEnSala(Objeto *lista, int n, char *id_sala) {
    int i, encontrados = 0;
    
    // Convierte el ID de sala a número para comparación
    int sala_actual = atoi(id_sala);

    printf("Objetos presentes en esta sala:\n");
    for (i = 0; i < n; i++) {
        // Comprueba si el objeto está en esta sala
        // Si localiz es "Oculto", atoi devuelve 0
        if (atoi(lista[i].localiz) == sala_actual && sala_actual != 0) {
            printf("- %s (%s)\n", lista[i].nomb_obj, lista[i].id_obj);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No hay objetos a la vista.\n");
    }
}

// Lista todos los objetos del inventario del jugador
void listarInventario(Objeto *lista, int n) {
    int i, tieneObjetos = 0;
    printf("\n--- TU INVENTARIO ---\n");
    // Recorre todos los objetos
    for (i = 0; i < n; i++) {
        char loc_limpia[20];
        strcpy(loc_limpia, lista[i].localiz);
        // Limpia espacios y saltos de línea
        loc_limpia[strcspn(loc_limpia, " \r\n")] = 0;

        // Comprueba si está en el inventario
        if (strcmp(loc_limpia, "Inventario") == 0) {
            printf("[%s] %s: %s\n", lista[i].id_obj, lista[i].nomb_obj, lista[i].descrip);
            tieneObjetos = 1;
        }
    }
    if (!tieneObjetos) {
        printf("Tu inventario esta vacio.\n");
    }
}

// Permite coger un objeto de la sala actual
int cogerObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual) {
    int sala_actual = atoi(id_sala_actual);
    
    for (int i = 0; i < n; i++) {
        // Limpia los IDs de caracteres especiales
        char id_ingresado[20], id_lista[20];
        strcpy(id_ingresado, id_obj);
        id_ingresado[strcspn(id_ingresado, " \r\n")] = 0;
        
        strcpy(id_lista, lista[i].id_obj);
        id_lista[strcspn(id_lista, " \r\n")] = 0;

        // Comprueba si encontró el objeto
        if (strcmp(id_lista, id_ingresado) == 0) {
            // Verifica que esté en la sala actual
            if (atoi(lista[i].localiz) == sala_actual && sala_actual != 0) {
                // Mueve el objeto al inventario
                strcpy(lista[i].localiz, "Inventario");
                printf("\n[+] ¡Has cogido '%s'!\n", lista[i].nomb_obj);
                return 1;
            } else if (strcmp(lista[i].localiz, "Inventario") == 0) {
                printf("\n[X] Ya lo tienes.\n");
                return 0;
            }
        }
    }
    printf("\n[X] No puedes coger eso.\n");
    return 0;
}

// Permite soltar un objeto en la sala actual
int soltarObjeto(Objeto *lista, int n, char *id_obj, char *id_sala_actual) {
    for (int i = 0; i < n; i++) {
        // Comprueba si el objeto existe y está en el inventario
        if (strcmp(lista[i].id_obj, id_obj) == 0 && strcmp(lista[i].localiz, "Inventario") == 0) {
            // Mueve el objeto a la sala actual
            strcpy(lista[i].localiz, id_sala_actual);
            return 1;
        }
    }
    return 0;
}

// Verifica si un objeto es necesario para algo (uso válido)
int verificarUsoObjeto(Objeto *lista, int n, char *id_obj_necesario) {
    char condicion_limpia[50];
    strcpy(condicion_limpia, id_obj_necesario);
    // Limpia espacios y saltos
    condicion_limpia[strcspn(condicion_limpia, " \r\n")] = 0;

    for (int i = 0; i < n; i++) {
        char id_limpio[50], local_limpia[50];
        
        // Limpia el ID del objeto
        strcpy(id_limpio, lista[i].id_obj);
        id_limpio[strcspn(id_limpio, " \r\n")] = 0;
        
        // Limpia la localización
        strcpy(local_limpia, lista[i].localiz);
        local_limpia[strcspn(local_limpia, " \r\n")] = 0;

        // Comprueba si es el objeto necesario y está en el inventario
        if (strcmp(id_limpio, condicion_limpia) == 0 && strcmp(local_limpia, "Inventario") == 0) {
            return 1; // Objeto disponible
        }
    }
    return 0; // Objeto no disponible
}

// Libera la memoria dinámica asignada a la lista de objetos
void liberarObjetos(Objeto *lista) {
    if (lista != NULL) free(lista);
}

// Guarda la lista de objetos en el archivo Objetos.txt
void guardarObjetos(Objeto *lista, int n) {
    // Abre el archivo en modo escritura
    FILE *f = fopen("Objetos.txt", "w");
    if (f != NULL) {
        // Escribe el número total de objetos
        fprintf(f, "%d\n", n); 
        // Escribe cada objeto en formato ID-NOMBRE-DESCRIPCION-LOCALIZACION
        for (int i = 0; i < n; i++) {
            fprintf(f, "%s-%s-%s-%s\n", lista[i].id_obj, lista[i].nomb_obj, lista[i].descrip, lista[i].localiz);
        }
        fclose(f);
    }
}