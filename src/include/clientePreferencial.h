//
// Created by sebav on 06-05-2024.
//

#ifndef TALLERESTRUCTURA2_CLIENTEPREFERENCIAL_H
#define TALLERESTRUCTURA2_CLIENTEPREFERENCIAL_H

#include "clienteGeneral.h"
using namespace std;

class clientePreferencial : public clienteGeneral {
private:
    string tipoDeCliente;

public:
    clientePreferencial(string nombre,string tipoDeCliente);
    ~clientePreferencial();
    string getTipoDeCliente();
};


#endif //TALLERESTRUCTURA2_CLIENTEPREFERENCIAL_H
