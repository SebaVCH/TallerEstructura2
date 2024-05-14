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
    int idProducto;
    string nombreProducto;
    int cantEnStock;

public:
    Producto(std::string categoria, std::string subcategoria,int idProducto,std:: string nombreProducto, float precio,int cantEnStock );

    string getCategoria() ;
    void setCategoria(std::string categoria);

    string getSubcategoria() ;
    void setSubcategoria(std::string subcategoria);


    float getPrecio() ;
    void setPrecio(float precio);

    int getIdProducto() ;
    void setIdProducto(int idProducto);

    string getNombreProducto() ;
    void setNombreProducto(std::string nombreProducto);

    int getCantEnStock() ;
    void setCantEnStock(int cantEnStock);
    
};

#endif //TALLERESTRUCTURA2_PRODUCTO_H
