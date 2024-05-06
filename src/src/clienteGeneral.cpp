//
// Created by sebav on 06-05-2024.
//

#include "../include/clienteGeneral.h"


clienteGeneral::clienteGeneral(string nombre) : nombre(nombre) {}

clienteGeneral::~clienteGeneral() {}

string clienteGeneral::getNombre() {
    return nombre;
}