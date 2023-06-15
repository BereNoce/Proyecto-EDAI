#include "Producto.h"

/**
 * The function imports product data from a CSV file and stores it in an
 * array of Product structs.
 *
 * @param productos an array of Producto structures where the imported data
 * will be stored.
 * @param numProductos A pointer to an integer variable that will store the
 * number of products imported from the CSV file.
 *
 * @return The function doesn't return anything; it has a void return type.
 */
void Producto_importarCSV(TAD_Productos* productos) {
    FILE *archivo = fopen("productos.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[MAX_CHAR];
    productos->numProductos = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (productos->numProductos >= MAX_PRODUCTS) {
            printf("Se ha alcanzado el número máximo de productos permitidos.\n");
            break;
        }

        char *token;
        Producto producto;

        // Obtener el nombre del producto
        token = strtok(linea, ",");
        if (token != NULL) {
            strncpy(producto.nombre, token, sizeof(producto.nombre) - 1);
            producto.nombre[sizeof(producto.nombre) - 1] = '\0';
        }

        // Obtener el ID del producto
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(producto.id, token, sizeof(producto.id) - 1);
            producto.id[sizeof(producto.id) - 1] = '\0';
        }

        // Obtener la categoría del producto
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(producto.categoria, token, sizeof(producto.categoria) - 1);
            producto.categoria[sizeof(producto.categoria) - 1] = '\0';
        }

        // Obtener el stock del producto
        token = strtok(NULL, ",");
        if (token != NULL) {
            producto.stock = atoi(token);
        }

        // Obtener el precio de venta del producto
        token = strtok(NULL, ",");
        if (token != NULL) {
            producto.precio_venta = atof(token);
        }

        // Obtener las ventas del producto
        token = strtok(NULL, ",");
        if (token != NULL) {
            producto.ventas = atoi(token);
        }

        productos->productos[productos->numProductos] = producto;
        productos->numProductos++;
    }

    fclose(archivo);
}

/**
 * The function adds a new product to an array of products, prompting the
 * user to input the product's name, ID, category, stock, and price.
 *
 * @param productos an array of Producto structures, representing the list
 * of products.
 * @param numProductos A pointer to an integer variable that stores the
 * current number of products in the array.
 *
 * @return Nothing is being explicitly returned in this function. However,
 * the function may return control to the calling function prematurely if
 * the maximum number of products has already been reached.
 */
void Producto_agregar(TAD_Productos* productos) {
    if (productos->numProductos >= MAX_PRODUCTS) {
        printf("No se pueden agregar más productos. Límite alcanzado.\n");
        return;
    }

    Producto nuevoProducto;

    printf("Ingrese el nombre del producto: ");
    fgets(nuevoProducto.nombre, sizeof(nuevoProducto.nombre), stdin);
    nuevoProducto.nombre[strcspn(nuevoProducto.nombre, "\n")] = '\0';  // Eliminar el salto de línea

    printf("Ingrese el ID del producto: ");
    fgets(nuevoProducto.id, sizeof(nuevoProducto.id), stdin);
    nuevoProducto.id[strcspn(nuevoProducto.id, "\n")] = '\0';  // Eliminar el salto de línea

    int categoriaValida = 0;
    while (!categoriaValida) {
        printf("Ingrese la categoría del producto (Bebida/Postre/Pizza): ");
        fgets(nuevoProducto.categoria, sizeof(nuevoProducto.categoria), stdin);
        nuevoProducto.categoria[strcspn(nuevoProducto.categoria, "\n")] = '\0';  // Eliminar el salto de línea

        if (strcmp(nuevoProducto.categoria, "Bebida") == 0 || strcmp(nuevoProducto.categoria, "Postre") == 0 ||
            strcmp(nuevoProducto.categoria, "Pizza") == 0) {
            categoriaValida = 1;
        } else {
            printf("Categoría inválida. Por favor, ingrese una categoría válida.\n");
        }
    }

    printf("Ingrese el stock del producto: ");
    scanf("%d", &nuevoProducto.stock);
    getchar();  // Consumir el carácter de nueva línea residual en el búfer de entrada

    printf("Ingrese el precio de venta del producto: ");
    scanf("%f", &nuevoProducto.precio_venta);
    getchar();  // Consumir el carácter de nueva línea residual en el búfer de entrada

    printf("Ingrese las ventas del producto: ");
    scanf("%d", &nuevoProducto.ventas);
    getchar();  // Consumir el carácter de nueva línea residual en el búfer de entrada

    productos->productos[productos->numProductos] = nuevoProducto;
    productos->numProductos++;

    Producto_modificarCSV("productos.csv", productos);
}

