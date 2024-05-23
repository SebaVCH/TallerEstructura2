#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <cctype>
#include "../include/clienteGeneral.h"
#include "../include/clienteNormal.h"
#include "../include/clientePreferencial.h"
#include "../include/Producto.h"
#include "../include/HashMap.h"
// g++ src/src/*.cpp -o a


using namespace std;

//Menu
void menu(queue<clienteGeneral *> listaClientes, HashMap& listaProductos);

//Cargar Datos y Guardar datos
queue<clienteGeneral*> cargarDatosClientesOrdenados();
HashMap cargarDatosProductos();
void guardarDatosClientes(queue<clienteGeneral*>& listaClientes);

//Ordenar Datos
queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &lista);

//Funciones del menu
void agregarCliente(queue<clienteGeneral*> &listaDeClientes);
void llamarSiguienteCliente(queue<clienteGeneral*> &listaDeClientes, HashMap &listaDeProductos);
void agregarProducosABodega(HashMap &listaDeProductos);
void mostrarProductosBodega(HashMap &listaDeProductos);
void generarBoleta(HashMap &listaProductos);


int main() {

    queue<clienteGeneral*> listaClientes = cargarDatosClientesOrdenados();
    HashMap listaDeProductos = cargarDatosProductos();

    menu(listaClientes,listaDeProductos);

    return 0;
}

void menu(queue<clienteGeneral *> listaDeClientes, HashMap& listaProductos) {


    //Menu para seleccionar la opcion que se desea realizar
    int opcion;
    do {
        cout << "" << endl;
        cout << "Seleccione una opcion:" << endl;
        cout << "1. Agregar cliente a la fila" << endl;
        cout << "2. Atender al cliente" << endl;
        cout << "3. Mostrar productos en bodega" << endl;
        cout << "4. Agregar productos a la bodega" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarCliente(listaDeClientes);
                cout<< endl;
                break;
            case 2:
                llamarSiguienteCliente(listaDeClientes, listaProductos);
                cout<< endl;
                break;
            case 3:
                mostrarProductosBodega(listaProductos);
                cout<< endl;
                break;
            case 4:
                agregarProducosABodega(listaProductos);
                cout<< endl;

                break;
            case 0:
                cout << "Saliendo..." << endl;

                //Vaciar memoria de clientes y del hashmap
                while (!listaDeClientes.empty()) {
                    delete listaDeClientes.front();
                    listaDeClientes.pop();
                }
                listaProductos.limpiarHashMap();
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 0);
}

void generarBoleta(HashMap& listaProductos){

    //Generar el total de la compra segun el total de productos comprados
    string respuesta;
    do {
        int id;
        cout << "Ingrese ID del producto: ";
        cin >> id;
        int cant;
        Producto* producto = listaProductos.buscar(id);
        if (producto != nullptr) {
            cout << "Producto encontrado: " << producto->getNombreProducto() << endl;
            cout << "Precio unitario: $" << producto->getPrecio() << endl;
            cout << "Cantidad disponible en stock: " << producto->getCantEnStock() << endl;
            cout << "¿Cuántos desea comprar?" << endl;
            cout << "Cantidad: ";
            cin >> cant;
            if (cant <= producto->getCantEnStock()) {
                float precio = producto->getPrecio();

                cout << "El precio final es: "<< precio * cant << " $" << endl;
                cout << "¿Pagar? (Si/No): ";
                cin >> respuesta;
                transform(respuesta.begin(), respuesta.end(), respuesta.begin(), [](unsigned char c){ return tolower(c); });

                if (respuesta == "si") {
                    cout << "Compra efectuada con éxito" << endl;
                    producto->setCantEnStock(producto->getCantEnStock() - cant);
                    string nombreArch = "ruta/del/archivo/Bodega.txt";
                    listaProductos.actualizarArchivo(nombreArch);
                }
                else if (respuesta == "no") {
                    cout << "Compra rechazada" << endl;
                }
                else {
                    cout << "Respuesta no válida." << endl;
                }
            }
            else {
                cout << "Ingrese una cantidad válida." << endl;
            }
        }
        else {
            cout << "Producto no encontrado con el ID proporcionado." << endl;
        }
        cout << "¿Desea agregar más productos? (Si/No): ";
        cin >> respuesta;
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), [](unsigned char c){ return tolower(c); });
    } while (respuesta == "si");
}

