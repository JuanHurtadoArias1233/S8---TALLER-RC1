#include <stdio.h>
#include <string.h>
#include "productos.h"

/* --- Recursos --- */
void ingresarRecursos(char recursos[][MAX_NOMBRE], int disponibles[], int *numRecursos) {
    int k;
    printf("\n¿Cuántos tipos de recursos desea registrar (max %d)? ", MAX_RECURSOS);
    if (scanf("%d", &k) != 1) return;
    if (k < 0) k = 0;
    if (k > MAX_RECURSOS) k = MAX_RECURSOS;
    *numRecursos = k;

    for (int i = 0; i < *numRecursos; i++) {
        printf("Nombre recurso %d: ", i + 1);
        scanf("%49s", recursos[i]);
        printf("Cantidad disponible de %s: ", recursos[i]);
        scanf("%d", &disponibles[i]);
        if (disponibles[i] < 0) disponibles[i] = 0;
    }
}

void editarRecurso(char recursos[][MAX_NOMBRE], int disponibles[], int numRecursos) {
    char nombre[MAX_NOMBRE];
    if (numRecursos <= 0) {
        printf("No hay recursos registrados.\n");
        return;
    }

    printf("\nIngrese el nombre del recurso a editar: ");
    scanf("%49s", nombre);

    for (int i = 0; i < numRecursos; i++) {
        if (strcmp(nombre, recursos[i]) == 0) {
            printf("Nuevo nombre para %s: ", recursos[i]);
            scanf("%49s", recursos[i]);
            printf("Nueva cantidad disponible: ");
            scanf("%d", &disponibles[i]);
            if (disponibles[i] < 0) disponibles[i] = 0;
            printf("Recurso actualizado.\n");
            return;
        }
    }
    printf("Recurso no encontrado.\n");
}

void mostrarRecursos(char recursos[][MAX_NOMBRE], int disponibles[], int numRecursos) {
    if (numRecursos <= 0) {
        printf("No hay recursos registrados.\n");
        return;
    }
    printf("\n--- Recursos ---\n");
    for (int r = 0; r < numRecursos; r++) {
        printf("%d) %s : %d\n", r + 1, recursos[r], disponibles[r]);
    }
}

/* --- Productos --- */
void ingresarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                       int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos) {

    int k;
    printf("\n¿Cuántos productos desea ingresar (max %d)? ", MAX_PRODUCTOS - *numProductos);
    if (scanf("%d", &k) != 1) return;
    if (k < 0) k = 0;
    if (k > (MAX_PRODUCTOS - *numProductos)) k = MAX_PRODUCTOS - *numProductos;

    for (int i = *numProductos; i < *numProductos + k; i++) {
        printf("\n--- Producto %d ---\n", i + 1);
        printf("Nombre: ");
        scanf("%49s", productos[i]);

        printf("Cantidad demandada: ");
        scanf("%d", &cantidades[i]);
        if (cantidades[i] < 0) cantidades[i] = 0;

        printf("Tiempo de fabricacion por unidad (horas, ej: 2.5): ");
        scanf("%f", &tiempos[i]);
        if (tiempos[i] < 0.0f) tiempos[i] = 0.0f;

        if (numRecursos > 0)
            printf("Ingrese recursos requeridos por unidad:\n");
        for (int r = 0; r < numRecursos; r++) {
            printf("  %s por unidad: ", (r>=0? "recurso":"recurso"));
            scanf("%d", &usoRecursos[i][r]);
            if (usoRecursos[i][r] < 0) usoRecursos[i][r] = 0;
        }
        /* Si hay más recursos que se han registrado anteriormente, inicializamos las columnas que no se usan */
        for (int r = numRecursos; r < MAX_RECURSOS; r++) usoRecursos[i][r] = 0;
    }
    *numProductos += k;
}

void mostrarProductos(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], char recursos[][MAX_NOMBRE], int numProductos, int numRecursos) {

    if (numProductos <= 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\n--- Productos ---\n");
    for (int i = 0; i < numProductos; i++) {
        printf("\n%d) %s\n", i + 1, productos[i]);
        printf("   Cantidad demandada: %d\n", cantidades[i]);
        printf("   Tiempo por unidad: %.2f horas\n", tiempos[i]);
        if (numRecursos > 0) {
            printf("   Recursos por unidad:\n");
            for (int r = 0; r < numRecursos; r++) {
                printf("     - %s: %d\n", recursos[r], usoRecursos[i][r]);
            }
        }
    }
}

void editarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                    int usoRecursos[][MAX_RECURSOS], int numProductos, int numRecursos) {

    char nombre[MAX_NOMBRE];
    if (numProductos <= 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    printf("\nIngrese el nombre del producto a editar: ");
    scanf("%49s", nombre);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombre, productos[i]) == 0) {
            printf("Nuevo nombre (actual: %s): ", productos[i]);
            scanf("%49s", productos[i]);

            printf("Nueva cantidad demandada: ");
            scanf("%d", &cantidades[i]);
            if (cantidades[i] < 0) cantidades[i] = 0;

            printf("Nuevo tiempo por unidad: ");
            scanf("%f", &tiempos[i]);
            if (tiempos[i] < 0.0f) tiempos[i] = 0.0f;

            for (int r = 0; r < numRecursos; r++) {
                printf("Nuevo %s por unidad: ", productos[i]);
                scanf("%d", &usoRecursos[i][r]);
                if (usoRecursos[i][r] < 0) usoRecursos[i][r] = 0;
            }
            printf("Producto actualizado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto(char productos[][MAX_NOMBRE], int cantidades[], float tiempos[],
                      int usoRecursos[][MAX_RECURSOS], int *numProductos, int numRecursos) {

    char nombre[MAX_NOMBRE];
    if (*numProductos <= 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    printf("\nIngrese el nombre del producto a eliminar: ");
    scanf("%49s", nombre);

    for (int i = 0; i < *numProductos; i++) {
        if (strcmp(nombre, productos[i]) == 0) {
            /* desplazar todo hacia arriba */
            for (int j = i; j < *numProductos - 1; j++) {
                strcpy(productos[j], productos[j + 1]);
                cantidades[j] = cantidades[j + 1];
                tiempos[j] = tiempos[j + 1];
                for (int r = 0; r < numRecursos; r++)
                    usoRecursos[j][r] = usoRecursos[j + 1][r];
            }
            (*numProductos)--;
            printf("Producto eliminado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

int buscarProducto(char productos[][MAX_NOMBRE], int numProductos, const char *nombre) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i], nombre) == 0) return i;
    }
    return -1;
}

/* --- Cálculos --- */
float calcularTiempoTotal(int cantidades[], float tiempos[], int numProductos) {
    float total = 0.0f;
    for (int i = 0; i < numProductos; i++) {
        total += cantidades[i] * tiempos[i];
    }
    return total;
}

void calcularRecursosTotales(int cantidades[], int usoRecursos[][MAX_RECURSOS],
                             int numProductos, int numRecursos, int resultado[]) {
    for (int r = 0; r < numRecursos; r++) resultado[r] = 0;
    for (int i = 0; i < numProductos; i++) {
        for (int r = 0; r < numRecursos; r++) {
            resultado[r] += cantidades[i] * usoRecursos[i][r];
        }
    }
}

int verificarFactibilidad(float tiempoTotal, float tiempoDisponible,
                          int recursosTotales[], int recursosDisponibles[], int numRecursos) {

    if (tiempoTotal > tiempoDisponible) return 0;

    for (int r = 0; r < numRecursos; r++) {
        if (recursosTotales[r] > recursosDisponibles[r]) return 0;
    }
    return 1;
}