/**
 * The function exports data of products to a CSV file.
 *
 * @param productos an array of Producto structures that contains the
 * product data to be exported to a CSV file.
 * @param numProductos The number of products in the "productos" array.
 *
 * @return The function does not return anything; it is a void function.
 */
void Producto_exportarCSV(const TAD_Productos* productos) {
    FILE* archivoCSV = fopen("productos.csv", "a");  // Abrir en modo "append"

    if (archivoCSV == NULL) {
        printf("Error al abrir el archivo productos.csv\n");
        return;
    }

    // Escribir datos de los productos en el CSV
    for (int i = 0; i < productos->numProductos; ++i) {
        if (!Producto_existeEnCSV("productos.csv", productos->productos[i].nombre)) {
            fprintf(archivoCSV, "%s,%s,%s,%d,%.2f,%d\n", productos->productos[i].nombre, productos->productos[i].id,
                    productos->productos[i].categoria, productos->productos[i].stock, productos->productos[i].precio_venta,
                    productos->productos[i].ventas);
        }
    }

    fclose(archivoCSV);

    printf("Datos de productos exportados exitosamente a productos.csv\n");
}

/**
 * The function prints a list of products with their respective information.
 *
 * @param productos an array of Producto structures, representing a list of
 * products
 * @param numProductos The number of products in the "productos" array.
 *
 * @return The function does not return anything; it is a void function.
 */
void Producto_listar(const TAD_Productos* productos) {
    printf("Lista de productos:\n");
    printf("Nombre\t\tID\t\tCategoría\tStock\tPrecio de Venta\tVentas\n");
    for (int i = 0; i < productos->numProductos; ++i) {
        printf("%s\t%s\t%s\t%d\t%.2f\t\t%d\n", productos->productos[i].nombre, productos->productos[i].id,
               productos->productos[i].categoria, productos->productos[i].stock, productos->productos[i].precio_venta,
               productos->productos[i].ventas);
    }
}

/**
 * The function displays a list of pizzas with their details such as name,
 * ID, category, stock, price, and sales.
 *
 * @param productos an array of Producto structures
 * @param numProductos The number of elements in the array of Productos.
 *
 * @return The function does not return anything; it is a void function.
 */
void Producto_mostrarPizzas(const TAD_Productos* productos) {
    printf("Lista de pizzas:\n");
    printf("Nombre\t\tID\t\tCategoría\tStock\tPrecio de Venta\tVentas\n");

    int encontradas = 0;

    for (int i = 0; i < productos->numProductos; ++i) {
        if (strcmp(productos->productos[i].categoria, "Pizza") == 0) {
            printf("%s\t%s\t%s\t%d\t%.2f\t\t%d\n", productos->productos[i].nombre, productos->productos[i].id,
                   productos->productos[i].categoria, productos->productos[i].stock, productos->productos[i].precio_venta,
                   productos->productos[i].ventas);
            encontradas = 1;
        }
    }

    if (!encontradas) {
        printf("No se encontraron pizzas.\n");
    }
}

/**
 * The function "Producto_mostrarPostres" displays a list of dessert 
 * products with their respective information.
 * 
 * @param productos an array of Producto structures
 * @param numProductos The number of elements in the array of Productos.
 *
 * @return The function does not return anything; it is a void function.
 */
void Producto_mostrarPostres(const TAD_Productos* productos) {
    printf("Lista de postres:\n");
    printf("Nombre\t\tID\t\tCategoría\tStock\tPrecio de Venta\tVentas\n");

    for (int i = 0; i < productos->numProductos; ++i) {
        if (strcmp(productos->productos[i].categoria, "Postre") == 0) {
            printf("%s\t%s\t%s\t%d\t%.2f\t\t%d\n", productos->productos[i].nombre, productos->productos[i].id,
                   productos->productos[i].categoria, productos->productos[i].stock, productos->productos[i].precio_venta,
                   productos->productos[i].ventas);
        }
    }
}

/**
 * The function "Producto_mostrarBebidas" displays a list of products that 
 * belong to the "Bebida" category.
 * 
 * @param productos an array of Producto structures
 * @param numProductos The number of products in the "productos" array.
 *
 * @return The function does not return anything; it is a void function.
 */