void mostrarProductosBodega(HashMap& listaDeProductos) {

    //Mostrar los productos en bodega segun el filtro que uno desee
    int opcion;
    cout << "Indique la opcion que desea:" << endl;
    cout << "1) Ver todos los productos." << endl;
    cout << "2) Filtrar por categoria." << endl;
    cout << "3) Filtrar por sub-categoria." << endl;
    cout << "0) Salir." << endl;
    cout <<  "Opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: {
            cout << "Todos los productos en la bodega:" << endl;
            for (int i = 0; i < listaDeProductos.obtenerCantElementos(); ++i) {
                Producto* producto = listaDeProductos.buscar(i);
                if (producto != nullptr) {
                    cout << "ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombreProducto() << endl;
                }
            }
            break;
        }
        case 2: {
            string categoria;
            cout << "Ingrese la categoría para filtrar: ";
            cin >> categoria;
            cout << "Productos en la categoría " << categoria << ":" << endl;
            for (int i = 0; i < listaDeProductos.obtenerCantElementos(); ++i) {
                Producto* producto = listaDeProductos.buscar(i);
                if (producto != nullptr && producto->getCategoria() == categoria) {
                    cout << "ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombreProducto() << endl;
                }
            }
            break;
        }
        case 3: {
            string subcategoria;
            cout << "Ingrese la sub-categoría para filtrar: ";
            cin >> subcategoria;
            cout << "Productos en la sub-categoría " << subcategoria << ":" << endl;
            for (int i = 0; i < listaDeProductos.obtenerCantElementos(); ++i) {
                Producto* producto = listaDeProductos.buscar(i);
                if (producto != nullptr && producto->getSubcategoria() == subcategoria) {
                    cout << "ID: " << producto->getIdProducto() << ", Nombre: " << producto->getNombreProducto() << endl;
                }
            }
            break;
        }
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
    }
}

void agregarProducosABodega(HashMap& listaDeProductos) {

    //Agregar productos a la bodega con cada dato solicitado
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
    string nombreArch = "ruta/del/archivo/Bodega.txt";
    listaDeProductos.actualizarArchivo(nombreArch);
    cout << "Producto agregado correctamente a la bodega." << endl;

}

void agregarCliente(queue<clienteGeneral*> &listaDeClientes) {

    //Agregar cliente a la fila
    string nombre;
    string tipoCliente;
    cout << "Ingrese el nombre del cliente: ";
    cin >> nombre;

    cout << "Ingrese el tipo de cliente (Tercera edad, Discapacidad, Embarazada, Normal): ";
    cin >> tipoCliente;

    transform(tipoCliente.begin(), tipoCliente.end(), tipoCliente.begin(), [](unsigned char c){ return tolower(c); });

    if (tipoCliente == "tercera edad" || tipoCliente == "discapacidad" || tipoCliente == "embarazada" || tipoCliente == "normal") {
        if (tipoCliente == "normal") {
            listaDeClientes.push(new clienteNormal(nombre));
        } 
        else if(tipoCliente =="embarazada"){
            listaDeClientes.push(new clientePreferencial(nombre, "Embarazada"));
        }
        else if(tipoCliente =="discapacidad"){
            listaDeClientes.push(new clientePreferencial(nombre, "Discapacidad"));
        }
        else if(tipoCliente =="tercera edad"){
            listaDeClientes.push(new clientePreferencial(nombre, "Tercera edad"));
        }
        
        cout << "Cliente agregado correctamente a la cola." << endl;

        //Ordenar para mantener la preferencia
        ordenarSegunPreferencia(listaDeClientes);
        guardarDatosClientes(listaDeClientes);
    } else {
        cout << "Tipo de cliente invalido. Intentelo de nuevo." << endl;
    }

    

}

