//
// Created by sebav on 03-05-2024.
//

#include "../include/Producto.h"
using namespace std;

Producto::Producto(string categoria, string subcategoria,int idProducto,std:: string nombreProducto, float precio,int cantEnStock ) {
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

void Producto::setCategoria(std::string categoria) {
    this->categoria = categoria;
}

string Producto::getSubcategoria()  {
    return subcategoria;
}

void Producto::setSubcategoria(std::string subcategoria) {
    this->subcategoria = subcategoria;
}

float Producto::getPrecio()  {
    return precio;
}

void Producto::setPrecio(float precio) {
    this->precio = precio;
}

int Producto::getIdProducto()  {
    return idProducto;
}

void Producto::setIdProducto(int idProducto) {
    this->idProducto = idProducto;
}

string Producto::getNombreProducto() { 
    return nombreProducto;
}

void Producto::setNombreProducto(std::string nombreProducto) { 
    this->nombreProducto = nombreProducto;
}