void Producto_mostrarBebidas(const TAD_Productos* productos) {
    printf("Lista de bebidas:\n");
    printf("Nombre\t\tID\t\tCategoría\tStock\tPrecio de Venta\tVentas\n");

    for (int i = 0; i < productos->numProductos; ++i) {
        if (strcmp(productos->productos[i].categoria, "Bebida") == 0) {
            printf("%s\t%s\t%s\t%d\t%.2f\t\t%d\n", productos->productos[i].nombre, productos->productos[i].id,
                   productos->productos[i].categoria, productos->productos[i].stock, productos->productos[i].precio_venta,
                   productos->productos[i].ventas);
        }
    }
}

/**
 * The function allows the user to search for a product by either name or ID 
 * and displays its information if found.
 * 
 * @param productos an array of Producto structures, representing a list of 
 * products
 * @param numProductos The number of products in the array "productos".
 *
 * @return The function does not return anything; it is a void function.
 */
void Producto_buscar(const TAD_Productos* productos) {
    char nombreBusqueda[MAX_CHAR];
    printf("Ingrese el nombre del producto a buscar: ");
    fgets(nombreBusqueda, sizeof(nombreBusqueda), stdin);
    nombreBusqueda[strcspn(nombreBusqueda, "\n")] = '\0';  // Eliminar el salto de línea

    int encontrado = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].nombre, nombreBusqueda) == 0) {
            printf("Producto encontrado:\n");
            printf("Nombre: %s\n", productos->productos[i].nombre);
            printf("ID: %s\n", productos->productos[i].id);
            printf("Categoría: %s\n", productos->productos[i].categoria);
            printf("Stock: %d\n", productos->productos[i].stock);
            printf("Precio de venta: %.2f\n", productos->productos[i].precio_venta);
            printf("Ventas: %d\n", productos->productos[i].ventas);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

/**
 * The function removes a product from the array of Product structs based on the product name.
 *
 * @param productos An array of Product structures from which the product will be removed.
 * @param numProductos A pointer to an integer variable that stores the number of products.
 *
 * @return Nothing is being returned; the function has a void return type.
 */
void Producto_eliminar(TAD_Productos* productos) {
    char nombreEliminar[MAX_CHAR];
    printf("Ingrese el nombre del producto a eliminar: ");
    fgets(nombreEliminar, sizeof(nombreEliminar), stdin);
    nombreEliminar[strcspn(nombreEliminar, "\n")] = '\0';  // Eliminar el salto de línea

    int encontrado = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].nombre, nombreEliminar) == 0) {
            encontrado = 1;

            // Desplazar los elementos restantes hacia atrás para eliminar el producto
            memmove(&productos->productos[i], &productos->productos[i + 1], sizeof(Producto) * (productos->numProductos - i - 1));

            (productos->numProductos)--;
            printf("Producto eliminado exitosamente.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
    Producto_modificarCSV("productos.csv", productos);
}

/**
 * The function "Producto_stock" retrieves the stock quantity of a product based on its name or ID.
 *
 * @param productos An array of Producto structures representing the list of products.
 * @param nombre_or_id The name or ID of the product to search for.
 *
 * @return The stock quantity of the product if found, -1 otherwise.
 */
int Producto_stock(const TAD_Productos* productos, const char* nombre_or_id) {
    int numProductos = productos->numProductos;

    for (int i = 0; i < numProductos; ++i) {
        if (strcmp(productos->productos[i].nombre, nombre_or_id) == 0 || strcmp(productos->productos[i].id, nombre_or_id) == 0) {
            return productos->productos[i].stock;
        }
    }
    return -1;  // Product not found
}

/**
 * The function "Producto_modificaciones" allows modifications to be made to an existing product
 * in the array of Product structs.
 *
 * @param productos An array of Product structures where the product data is stored.
 * @param numProductos The number of products in the array.
 *
 * @return Nothing is being returned; the function has a void return type.
 */
void Producto_modificaciones(TAD_Productos* productos) {
    // Declarar la variable nuevoProducto
    Producto nuevoProducto;

    // Obtener los datos del nuevo producto
    printf("Ingrese el nombre del producto: ");
    fgets(nuevoProducto.nombre, sizeof(nuevoProducto.nombre), stdin);
    nuevoProducto.nombre[strcspn(nuevoProducto.nombre, "\n")] = '\0';  // Eliminar el salto de línea

    // Buscar el producto a modificar por su nombre
    int encontrado = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].nombre, nuevoProducto.nombre) == 0) {
            encontrado = 1;

            // Obtener los datos restantes del nuevo producto
            printf("Ingrese el ID del producto: ");
            fgets(nuevoProducto.id, sizeof(nuevoProducto.id), stdin);
            nuevoProducto.id[strcspn(nuevoProducto.id, "\n")] = '\0';  // Eliminar el salto de línea

            printf("Ingrese la categoría del producto (Pizza, Bebida, Postre): ");
            fgets(nuevoProducto.categoria, sizeof(nuevoProducto.categoria), stdin);
            nuevoProducto.categoria[strcspn(nuevoProducto.categoria, "\n")] = '\0';  // Eliminar el salto de línea

            // Verificar que la categoría sea válida
            if (strcmp(nuevoProducto.categoria, "Pizza") != 0 &&
                strcmp(nuevoProducto.categoria, "Bebida") != 0 &&
                strcmp(nuevoProducto.categoria, "Postre") != 0) {
                printf("Categoría inválida. Solo se permiten las categorías: Pizza, Bebida, Postre.\n");
                return;
            }

            printf("Ingrese el stock del producto: ");
            scanf("%d", &nuevoProducto.stock);
            getchar();  // Capturar el carácter de nueva línea después del scanf

            printf("Ingrese el precio de venta del producto: ");
            scanf("%f", &nuevoProducto.precio_venta);
            getchar();  // Capturar el carácter de nueva línea después del scanf

            printf("Ingrese las ventas del producto: ");
            scanf("%d", &nuevoProducto.ventas);
            getchar();  // Capturar el carácter de nueva línea después del scanf

            // Actualizar los datos del producto encontrado con los nuevos datos
            strcpy(productos->productos[i].id, nuevoProducto.id);
            strcpy(productos->productos[i].categoria, nuevoProducto.categoria);
            productos->productos[i].stock = nuevoProducto.stock;
            productos->productos[i].precio_venta = nuevoProducto.precio_venta;
            productos->productos[i].ventas = nuevoProducto.ventas;

            printf("Producto modificado exitosamente.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }

    // Modificar el archivo CSV con los cambios realizados
    Producto_modificarCSV("productos.csv", productos);
}

/**
 * The function "Producto_modificarCSV" modifies the CSV file by updating the data of a specific product.
 *
 * @param archivo The name of the original file.
 * @param productos A pointer to the TAD_Productos structure containing the updated product data.
 *
 * @return Nothing is being returned; the function has a void return type.
 */
void Producto_modificarCSV(const char* archivo, const TAD_Productos* productos) {
    FILE* archivoOriginal = fopen(archivo, "r");
    if (archivoOriginal == NULL) {
        printf("Error al abrir el archivo original.\n");
        return;
    }

    FILE* archivoTemp = fopen("productos_temp.csv", "w");
    if (archivoTemp == NULL) {
        printf("Error al abrir el archivo temporal.\n");
        fclose(archivoOriginal);
        return;
    }

    char linea[MAX_CHAR];
    while (fgets(linea, sizeof(linea), archivoOriginal)) {
        char token[MAX_CHAR];
        strcpy(token, linea);
        char* nombre = strtok(token, ",");
        if (nombre != NULL && strcmp(nombre, productos->productos[productos->numProductos - 1].nombre) == 0) {
            // Escribir la línea modificada en el archivo temporal
            fprintf(archivoTemp, "%s,%s,%s,%d,%.2f,%d\n",
                    productos->productos[productos->numProductos - 1].nombre,
                    productos->productos[productos->numProductos - 1].id,
                    productos->productos[productos->numProductos - 1].categoria,
                    productos->productos[productos->numProductos - 1].stock,
                    productos->productos[productos->numProductos - 1].precio_venta,
                    productos->productos[productos->numProductos - 1].ventas);
        } else {
            // Escribir la línea original en el archivo temporal
            fputs(linea, archivoTemp);
        }
    }

    fclose(archivoOriginal);
    fclose(archivoTemp);

    // Renombrar el archivo temporal al archivo original
    if (rename("productos_temp.csv", archivo) != 0) {
        printf("Error al renombrar el archivo temporal.\n");
    }
}

/**
 * The function "Producto_obtenerPreciosPizzas" retrieves the prices of all pizzas from the array of products.
 *
 * @param productos An array of Product structures.
 * @param numProductos The number of products in the array.
 * @param numPrecios A pointer to an integer variable that will store the number of pizza prices retrieved.
 *
 * @return A dynamically allocated array of floats containing the prices of pizzas. The array size will be equal to the number of pizzas.
 */
float* Producto_obtenerPreciosPizzas(const TAD_Productos* productos, int* numPrecios) {
    int contador = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].categoria, "Pizza") == 0) {
            contador++;
        }
    }

    float* PrecioPizzas = malloc(contador * sizeof(float));
    if (PrecioPizzas == NULL) {
        printf("Error al asignar memoria para los precios de las pizzas.\n");
        *numPrecios = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].categoria, "Pizza") == 0) {
            PrecioPizzas[index] = productos->productos[i].precio_venta;
            index++;
        }
    }

    *numPrecios = contador;
    return PrecioPizzas;
}

