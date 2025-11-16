#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define MAX_RECURSOS 10
#define MAX_PRODUCTOS 10
#define MAX_NOMBRE 50

/* PROTOTIPOS */

// Recursos
void ingresarRecursos(char recursos[][MAX_NOMBRE], int recursosDisponibles[], int *numRecursos);
void mostrarRecursos(char recursos[][MAX_NOMBRE], int recursosDisponibles[], int numRecursos);
void editarRecurso(char recursos[][MAX_NOMBRE], int recursosDisponibles[], int numRecursos);

// Productos
void ingresarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                       int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos);

void mostrarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], int numProductos, int numRecursos);

void editarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                    int usoRecursos[][MAX_RECURSOS], int numProductos, int numRecursos);

void eliminarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos);

// Utilidades
float calcularTiempoTotal(int cantidades[], float tiempos[], int numProductos);
void calcularRecursosTotales(int cantidades[], int usoRecursos[][MAX_RECURSOS],
                             int numProductos, int numRecursos, int recursosTotales[]);

/*
 Verificar factibilidad ahora acepta:
  - tiempoTotal requerido (float)
  - tiempoDisponible (float)
  - recursosTotales[] calculados (int[])
  - recursosDisponibles[] (int[])
  - numRecursos (int)
*/
int verificarFactibilidad(float tiempoTotal, float tiempoDisponible,
                          int recursosTotales[], int recursosDisponibles[],
                          int numRecursos);

#endif
