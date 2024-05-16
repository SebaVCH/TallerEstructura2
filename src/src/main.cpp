#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include "../include/clienteGeneral.h"
#include "../include/clienteNormal.h"
#include "../include/clientePreferencial.h"
#include "../include/Producto.h"
#include "../include/HashMap.h"

using namespace std;

//Menu
void menu(queue<clienteGeneral *> listaClientes, HashMap listaProductos);

//Cargar Datos
queue<clienteGeneral*> cargarDatosClientesOrdenados();
HashMap cargarDatosProductos();

//Funciones del menu
void agregarCliente(queue<clienteGeneral*> &lista);
queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &lista);
void llamarSiguienteCliente(queue<clienteGeneral*> &lista);
void agregarProducosABodega(HashMap listaDeProductos);

int main() {

    queue<clienteGeneral*> listaClientes = cargarDatosClientesOrdenados();
    HashMap listaDeProductos = cargarDatosProductos();

    menu(listaClientes,listaDeProductos);

    return 0;
}

void menu(queue<clienteGeneral *> listaDeClientes, HashMap listaProductos) {

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
                agregarProducosABodega(listaProductos);
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

void agregarProducosABodega(HashMap listaDeProductos) {

    string categoria, subcategoria, nombreProducto;
    float precio;
    int idProducto, cantEnStock;

    cout << "Ingrese la categoria del nuevo producto:" << endl;
    cin >> categoria;
    cout << "Ingrese la sub-categoria del nuevo producto:" << endl;
    cin >> subcategoria;
    cout << "Ingrese el nombre del nuevo producto:" << endl;
    cin >> nombreProducto;
    cout << "Ingrese el precio del nuevo producto:" << endl;
    cin >> precio;
    cout << "Ingrese el ID del nuevo producto:" << endl;
    cin >> idProducto;
    cout << "Ingrese la cantidad en stock del nuevo producto:" << endl;
    cin >> cantEnStock;

    Producto* nuevoProducto = new Producto(categoria,subcategoria,idProducto,nombreProducto,precio,cantEnStock);

    listaDeProductos.insertarProducto(nuevoProducto);
    cout << "Producto agregado correctamente a la bodega." << endl;

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
HashMap cargarDatosProductos(){

    //cargar productos al HashMap
    HashMap listaDeProductos;
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt"
    ifstream arch("D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt");
    string linea;

     if (arch.is_open()) {
         while (std::getline(arch, linea)) {
             stringstream ss(linea);
             string categoria, subcategoria, nombreProducto;
             float precio;
             int idProducto, cantEnStock;

             std::getline(ss, categoria, ',');
             std::getline(ss, subcategoria, ',');
             ss >> idProducto;
             ss.ignore();
             std::getline(ss, nombreProducto, ',');
             ss >> precio;
             ss.ignore();
             ss >> cantEnStock;

             Producto* producto = new Producto(categoria,subcategoria,idProducto,nombreProducto,precio,cantEnStock);
             listaDeProductos.insertarProducto(producto);
         }
        arch.close();
     }
     else {
        cout << "No se pudo abrir el archivo Productos.txt" << endl;
     }

    return listaDeProductos;

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
