#ifndef JUGABILIDAD_H
#define JUGABILIDAD_H

void iniciarSistema();
void gestionarMenuPrincipal(int id_jugador);
void buclePartida(int id_jugador, char *sala_inicio);
void mostrarAccionesDisponibles(char *nombreSala);
void ejecutarAccionSeleccionada(int opcion, char *id_sala_actual, int *continuarPartida);
int comprobarCondicionVictoria(char *tipoSala);

#endif