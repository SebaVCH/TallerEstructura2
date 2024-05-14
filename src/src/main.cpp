#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include "../include/clienteGeneral.h"
#include "../include/clienteNormal.h"
#include "../include/clientePreferencial.h"
#include "../include/Producto.h"

using namespace std;

queue<clienteGeneral*> cargarDatosClientesOrdenados();
void agregarCliente(queue<clienteGeneral*> &lista);
queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &lista);
void llamarSiguienteCliente(queue<clienteGeneral*> &lista);

queue<Producto*>  cargarDatosProductos();


void menu(queue<clienteGeneral *> queue1);

int main() {

    queue<clienteGeneral*> listaClientes = cargarDatosClientesOrdenados();
    queue<Producto*> listaProductos = cargarDatosProductos();

    menu(listaClientes);

    return 0;
}

void menu(queue<clienteGeneral *> listaDeClientes) {

    int opcion;
    do {
        cout << "Seleccione una opcion:" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Llamar siguiente cliente" << endl;
        cout << "3. Productos en Bodega" << endl;
        cout << "4. Agregar Productos Bodega" << endl;
        cout << "5. Generar Boleta" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarCliente(listaDeClientes);
                break;
            case 2:
                llamarSiguienteCliente(listaDeClientes);
                break;
            case 3:
                //se pregunta q categoria y se muestra esa categoria cuantos tiene
                break;
            case 4:
                //Se preguntan todos los datos
                //Categoria,Sub-Categoria,ID,NombreProducto,Precio,CantidadElementos
                //Se agrega a bodega
                break;
            case 5:
                //Se pregunta por el ID de un producta que se desee vender, luego se revisa si esta disponible
                //Luego se imprime por pantalla algo como una boleta el valor y todo
                //Se restan los elementos de Bodega
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 0);
}

void agregarCliente(queue<clienteGeneral*> &lista) {

    //Agregar cliente a la fila
    string nombre;
    string tipoCliente;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;

    cout << "Ingrese el tipo de cliente (Tercera edad, Discapacidad, Embarazada, Normal): ";
    cin >> tipoCliente;
    if (tipoCliente == "Tercera edad" || tipoCliente == "Discapacidad" || tipoCliente == "Embarazada" || tipoCliente == "Normal") {
        if (tipoCliente == "Normal") {
            lista.push(new clienteNormal(nombre));
        } else {
            lista.push(new clientePreferencial(nombre, tipoCliente));
        }
        cout << "Cliente agregado correctamente a la cola." << endl;
    } else {
        cout << "Tipo de cliente inválido. Inténtelo de nuevo." << endl;
    }

    //Ordenar para mantener la preferencia
    ordenarSegunPreferencia(lista);

}


void llamarSiguienteCliente(queue<clienteGeneral*> &lista) {
    //Llamar al siguiente cliente
    if (!lista.empty()) {
        cout << "Cliente llamado: " << lista.front()->getNombre() << endl;
        delete lista.front();
        lista.pop();
    } else {
        cout << "No hay clientes en espera." << endl;
    }
}

queue<clienteGeneral*> cargarDatosClientesOrdenados() {

    //Cargar datos de los clientes
    queue<clienteGeneral*> lista;
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt"

    ifstream archivo("D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt");
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombre;
            string tipoCliente;

            getline(ss, nombre, ',');

            if (!ss.eof()) {
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

    //Ordenar luego de agregar los datos
    return ordenarSegunPreferencia(lista);

}
queue<Producto*>  cargarDatosProductos(){
    queue<Producto*> listaProductos;
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt"
    ifstream arch("D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\Bodega.txt");
    string linea;

     if (arch.is_open()) {
        while (getline(arch, linea)) {
            stringstream ss(linea);
            cout <<linea <<endl;


        }
        arch.close();
     }
     else {
        cout << "No se pudo abrir el archivo Productos.txt" << endl;
     }

    return listaProductos;


}
queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &lista) {
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
