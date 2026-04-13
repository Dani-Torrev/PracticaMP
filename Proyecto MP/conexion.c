#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include "conexion.h"
#include "utilidades.h"

Conexion* cargar_conexiones(int *num_conexiones) {
    FILE *f = fopen("conexiones.txt", "r");
    if (f == NULL) {
        mostrar_error("No se pudo abrir el archivo conexiones.txt");
        *num_conexiones = 0;
        return NULL;
    }

    Conexion *lista = NULL;
    *num_conexiones = 0;
    char linea[50];

    while (fgets(linea, sizeof(linea), f) != NULL) {
        quitar_salto_linea(linea);
        
        // Saltamos las líneas en blanco por si hay saltos de línea extra
        if (strlen(linea) == 0) continue; 

        // Ampliamos memoria
        Conexion *aux = (Conexion*)realloc(lista, (*num_conexiones + 1) * sizeof(Conexion));
        if (aux == NULL) {
            mostrar_error("Fallo de memoria al cargar conexiones.");
            fclose(f);
            return lista;
        }
        lista = aux;

        // La primera línea es el ID de la conexión (C01, C02...)
        strncpy(lista[*num_conexiones].id_conexion, linea, sizeof(lista[*num_conexiones].id_conexion) - 1);

        // Siguiente: ID Origen
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_conexiones].id_origen, linea, sizeof(lista[*num_conexiones].id_origen) - 1);
        }
        // Siguiente: ID Destino
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_conexiones].id_destino, linea, sizeof(lista[*num_conexiones].id_destino) - 1);
        }
        // Siguiente: Estado (Activa, Bloqueada...)
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_conexiones].estado, linea, sizeof(lista[*num_conexiones].estado) - 1);
        }
        // Siguiente: Condición (0, OBJ01, P01...)
        if (fgets(linea, sizeof(linea), f)) {
            quitar_salto_linea(linea);
            strncpy(lista[*num_conexiones].condicion, linea, sizeof(lista[*num_conexiones].condicion) - 1);
        }

        (*num_conexiones)++;
    }
    
    fclose(f);
    return lista;
}