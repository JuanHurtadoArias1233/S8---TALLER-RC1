#include <stdio.h>
#include "productos.h"

int main(void) {

    /* Datos de recursos */
    char recursos[MAX_RECURSOS][MAX_NOMBRE];
    int recursosDisponibles[MAX_RECURSOS];
    int numRecursos = 0;

    /* Datos de productos */
    char productos[MAX_PRODUCTOS][MAX_NOMBRE];
    int cantidades[MAX_PRODUCTOS];
    float tiempos[MAX_PRODUCTOS];
    int usoRecursos[MAX_PRODUCTOS][MAX_RECURSOS];
    int numProductos = 0;

    /* Inicializar arrays */
    for (int i = 0; i < MAX_RECURSOS; i++)
        recursosDisponibles[i] = 0;

    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        cantidades[i] = 0;
        tiempos[i] = 0.0f;
        for (int r = 0; r < MAX_RECURSOS; r++)
            usoRecursos[i][r] = 0;
    }

    int opcion;
    printf("=== Sistema de Produccion - Fabrica ===\n");

    /* Registrar recursos inicialmente */
    ingresarRecursos(recursos, recursosDisponibles, &numRecursos);

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Mostrar recursos\n");
        printf("2. Editar recurso\n");
        printf("3. Ingresar productos\n");
        printf("4. Mostrar productos\n");
        printf("5. Editar producto\n");
        printf("6. Eliminar producto\n");
        printf("7. Calcular tiempos y recursos totales\n");
        printf("8. Verificar factibilidad\n");
        printf("9. Volver a ingresar recursos\n");
        printf("0. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1) break;

        if (opcion == 1) {

            mostrarRecursos(recursos, recursosDisponibles, numRecursos);

        } else if (opcion == 2) {

            editarRecurso(recursos, recursosDisponibles, numRecursos);

        } else if (opcion == 3) {

            ingresarProductos(productos, cantidades, tiempos, usoRecursos, &numProductos, numRecursos);

        } else if (opcion == 4) {
            /* LLAMADA CORREGIDA */
            mostrarProductos(productos, cantidades, tiempos, usoRecursos, numProductos, numRecursos);

        } else if (opcion == 5) {

            editarProducto(productos, cantidades, tiempos, usoRecursos, numProductos, numRecursos);

        } else if (opcion == 6) {

            eliminarProducto(productos, cantidades, tiempos, usoRecursos, &numProductos, numRecursos);

        } else if (opcion == 7) {

            float tiempoTotal = calcularTiempoTotal(cantidades, tiempos, numProductos);
            int recursosTotales[MAX_RECURSOS];

            calcularRecursosTotales(cantidades, usoRecursos, numProductos, numRecursos, recursosTotales);

            printf("\nTiempo total requerido: %.2f horas\n", tiempoTotal);
            printf("Recursos totales requeridos:\n");

            for (int r = 0; r < numRecursos; r++)
                printf("  - %s: %d\n", recursos[r], recursosTotales[r]);

        } else if (opcion == 8) {

            float tiempoDisponible;
            printf("Ingrese tiempo disponible total (horas): ");
            if (scanf("%f", &tiempoDisponible) != 1) tiempoDisponible = 0.0f;

            int recursosTotales[MAX_RECURSOS];
            calcularRecursosTotales(cantidades, usoRecursos, numProductos, numRecursos, recursosTotales);

            int posible = verificarFactibilidad(
                calcularTiempoTotal(cantidades, tiempos, numProductos),
                tiempoDisponible,
                recursosTotales,
                recursosDisponibles,
                numRecursos
            );

            if (posible) {
                printf("\n✔ La producción es FACTIBLE.\n");
            } else {
                printf("\n✘ La producción NO es factible. Detalles:\n");

                float tiempoTotal = calcularTiempoTotal(cantidades, tiempos, numProductos);
                if (tiempoTotal > tiempoDisponible)
                    printf("  - Tiempo insuficiente: requerido %.2f, disponible %.2f\n",
                           tiempoTotal, tiempoDisponible);

                for (int r = 0; r < numRecursos; r++) {
                    if (recursosTotales[r] > recursosDisponibles[r])
                        printf("  - Recurso insuficiente: %s (necesita %d, disponible %d)\n",
                               recursos[r], recursosTotales[r], recursosDisponibles[r]);
                }
            }

        } else if (opcion == 9) {

            ingresarRecursos(recursos, recursosDisponibles, &numRecursos);

        } else if (opcion == 0) {

            printf("Saliendo...\n");

        } else {

            printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