/**
 * The function "Producto_obtenerPreciosBebidas" retrieves the prices of all beverages from the array of products.
 *
 * @param productos An array of Product structures.
 * @param numProductos The number of products in the array.
 * @param numPrecios A pointer to an integer variable that will store the number of beverage prices retrieved.
 *
 * @return A dynamically allocated array of floats containing the prices of beverages. The array size will be equal to the number of beverages.
 */
 
float* Producto_obtenerPreciosBebidas(const TAD_Productos* productos, int* numPrecios) {
    int contador = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].categoria, "Bebida") == 0) {
            contador++;
        }
    }

    float* PrecioBebidas = malloc(contador * sizeof(float));
    if (PrecioBebidas == NULL) {
        printf("Error al asignar memoria para los precios de las bebidas.\n");
        *numPrecios = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].categoria, "Bebida") == 0) {
            PrecioBebidas[index] = productos->productos[i].precio_venta;
            index++;
        }
    }

    *numPrecios = contador;
    return PrecioBebidas;
}

/**
 * The function "Producto_obtenerPreciosPostres" retrieves the prices of all desserts from the array of products.
 *
 * @param productos An array of Product structures.
 * @param numProductos The number of products in the array.
 * @param numPrecios A pointer to an integer variable that will store the number of dessert prices retrieved.
 *
 * @return A dynamically allocated array of floats containing the prices of desserts. The array size will be equal to the number of desserts.
 */
