#include <stdio.h>
#include <string.h>
#include "productos.h"

/* ================= RECURSOS ================= */

void ingresarRecursos(char recursos[][MAX_NOMBRE], int recursosDisponibles[], int *numRecursos) {
    printf("\n¿Cuántos recursos desea ingresar?: ");
    if (scanf("%d", numRecursos) != 1) {
        *numRecursos = 0;
        return;
    }

    if (*numRecursos > MAX_RECURSOS) *numRecursos = MAX_RECURSOS;
    for (int i = 0; i < *numRecursos; i++) {
        printf("Nombre del recurso %d: ", i + 1);
        scanf("%s", recursos[i]);
        printf("Cantidad disponible: ");
        scanf("%d", &recursosDisponibles[i]);
    }
}

void mostrarRecursos(char recursos[][MAX_NOMBRE], int recursosDisponibles[], int numRecursos) {
    printf("\n--- LISTA DE RECURSOS ---\n");
    for (int i = 0; i < numRecursos; i++) {
        printf("%d. %s - %d unidades\n", i + 1, recursos[i], recursosDisponibles[i]);
    }
}

void editarRecurso(char recursos[][MAX_NOMBRE], int recursosDisponibles[], int numRecursos) {
    if (numRecursos <= 0) {
        printf("No hay recursos para editar.\n");
        return;
    }

    mostrarRecursos(recursos, recursosDisponibles, numRecursos);
    int id;
    printf("\nIngrese número de recurso a editar: ");
    if (scanf("%d", &id) != 1) return;
    id--;

    if (id < 0 || id >= numRecursos) {
        printf("ID inválido.\n");
        return;
    }

    printf("Nuevo nombre: ");
    scanf("%s", recursos[id]);
    printf("Nueva cantidad: ");
    scanf("%d", &recursosDisponibles[id]);
}

/* ================= PRODUCTOS ================= */

void ingresarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                       int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos) {
    printf("\n¿Cuántos productos desea ingresar?: ");
    if (scanf("%d", numProductos) != 1) {
        *numProductos = 0;
        return;
    }

    if (*numProductos > MAX_PRODUCTOS) *numProductos = MAX_PRODUCTOS;
    for (int i = 0; i < *numProductos; i++) {
        printf("\nNombre del producto %d: ", i + 1);
        scanf("%s", productos[i]);

        printf("Cantidad a producir: ");
        scanf("%d", &cantidades[i]);

        printf("Tiempo por unidad: ");
        scanf("%f", &tiempos[i]);

        if (numRecursos > 0) {
            printf("Uso de recursos para '%s':\n", productos[i]);
            for (int r = 0; r < numRecursos; r++) {
                printf("  Recurso %d: ", r + 1);
                scanf("%d", &usoRecursos[i][r]);
            }
        } else {
            for (int r = 0; r < MAX_RECURSOS; r++) usoRecursos[i][r] = 0;
        }
    }
}

void mostrarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], int numProductos, int numRecursos) {
    printf("\n--- LISTA DE PRODUCTOS ---\n");
    if (numProductos <= 0) {
        printf("No hay productos.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++) {
        printf("\nProducto %d: %s\n", i + 1, productos[i]);
        printf("Cantidad: %d\n", cantidades[i]);
        printf("Tiempo por unidad: %.2f\n", tiempos[i]);

        if (numRecursos > 0) {
            printf("Uso de recursos:\n");
            for (int r = 0; r < numRecursos; r++) {
                printf("  Recurso %d: %d\n", r + 1, usoRecursos[i][r]);
            }
        }
    }
}

void editarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                    int usoRecursos[][MAX_RECURSOS], int numProductos, int numRecursos) {
    if (numProductos <= 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    mostrarProductos(productos, cantidades, tiempos, usoRecursos, numProductos, numRecursos);
    int id;
    printf("\nIngrese número de producto a editar: ");
    if (scanf("%d", &id) != 1) return;
    id--;

    if (id < 0 || id >= numProductos) {
        printf("ID inválido.\n");
        return;
    }

    printf("Nuevo nombre: ");
    scanf("%s", productos[id]);

    printf("Nueva cantidad: ");
    scanf("%d", &cantidades[id]);

    printf("Nuevo tiempo por unidad: ");
    scanf("%f", &tiempos[id]);

    for (int r = 0; r < numRecursos; r++) {
        printf("Nuevo uso del recurso %d: ", r + 1);
        scanf("%d", &usoRecursos[id][r]);
    }
}

void eliminarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos) {
    if (*numProductos <= 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    mostrarProductos(productos, cantidades, tiempos, usoRecursos, *numProductos, numRecursos);
    int id;
    printf("\nIngrese número de producto a eliminar: ");
    if (scanf("%d", &id) != 1) return;
    id--;

    if (id < 0 || id >= *numProductos) {
        printf("ID inválido.\n");
        return;
    }

    for (int i = id; i < *numProductos - 1; i++) {
        strcpy(productos[i], productos[i+1]);
        cantidades[i] = cantidades[i+1];
        tiempos[i] = tiempos[i+1];
        for (int r = 0; r < numRecursos; r++)
            usoRecursos[i][r] = usoRecursos[i+1][r];
    }
    (*numProductos)--;
}

/* ================= UTILIDADES ================= */

float calcularTiempoTotal(int cantidades[], float tiempos[], int numProductos) {
    float total = 0.0f;
    for (int i = 0; i < numProductos; i++)
        total += cantidades[i] * tiempos[i];
    return total;
}

void calcularRecursosTotales(int cantidades[], int usoRecursos[][MAX_RECURSOS],
                             int numProductos, int numRecursos, int recursosTotales[]) {
    for (int r = 0; r < numRecursos; r++) {
        recursosTotales[r] = 0;
        for (int p = 0; p < numProductos; p++) {
            recursosTotales[r] += cantidades[p] * usoRecursos[p][r];
        }
    }
}

/*
 verificarFactibilidad:
 - retorna 1 si es factible (tiempo suficiente Y recursos suficientes)
 - retorna 0 si NO es factible
*/
int verificarFactibilidad(float tiempoTotal, float tiempoDisponible,
                          int recursosTotales[], int recursosDisponibles[],
                          int numRecursos) {

    if (tiempoTotal > tiempoDisponible)
        return 0;

    for (int r = 0; r < numRecursos; r++) {
        if (recursosTotales[r] > recursosDisponibles[r])
            return 0;
    }

    return 1;
}