void llamarSiguienteCliente(queue<clienteGeneral*> &listaDeClientes ,HashMap &listaDeProductos ) {
    //Llamar al siguiente cliente y atenderlo
    if (!listaDeClientes.empty()) {
        cout << "Cliente llamado: " << listaDeClientes.front()->getNombre() << endl;
        generarBoleta(listaDeProductos);
        delete listaDeClientes.front();
        listaDeClientes.pop();
    } else {
        cout << "No hay clientes en espera." << endl;
    }
    guardarDatosClientes(listaDeClientes);
}

queue<clienteGeneral*> cargarDatosClientesOrdenados() {

    //Cargar datos de los clientes y asignarles el numero de atencion

    queue<clienteGeneral*> lista;
    queue<clienteGeneral*> listaMostrar;
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt"

    ifstream archivo("D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt");
    string linea;
    int numeroAtencion = 1;
    cout << "Lista de clientes y numero de atencion: " << endl;

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
        listaMostrar = lista;
        while (!listaMostrar.empty()) {
            clienteGeneral* cliente = listaMostrar.front();
            cout << "Cliente: " << cliente->getNombre() << ", Numero de cliente: " << numeroAtencion++ << endl;
            listaMostrar.pop();
        }
        cout << "" << endl;

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo clientes.txt" << endl;
    }

    //Ordenar luego de agregar los datos
    return ordenarSegunPreferencia(lista);

}

HashMap cargarDatosProductos(){

    //Cargar productos al HashMap
    HashMap listaDeProductos;
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\Bodega.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\Bodega.txt"
    ifstream arch("D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\Bodega.txt");
    string linea;

     if (arch.is_open()) {
         while (getline(arch, linea)) {
             stringstream ss(linea);
             string categoria, subcategoria, nombreProducto;
             float precio;
             int idProducto, cantEnStock;

             getline(ss, categoria, ',');
             getline(ss, subcategoria, ',');
             ss >> idProducto;
             ss.ignore();
             getline(ss, nombreProducto, ',');
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

queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &listaDeClientes) {

    //Numero de atencion

    int numeroAtencion = 1;

    //Ordenar la fila por orden preferencial y reasignar el numero de atencion
    queue<clienteGeneral*> terceraEdad;
    queue<clienteGeneral*> discapacidad;
    queue<clienteGeneral*> embarazada;
    queue<clienteGeneral*> normal;

    queue<clienteGeneral*> listaOrdenada;
    queue<clienteGeneral*> listaMostrar;

    while (!listaDeClientes.empty()) {
        clienteGeneral* cliente = listaDeClientes.front();
        listaDeClientes.pop();

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
        listaOrdenada.push(terceraEdad.front());
        terceraEdad.pop();
    }
    while (!discapacidad.empty()) {
        listaOrdenada.push(discapacidad.front());
        discapacidad.pop();
    }
    while (!embarazada.empty()) {
        listaOrdenada.push(embarazada.front());
        embarazada.pop();
    }
    while (!normal.empty()) {
        listaOrdenada.push(normal.front());
        normal.pop();
    }


    listaMostrar = listaOrdenada;
    cout << "Lista de clientes reordenada y su respectivo numero de atencion: " << endl;
    while (!listaMostrar.empty()) {
        clienteGeneral* cliente = listaMostrar.front();
        cout << "Cliente: " << cliente->getNombre() << ", Numero de cliente: " << numeroAtencion++ << endl;
        listaMostrar.pop();
    }


    guardarDatosClientes(listaOrdenada);
    return listaOrdenada;
}

void guardarDatosClientes(queue<clienteGeneral*> &listaClientes) {

    //Guardar datos de los clientes
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\Bodega.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes_guardados.txt"

    
    ofstream archivo("D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt");

    if (archivo.is_open()) {
        while (!listaClientes.empty()) {
            clienteGeneral* cliente = listaClientes.front();
            archivo << cliente->getNombre();

            clientePreferencial* clientePref = dynamic_cast<clientePreferencial*>(cliente);
            if (clientePref != nullptr) {
                archivo << "," << clientePref->getTipoDeCliente();
            }

            archivo << endl;
            listaClientes.pop();
        }

        archivo.close();
        cout << "Datos de clientes guardados correctamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo clientes.txt para guardar los datos." << endl;
    }
}


