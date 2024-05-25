#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../include/clienteGeneral.h"
#include "../include/clienteNormal.h"
#include "../include/clientePreferencial.h"
#include "../include/Producto.h"
#include "../include/HashMap.h"
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
queue<clienteGeneral*> agregarCliente(queue<clienteGeneral*> listaDeClientes);
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
                listaDeClientes = agregarCliente(listaDeClientes);
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
                cout << "Opcion no valida. Intentelo de nuevo." << endl;
        }
    } while (opcion != 0);
}

void generarBoleta(HashMap& listaProductos){

    //Generar el total de la compra segun el total de productos comprados
    string respuesta;
    do {
        string id;
        cout << "Ingrese ID del producto: ";
        cin >> id;
        int cant;
        Producto* producto = listaProductos.buscar(id);
        if (producto != nullptr) {
            cout << "Producto encontrado: " << producto->getNombreProducto() << endl;
            cout << "Precio unitario: $" << producto->getPrecio() << endl;
            cout << "Cantidad disponible en stock: " << producto->getCantEnStock() << endl;
            cout << "¿Cuantos desea comprar?" << endl;
            cout << "Cantidad: ";
            cin >> cant;
            if (cant <= producto->getCantEnStock()) {
                float precio = producto->getPrecio();

                cout << "El precio final es: "<< precio * cant << " $" << endl;
                cout << "¿Pagar? (Si/No): ";
                cin >> respuesta;
                transform(respuesta.begin(), respuesta.end(), respuesta.begin(),::tolower);

                if (respuesta == "si") {
                    cout << "Compra efectuada con exito" << endl;
                    producto->setCantEnStock(producto->getCantEnStock() - cant);

                    if (producto->getCantEnStock() == 0){
                        listaProductos.eliminarProducto(producto->getIdProducto());
                    }
                    //Actualizar la bodega
                    string nombreArch = "/workspaces/TallerEstructura2/src/data/Bodega.txt";
                    listaProductos.actualizarArchivo(nombreArch);

                }
                else if (respuesta == "no") {
                    cout << "Compra rechazada" << endl;
                }
                else {
                    cout << "Respuesta no valida." << endl;
                }
            }
            else {
                cout << "Ingrese una cantidad valida." << endl;
            }
        }
        else {
            cout << "Producto no encontrado con el ID proporcionado." << endl;
        }
        cout << "¿Desea agregar mas productos? (Si/No): ";
        cin >> respuesta;
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
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
            listaDeProductos.mostrarProductos();
            break;
        }
        case 2: {
            string categoria;
            cout << "Ingrese la categoria para filtrar: ";
            getline(cin >> ws, categoria);
            cout << "Productos en la categoria " << categoria << ":" << endl;
            listaDeProductos.mostrarProductosCategoria(categoria);
            break;
        }
        case 3: {
            string subcategoria;
            cout << "Ingrese la sub-categoria para filtrar: ";
            getline(cin >> ws, subcategoria);
            cout << "Productos en la sub-categoria " << subcategoria << ":" << endl;
            listaDeProductos.mostrarProductosSubCategoria(subcategoria);
            break;
        }
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intentelo de nuevo." << endl;
    }
}

void agregarProducosABodega(HashMap& listaDeProductos) {

    //Agregar productos a la bodega con cada dato solicitado
    string categoria, subcategoria, nombreProducto, idProducto;
    float precio;
    int cantEnStock;

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
    string nombreArch = "/workspaces/TallerEstructura2/src/data/Bodega.txt";
    listaDeProductos.actualizarArchivo(nombreArch);
    cout << "Producto agregado correctamente a la bodega." << endl;

}

queue<clienteGeneral*> agregarCliente(queue<clienteGeneral*> listaDeClientes) {
    

    //Agregar cliente segun su tipo a la fila
    string nombre;
    string tipoCliente;
    cout << "Ingrese el nombre del cliente: " << endl;
    cin >> nombre;

    cout << "Ingrese el tipo de cliente (Tercera edad, Discapacidad, Embarazada, Normal): " << endl;
    getline(cin >> ws, tipoCliente);

    transform(tipoCliente.begin(), tipoCliente.end(), tipoCliente.begin(), ::tolower);

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
        listaDeClientes = ordenarSegunPreferencia(listaDeClientes);

    } else {
        cout << "Tipo de cliente invalido. Intentelo de nuevo." << endl;
    }

    return listaDeClientes;

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

    ifstream archivo("/workspaces/TallerEstructura2/src/data/clientes.txt");
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
    ifstream arch("/workspaces/TallerEstructura2/src/data/Bodega.txt");
    string linea;

     if (arch.is_open()) {
         while (getline(arch, linea)) {
             stringstream ss(linea);
             string categoria, subcategoria, nombreProducto, idProducto;
             float precio;
             int cantEnStock;

             getline(ss, categoria, ',');
             getline(ss, subcategoria, ',');
             getline(ss, idProducto, ',');
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
    // Guardar datos de los clientes en un archivo temporal

    ofstream archivoTemp("/workspaces/TallerEstructura2/src/data/clientes_temp.txt");

    if (archivoTemp.is_open()) {
        // Copiar la cola original para no modificarla
        queue<clienteGeneral*> listaTemporal = listaClientes;

        while (!listaTemporal.empty()) {
            clienteGeneral* cliente = listaTemporal.front();
            archivoTemp << cliente->getNombre();

            clientePreferencial* clientePref = dynamic_cast<clientePreferencial*>(cliente);
            if (clientePref != nullptr) {
                archivoTemp << "," << clientePref->getTipoDeCliente();
            }

            archivoTemp << endl;
            listaTemporal.pop();
        }

        archivoTemp.close();
        cout << "Datos de clientes guardados temporalmente." << endl;

        // Eliminar el archivo original
        if (remove("/workspaces/TallerEstructura2/src/data/clientes.txt") != 0) {
            perror("Error al eliminar el archivo original.");
        } else {
            // Cambiar el nombre del archivo temporal al nombre del archivo original
            if (rename("/workspaces/TallerEstructura2/src/data/clientes_temp.txt", "/workspaces/TallerEstructura2/src/data/clientes.txt") != 0) {
                perror("Error al cambiar el nombre del archivo temporal.");
            } else {
                cout << "Datos de clientes guardados correctamente." << endl;
            }
        }
    } else {
        cout << "No se pudo abrir el archivo temporal para guardar los datos." << endl;
    }
}



