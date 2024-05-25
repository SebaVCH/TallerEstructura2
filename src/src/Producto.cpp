//
// Created by sebav on 03-05-2024.
//

#include "../include/Producto.h"
using namespace std;

Producto::Producto(string categoria, string subcategoria,string idProducto,string nombreProducto, float precio,int cantEnStock ) {
    this->categoria = categoria;
    this->subcategoria = subcategoria;
    this->precio = precio;
    this->idProducto = idProducto;
    this->nombreProducto= nombreProducto;
    this->cantEnStock= cantEnStock;
}

string Producto::getCategoria()  {
    return categoria;
}

string Producto::getSubcategoria()  {
    return subcategoria;
}

float Producto::getPrecio()  {
    return precio;
}

string Producto::getIdProducto()  {
    return idProducto;
}

string Producto::getNombreProducto() { 
    return nombreProducto;
}

int Producto::getCantEnStock()  {
    return cantEnStock;
}

void Producto::setCantEnStock(int cantEnStock) {
    this->cantEnStock = cantEnStock;
}