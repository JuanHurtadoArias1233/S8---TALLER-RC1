#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define MAX_PRODUCTOS 50
#define MAX_RECURSOS 20
#define MAX_NOMBRE 50

/* Prototipos de funciones */
void ingresarRecursos(char recursos[][MAX_NOMBRE], int disponibles[], int *numRecursos);
void editarRecurso(char recursos[][MAX_NOMBRE], int disponibles[], int numRecursos);
void mostrarRecursos(char recursos[][MAX_NOMBRE], int disponibles[], int numRecursos);

void ingresarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                       int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos);

void mostrarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], char recursos[][MAX_NOMBRE], int numProductos, int numRecursos);

void editarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                    int usoRecursos[][MAX_RECURSOS], int numProductos, int numRecursos);

void eliminarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos);

int buscarProducto(char productos[][MAX_NOMBRE], int numProductos, const char *nombre);

/* Cálculos */
float calcularTiempoTotal(int cantidades[], float tiempos[], int numProductos);
void calcularRecursosTotales(int cantidades[], int usoRecursos[][MAX_RECURSOS],
                             int numProductos, int numRecursos, int resultado[]);
int verificarFactibilidad(float tiempoTotal, float tiempoDisponible,
                          int recursosTotales[], int recursosDisponibles[], int numRecursos);

#endif