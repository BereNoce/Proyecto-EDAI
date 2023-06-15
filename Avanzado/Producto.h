#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MIN_STOCK 10
#define MAX_PRODUCTS 100

typedef struct {
  char nombre[MAX_CHAR];
  char id[10];
  char categoria[12];
  int stock;
  float precio_venta;
  int ventas;
} Producto;

typedef struct {
    Producto* productos;
    int numProductos;
} TAD_Productos;

void Producto_importarCSV(TAD_Productos* productos);
void Producto_agregar(TAD_Productos* productos);
void Producto_exportarCSV(const TAD_Productos* productos);
void Producto_listar(const TAD_Productos* productos);
void Producto_mostrarPizzas(const TAD_Productos* productos);
void Producto_mostrarBebidas(const TAD_Productos* productos);
void Producto_mostrarPostres(const TAD_Productos* productos);
void Producto_buscar(const TAD_Productos* productos);
void Producto_eliminar(TAD_Productos* productos);
float* Producto_obtenerPreciosPizzas(const TAD_Productos* productos, int* numPrecios);
float* Producto_obtenerPreciosBebidas(const TAD_Productos* productos, int* numPrecios);
float* Producto_obtenerPreciosPostres(const TAD_Productos* productos, int* numPrecios);
int Producto_stock(const TAD_Productos* productos, const char* nombre_or_id);
void Producto_modificaciones(TAD_Productos* productos);
void Producto_modificarCSV(const char* archivo, const TAD_Productos* productos);
void Producto_liberarMemoria(float* arreglo);
bool Producto_existeEnCSV(const char* archivo, const char* nombre);

#endif

