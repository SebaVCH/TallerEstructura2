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

void Producto::setCategoria(string categoria) {
    this->categoria = categoria;
}

string Producto::getSubcategoria()  {
    return subcategoria;
}

void Producto::setSubcategoria(string subcategoria) {
    this->subcategoria = subcategoria;
}

float Producto::getPrecio()  {
    return precio;
}

void Producto::setPrecio(float precio) {
    this->precio = precio;
}

string Producto::getIdProducto()  {
    return idProducto;
}

void Producto::setIdProducto(string idProducto) {
    this->idProducto = idProducto;
}

string Producto::getNombreProducto() { 
    return nombreProducto;
}

void Producto::setNombreProducto(string nombreProducto) {
    this->nombreProducto = nombreProducto;
}

int Producto::getCantEnStock()  {
    return cantEnStock;
}

void Producto::setCantEnStock(int cantEnStock) {
    this->cantEnStock = cantEnStock;
}