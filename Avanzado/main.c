#include "Producto.h"

int main() {
    TAD_Productos productos;
    productos.productos = malloc(MAX_PRODUCTS * sizeof(Producto));
    productos.numProductos = 0;

    Producto_importarCSV(&productos);

    int opcion;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Agregar un producto\n");
        printf("2. Exportar productos a CSV\n");
        printf("3. Listar todos los productos\n");
        printf("4. Mostrar pizzas\n");
        printf("5. Mostrar bebidas\n");
        printf("6. Mostrar postres\n");
        printf("7. Buscar un producto\n");
        printf("8. Eliminar un producto\n");
        printf("9. Obtener stock de un producto\n");
        printf("10. Realizar modificaciones\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar();  // Consumir el carácter de nueva línea residual en el búfer de entrada

        switch (opcion) {
            case 1:
                Producto_agregar(&productos);
                break;
            case 2:
                Producto_exportarCSV(&productos);
                break;
            case 3:
                Producto_listar(&productos);
                break;
            case 4:
                Producto_mostrarPizzas(&productos);
                break;
            case 5:
                Producto_mostrarBebidas(&productos);
                break;
            case 6:
                Producto_mostrarPostres(&productos);
                break;
            case 7:
                Producto_buscar(&productos);
                break;
            case 8:
                Producto_eliminar(&productos);
                break;
            case 9:
                Producto_stock(&productos, NULL);
                break;
            case 10:
                Producto_modificaciones(&productos);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }
    } while (opcion != 0);

    free(productos.productos);
    return 0;
}







