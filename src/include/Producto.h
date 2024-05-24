//
// Created by sebav on 03-05-2024.
//

#ifndef TALLERESTRUCTURA2_PRODUCTO_H
#define TALLERESTRUCTURA2_PRODUCTO_H

#include <iostream>
using namespace std;

class Producto {

    string categoria;
    string subcategoria;
    float precio;
    string idProducto;
    string nombreProducto;
    int cantEnStock;

public:
    Producto(string categoria, string subcategoria,string idProducto,string nombreProducto, float precio,int cantEnStock );

    string getCategoria() ;
    void setCategoria(string categoria);

    string getSubcategoria() ;
    void setSubcategoria(string subcategoria);


    float getPrecio() ;
    void setPrecio(float precio);

    string getIdProducto() ;
    void setIdProducto(string idProducto);

    string getNombreProducto() ;
    void setNombreProducto(string nombreProducto);

    int getCantEnStock() ;
    void setCantEnStock(int cantEnStock);
    
};

#endif //TALLERESTRUCTURA2_PRODUCTO_H
