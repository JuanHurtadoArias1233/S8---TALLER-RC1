#include <stdio.h>
#include "productos.h"

int main() {
    int opcion;

    ingresarRecursos();

    do {
        menu();

        while (scanf("%d", &opcion) != 1 || opcion < 0 || opcion > 5) {
            printf("Opcion invalida. Intente otra vez: ");
            limpiarBuffer();
        }
        limpiarBuffer();

        switch (opcion) {

            case 1:
                ingresarProductos();
                break;

            case 2:
                mostrarProductos();
                break;

            case 3:
                editarProducto();
                break;

            case 4:
                eliminarProducto();
                break;

            case 5:
                solicitudCliente();
                break;

            case 0:
                printf("Saliendo...\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}
