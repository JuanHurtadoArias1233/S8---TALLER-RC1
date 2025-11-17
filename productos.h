#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define MAX_PRODUCTOS 50
#define MAX_RECURSOS 20
#define MAX_NOMBRE 50


extern char nombresRecursos[MAX_RECURSOS][MAX_NOMBRE];
extern int cantidadTotalRecursos[MAX_RECURSOS];
extern int numRecursos;

extern char nombresProductos[MAX_PRODUCTOS][MAX_NOMBRE];
extern float tiempoFabricacion[MAX_PRODUCTOS];
extern int recursosNecesarios[MAX_PRODUCTOS][MAX_RECURSOS];
extern int numProductos;

extern float tiempoFabrica;


void limpiarBuffer();
int leerEnteroNoNegativo();
float leerFlotanteNoNegativo();
void leerCadena(char *texto, int max);

void menu();

void ingresarRecursos();

void ingresarProductos();
void mostrarProductos();
void editarProducto();
void eliminarProducto();

void solicitudCliente();

#endif