float* Producto_obtenerPreciosPostres(const TAD_Productos* productos, int* numPrecios) {
    int contador = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].categoria, "Postre") == 0) {
            contador++;
        }
    }

    float* PrecioPostres = malloc(contador * sizeof(float));
    if (PrecioPostres == NULL) {
        printf("Error allocating memory for dessert prices.\n");
        *numPrecios = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < productos->numProductos; i++) {
        if (strcmp(productos->productos[i].categoria, "Postre") == 0) {
            PrecioPostres[index] = productos->productos[i].precio_venta;
            index++;
        }
    }

    *numPrecios = contador;
    return PrecioPostres;
}

/**
 * The function frees the dynamically allocated memory for a float array.
 *
 * @param arreglo The pointer to the float array that needs to be freed.
 *
 * @return Nothing is being returned, the function has a void return type.
 */
void Producto_liberarMemoria(float* arreglo) {
    free(arreglo);
}

/**
 * The function checks if a given product name exists in a CSV file.
 *
 * @param archivo The name of the CSV file to search in.
 * @param nombre The product name to search for.
 *
 * @return Returns true if the product name exists in the CSV file, false otherwise.
 */
bool Producto_existeEnCSV(const char* archivo, const char* nombre) {
    FILE* archivoCSV = fopen(archivo, "r");
    if (archivoCSV == NULL) {
        printf("Error al abrir el archivo productos.csv\n");
        return false;
    }

    char linea[MAX_CHAR];
    while (fgets(linea, sizeof(linea), archivoCSV)) {
        char token[MAX_CHAR];
        strcpy(token, linea);
        char* nombreProducto = strtok(token, ",");
        if (nombreProducto != NULL && strcmp(nombreProducto, nombre) == 0) {
            fclose(archivoCSV);
            return true;
        }
    }

    fclose(archivoCSV);
    return false;
}