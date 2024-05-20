//
// Created by sebav on 16-05-2024.
//

#ifndef TALLERESTRUCTURA2_HASHMAP_H
#define TALLERESTRUCTURA2_HASHMAP_H

#include <iostream>
#include "Producto.h"

class HashMap {
private:

    static const int sizeInicial = 100;
    Producto** tabla;
    int capacidad;
    int numElementosAlmacenados;

    int hash(const string &clave) const ;
    void rehash();

public:

    HashMap();
    ~HashMap();

    void insertarProducto(Producto* producto);
    Producto* buscar(int id);
    void eliminarProducto(int id);
    int obtenerCantElementos();
    void actualizarArchivo(const string& nombreArchivo);

    void limpiarHashMap();
};


#endif //TALLERESTRUCTURA2_HASHMAP_H
