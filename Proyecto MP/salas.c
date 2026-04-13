#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include "salas.h"
#include "utilidades.h"


Sala* cargar_salas(int *num_salas) {
    FILE *f = fopen("salas.txt", "r");
    if (f == NULL) {
        mostrar_error("No se pudo abrir el archivo salas.txt");
        *num_salas = 0;
        return NULL;
    }

    Sala *lista = NULL;
    *num_salas = 0;
    char linea[200];

    // Leemos línea a línea hasta que termine el fichero
    while (fgets(linea, sizeof(linea), f) != NULL) {
        quitar_salto_linea(linea); // Usamos tu función de utilidades
        
        // El archivo salas.txt termina con la palabra FIN
        if (strcmp(linea, "FIN") == 0) break; 

        // Ampliamos la memoria para la nueva sala
        Sala *aux = (Sala*)realloc(lista, (*num_salas + 1) * sizeof(Sala));
        if (aux == NULL) {
            mostrar_error("Fallo de memoria al cargar salas.");
            fclose(f);
            return lista;
        }
        lista = aux;

        // La primera línea es el ID
        strncpy(lista[*num_salas].id_sala, linea, sizeof(lista[*num_salas].id_sala) - 1);
        
        // Siguiente línea: Nombre
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_salas].nombre, linea, sizeof(lista[*num_salas].nombre) - 1);
        }
        // Siguiente línea: Tipo (NORMAL, INICIAL, SALIDA)
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_salas].tipo, linea, sizeof(lista[*num_salas].tipo) - 1);
        }
        // Siguiente línea: Descripción
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_salas].descripcion, linea, sizeof(lista[*num_salas].descripcion) - 1);
        }

        (*num_salas)++;
    }
    
    fclose(f);
    return lista;
}