#include <stdio.h>
#include <string.h>
#include "productos.h"



char nombresRecursos[MAX_RECURSOS][MAX_NOMBRE];
int cantidadTotalRecursos[MAX_RECURSOS];
int numRecursos = 0;

char nombresProductos[MAX_PRODUCTOS][MAX_NOMBRE];
float tiempoFabricacion[MAX_PRODUCTOS];
int recursosNecesarios[MAX_PRODUCTOS][MAX_RECURSOS];
int numProductos = 0;

float tiempoFabrica = 0;



void limpiarBuffer() {
    while (getchar() != '\n');
}

int leerEnteroNoNegativo() {
    int x;
    while (scanf("%d", &x) != 1 || x < 0) {
        printf("Valor invalido. Intente otra vez: ");
        limpiarBuffer();
    }
    limpiarBuffer();
    return x;
}

float leerFlotanteNoNegativo() {
    float x;
    while (scanf("%f", &x) != 1 || x < 0) {
        printf("Valor invalido. Intente otra vez: ");
        limpiarBuffer();
    }
    limpiarBuffer();
    return x;
}

void leerCadena(char *texto, int max) {
    fgets(texto, max, stdin);
    texto[strcspn(texto, "\n")] = 0;
}



void menu() {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Ingresar productos\n");
    printf("2. Mostrar productos\n");
    printf("3. Editar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Solicitud del cliente\n");
    printf("0. Salir\n");
    printf("Opcion: ");
}



void ingresarRecursos() {
    printf("\nCantidad de recursos: ");
    numRecursos = leerEnteroNoNegativo();

    for (int i = 0; i < numRecursos; i++) {
        printf("Nombre recurso %d: ", i + 1);
        leerCadena(nombresRecursos[i], MAX_NOMBRE);

        printf("Cantidad disponible: ");
        cantidadTotalRecursos[i] = leerEnteroNoNegativo();
    }

    printf("Tiempo disponible de la fabrica: ");
    tiempoFabrica = leerFlotanteNoNegativo();
}



void ingresarProductos() {
    printf("\nCantidad de productos a ingresar: ");
    int nuevos = leerEnteroNoNegativo();

    for (int i = numProductos; i < numProductos + nuevos; i++) {

        printf("Nombre del producto %d: ", i + 1);
        leerCadena(nombresProductos[i], MAX_NOMBRE);

        printf("Tiempo por unidad: ");
        tiempoFabricacion[i] = leerFlotanteNoNegativo();

        for (int r = 0; r < numRecursos; r++) {
            printf("Uso de %s por unidad: ", nombresRecursos[r]);
            recursosNecesarios[i][r] = leerEnteroNoNegativo();
        }
    }

    numProductos += nuevos;
}

void mostrarProductos() {
    printf("\n=== PRODUCTOS ===\n");

    for (int i = 0; i < numProductos; i++) {
        printf("\nProducto: %s\n", nombresProductos[i]);
        printf("Tiempo por unidad: %.2f\n", tiempoFabricacion[i]);

        for (int r = 0; r < numRecursos; r++) {
            printf("   %s: %d\n", nombresRecursos[r], recursosNecesarios[i][r]);
        }
    }
}

