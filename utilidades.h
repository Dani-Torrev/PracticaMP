#ifndef UTILIDADES_H
#define UTILIDADES_H

// Limpia el rastro del ENTER en el teclado para que no salte los scanf
void limpiar_buffer();

// Quita el '\n' que deja fgets al final de las cadenas
void quitar_salto_linea(char* cadena);

// Pasa una cadena a MAYÚSCULAS para comparar sin errores
void a_mayusculas(char* cadena);

// Muestra mensajes de error con un formato estándar
void mostrar_error(char* mensaje);

#endif