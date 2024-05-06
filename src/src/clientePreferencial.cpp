//
// Created by sebav on 06-05-2024.
//

#include "../include/clientePreferencial.h"

clientePreferencial::clientePreferencial(string nombre, string tipoDeCliente): clienteGeneral(nombre), tipoDeCliente(tipoDeCliente) {}

clientePreferencial::~clientePreferencial() {}

string clientePreferencial::getTipoDeCliente() {
    return tipoDeCliente;
}