void editarProducto() {
    char buscar[MAX_NOMBRE];
    printf("Nombre del producto: ");
    leerCadena(buscar, MAX_NOMBRE);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(buscar, nombresProductos[i]) == 0) {

            printf("Nuevo nombre: ");
            leerCadena(nombresProductos[i], MAX_NOMBRE);

            printf("Nuevo tiempo por unidad: ");
            tiempoFabricacion[i] = leerFlotanteNoNegativo();

            for (int r = 0; r < numRecursos; r++) {
                printf("Nuevo uso de %s por unidad: ", nombresRecursos[r]);
                recursosNecesarios[i][r] = leerEnteroNoNegativo();
            }
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    char buscar[MAX_NOMBRE];
    printf("Producto a eliminar: ");
    leerCadena(buscar, MAX_NOMBRE);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(buscar, nombresProductos[i]) == 0) {

            for (int j = i; j < numProductos - 1; j++) {
                strcpy(nombresProductos[j], nombresProductos[j + 1]);
                tiempoFabricacion[j] = tiempoFabricacion[j + 1];

                for (int r = 0; r < numRecursos; r++)
                    recursosNecesarios[j][r] = recursosNecesarios[j + 1][r];
            }

            numProductos--;
            printf("Producto eliminado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}



void solicitudCliente() {
    if (numProductos == 0) {
        printf("\nNo hay productos registrados. Ingrese productos primero.\n");
        return;
    }

    int pedidoCantidades[MAX_PRODUCTOS] = {0};
    char nombre[MAX_NOMBRE];
    printf("\n=== SOLICITUD DEL CLIENTE ===\n");
    printf("Ingrese productos (escriba 'fin' para terminar)\n");

    while (1) {
        printf("Producto: ");
        leerCadena(nombre, MAX_NOMBRE);

        if (strcmp(nombre, "fin") == 0) {
            break;
        }

        int idx = -1;
        for (int i = 0; i < numProductos; i++) {
            if (strcmp(nombre, nombresProductos[i]) == 0) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            printf("Producto no encontrado. Intente nuevamente.\n");
            continue;
        }

        printf("Cantidad: ");
        int q = leerEnteroNoNegativo();
        pedidoCantidades[idx] += q;
    }

    int hayPedido = 0;
    for (int i = 0; i < numProductos; i++) {
        if (pedidoCantidades[i] > 0) { hayPedido = 1; break; }
    }

    if (!hayPedido) {
        printf("Pedido vacio. Nada que evaluar.\n");
        return;
    }

    float tiempoNecesario = 0.0f;
    int recursosNecesariosTotales[MAX_RECURSOS] = {0};

    for (int i = 0; i < numProductos; i++) {
        if (pedidoCantidades[i] == 0) continue;

        tiempoNecesario += pedidoCantidades[i] * tiempoFabricacion[i];

        for (int r = 0; r < numRecursos; r++) {
            recursosNecesariosTotales[r] += pedidoCantidades[i] * recursosNecesarios[i][r];
        }
    }

    printf("\n--- RESUMEN DEL PEDIDO ---\n");
    for (int i = 0; i < numProductos; i++) {
        if (pedidoCantidades[i] > 0) {
            printf("- %s: %d (%.2f por unidad)\n",
                   nombresProductos[i], pedidoCantidades[i], tiempoFabricacion[i]);
        }
    }
    printf("Tiempo total requerido: %.2f\n", tiempoNecesario);

    printf("\nRecursos requeridos:\n");
    for (int r = 0; r < numRecursos; r++) {
        printf("%s: %d (disponible: %d)\n",
               nombresRecursos[r], recursosNecesariosTotales[r], cantidadTotalRecursos[r]);
    }

    printf("\n--- FACTIBILIDAD DEL PEDIDO ---\n");
    int ok = 1;

    if (tiempoNecesario > tiempoFabrica) {
        printf("No cumple el tiempo. (Necesario: %.2f  Disponible: %.2f)\n",
               tiempoNecesario, tiempoFabrica);
        ok = 0;
    } else {
        printf("Tiempo OK.\n");
    }

    for (int r = 0; r < numRecursos; r++) {
        if (recursosNecesariosTotales[r] > cantidadTotalRecursos[r]) {
            printf("Recurso insuficiente: %s (falta %d)\n",
                   nombresRecursos[r],
                   recursosNecesariosTotales[r] - cantidadTotalRecursos[r]);
            ok = 0;
        }
    }

    if (ok)
        printf("El pedido ES FACTIBLE.\n");
    else
        printf("El pedido NO es factible.\n");
}