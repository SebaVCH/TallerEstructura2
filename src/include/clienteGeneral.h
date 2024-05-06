//
// Created by sebav on 06-05-2024.
//

#ifndef TALLERESTRUCTURA2_CLIENTEGENERAL_H
#define TALLERESTRUCTURA2_CLIENTEGENERAL_H

#include <iostream>
using namespace std;

class clienteGeneral {

private:
    string nombre;

public:
    clienteGeneral(string nombre);

    virtual ~clienteGeneral();
    string getNombre();

};


#endif //TALLERESTRUCTURA2_CLIENTEGENERAL_H
