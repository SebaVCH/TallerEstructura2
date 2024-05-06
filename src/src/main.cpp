#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include "../include/clienteGeneral.h"
#include "../include/clienteNormal.h"
#include "../include/clientePreferencial.h"

using namespace std;


void atenderCliente();
void cargarProductosBodega();
void guardarDatosBodega();
queue<clienteGeneral*> cargarDatosClientesOrdenados();
void guardarDatosClientes();


int main() {

    queue<clienteGeneral*> listaClientes = cargarDatosClientesOrdenados();

    
    while (!listaClientes.empty()){
        cout << listaClientes.front()->getNombre() << endl;
        listaClientes.pop();

    }

    return 0;
}

queue<clienteGeneral*> cargarDatosClientesOrdenados() {

    //Cargar datos de los clientes

    queue<clienteGeneral*> lista;
    ifstream archivo("D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt");
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombre;
            string tipoCliente;

            getline(ss, nombre, ',');

            if (!ss.eof()) { // Verificar si hay más datos después de la coma
                getline(ss, tipoCliente);
                lista.push(new clientePreferencial(nombre, tipoCliente));
            } else {
                lista.push(new clienteNormal(nombre));
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo clientes.txt" << endl;
    }
    //Ordenar la fila por orden preferencial
    queue<clienteGeneral*> terceraEdad;
    queue<clienteGeneral*> discapacidad;
    queue<clienteGeneral*> embarazada;
    queue<clienteGeneral*> normal;

    queue<clienteGeneral*> ordenada;

    while (!lista.empty()) {
        clienteGeneral* cliente = lista.front();
        lista.pop();

        if (dynamic_cast<clientePreferencial*>(cliente)) {
            clientePreferencial* clientePref = dynamic_cast<clientePreferencial*>(cliente);
            string tipo = clientePref->getTipoDeCliente();
            if (tipo == "Tercera edad") {
                terceraEdad.push(cliente);
            } else if (tipo == "Discapacidad") {
                discapacidad.push(cliente);
            } else if (tipo == "Embarazada") {
                embarazada.push(cliente);
            }
        } else {
            normal.push(cliente);
        }
    }

    while (!terceraEdad.empty()) {
        ordenada.push(terceraEdad.front());
        terceraEdad.pop();
    }
    while (!discapacidad.empty()) {
        ordenada.push(discapacidad.front());
        discapacidad.pop();
    }
    while (!embarazada.empty()) {
        ordenada.push(embarazada.front());
        embarazada.pop();
    }
    while (!normal.empty()) {
        ordenada.push(normal.front());
        normal.pop();
    }

    return ordenada;

}
