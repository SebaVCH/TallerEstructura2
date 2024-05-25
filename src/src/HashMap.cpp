//
// Created by sebav on 16-05-2024.
//
#include <fstream>
#include <algorithm>
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

Producto *HashMap::buscar(string id){

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr && tabla[i]->getIdProducto() == id){
            return tabla[i];
        }
    }

    return nullptr;
}

void HashMap::eliminarProducto(string id) {

    Producto* producto = buscar(id);

    if (producto != nullptr && producto->getCantEnStock() <= 0) {
        for (int i = 0; i < capacidad; ++i) {
            if (tabla[i] != nullptr && tabla[i]->getIdProducto() == id){
                delete tabla[i];
                tabla[i] = nullptr;
                numElementosAlmacenados--;
                return;
            }
        }
    }
}

void HashMap::actualizarArchivo(string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int i = 0; i < capacidad; ++i) {
            if (tabla[i] != nullptr) {
                archivo << tabla[i]->getCategoria() << ","
                        << tabla[i]->getSubcategoria() << ","
                        << tabla[i]->getIdProducto() << ","
                        << tabla[i]->getNombreProducto() << ","
                        << tabla[i]->getPrecio() << ","
                        << tabla[i]->getCantEnStock() << endl;
            }
        }
        archivo.close();
        cout << "Archivo actualizado exitosamente." << endl;
    } else {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
    }
}

void HashMap::limpiarHashMap() {

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr) {
            delete tabla[i];
            tabla[i] = nullptr;
        }
    }
    numElementosAlmacenados = 0;

}

void HashMap::mostrarProductos() {

    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr) {
            Producto* producto = tabla[i];
            cout << "ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombreProducto() << endl;
        }
    }

}

void HashMap::mostrarProductosCategoria(string categoriaBuscada) {

    transform(categoriaBuscada.begin(), categoriaBuscada.end(), categoriaBuscada.begin(), ::tolower);
    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr) {
            string categoriaProducto = tabla[i]->getCategoria();
            transform(categoriaProducto.begin(), categoriaProducto.end(), categoriaProducto.begin(), ::tolower);
            if (categoriaProducto == categoriaBuscada) {
                Producto* producto = tabla[i];
                cout << "ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombreProducto() << endl;
            }
        }
    }
}

void HashMap::mostrarProductosSubCategoria(string subCategoriaBuscada) {

    transform(subCategoriaBuscada.begin(), subCategoriaBuscada.end(), subCategoriaBuscada.begin(), ::tolower);
    for (int i = 0; i < capacidad; ++i) {
        if (tabla[i] != nullptr) {
            string subCategoriaProducto = tabla[i]->getSubcategoria();
            transform(subCategoriaProducto.begin(), subCategoriaProducto.end(), subCategoriaProducto.begin(), ::tolower);
            if (subCategoriaProducto == subCategoriaBuscada) {
                Producto* producto = tabla[i];
                cout << "ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombreProducto() << endl;
            }
        }
    }

}


