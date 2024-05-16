//
// Created by sebav on 16-05-2024.
//

#include "../include/HashMap.h"

HashMap::HashMap() {
    capacidad = sizeInicial;
    numElementosAlmacenados = 0;
    tabla = new Producto * [capacidad]();
}

HashMap::~HashMap(){

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr){
            delete tabla[i];
        }
    }

    delete[] tabla;

}

int HashMap::hash(const string &clave) const {
    int hash = 0;

    for(char c : clave){
        hash += c;
    }

    return hash % capacidad;

}

void HashMap::rehash() {

    int nuevaCapacidad = capacidad * 2;

    Producto** nuevaTabla = new Producto* [nuevaCapacidad]();

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i]!= nullptr){
            int nuevoIndice = hash(tabla[i]->getNombreProducto());
            while (nuevaTabla[nuevoIndice] != nullptr){
                nuevoIndice = (nuevoIndice + 1) % nuevaCapacidad;
            }

            nuevaTabla[nuevoIndice] = tabla[i];

        }
    }

    delete[] tabla;
    tabla = nuevaTabla;
    capacidad = nuevaCapacidad;

}

void HashMap::insertarProducto(Producto *producto) {

    if (numElementosAlmacenados >= capacidad /2){
        rehash();
    }

    int indice = hash(producto->getNombreProducto());

    while (tabla[indice] != nullptr) {
        indice = (indice + 1) % capacidad;
    }

    tabla[indice] = producto;
    numElementosAlmacenados++;

}

Producto *HashMap::buscar(int id){

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr && tabla[i]->getIdProducto() == id){
            return tabla[i];
        }
    }

    return nullptr;
}

void HashMap::eliminarProducto(int id) {

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr && tabla[i]->getIdProducto() == id){
            delete tabla[i];
            tabla[i] = nullptr;
            numElementosAlmacenados--;
            return;
        }
    }

}

int HashMap::obtenerCantElementos() {
    return numElementosAlmacenados;
}




