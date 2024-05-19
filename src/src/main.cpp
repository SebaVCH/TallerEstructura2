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

//Cargar Datos
queue<clienteGeneral*> cargarDatosClientesOrdenados();
HashMap cargarDatosProductos();

//Ordenar Datos
queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &lista);

//Funciones del menu
void agregarCliente(queue<clienteGeneral*> &lista);
void llamarSiguienteCliente(queue<clienteGeneral*> &lista, HashMap &listaDeProductos);
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
        cout << "Seleccione una opcion:" << endl;
        cout << "1. Agregar cliente a la fila" << endl;
        cout << "2. Atender al cliente" << endl;
        cout << "3. Mostrar productos en bodega" << endl;
        cout << "4. Agregar productos a la bodega" << endl;
        //cout << "5. Generar boleta" << endl;
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
//            case 5:
//                //Se pregunta por el ID de un producta que se desee vender, luego se revisa si esta disponible
//                //Luego se imprime por pantalla algo como una boleta el valor y todo
//
//                //Se restan los elementos de Bodega //hasta aca
//                generarBoleta(listaProductos);
//                cout<< endl;
//                break;
            case 0:
                cout << "Saliendo..." << endl;
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
        string idABuscar;
        cout << "Ingrese ID del producto: ";
        cin >> idABuscar;
        int id = stoi(idABuscar);
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
                    // ahora se modifica el stock
                    producto->setCantEnStock(producto->getCantEnStock() - cant);

                    // actualización del archivo
                    string nombreArch = "ruta/del/archivo/Bodega.txt"; // Cambia la ruta a la correcta
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
    string opcion;
    cout << "Indique la opcion que desea:" << endl;
    cout << "1) Ver todos los productos." << endl;
    cout << "2) Filtrar por categoria." << endl;
    cout << "3) Filtrar por sub-categoria." << endl;
    cout << "0) Salir." << endl;
    cout <<  "Opcion: ";
    cin >> opcion;

    switch (stoi(opcion)) {
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

void llamarSiguienteCliente(queue<clienteGeneral*> &lista ,HashMap &listaDeProductos ) {
    //Llamar al siguiente cliente y atenderlo
    if (!lista.empty()) {
        cout << "Cliente llamado: " << lista.front()->getNombre() << endl;
        generarBoleta(listaDeProductos);
        delete lista.front();
        lista.pop();
    } else {
        cout << "No hay clientes en espera." << endl;
    }
}

queue<clienteGeneral*> cargarDatosClientesOrdenados() {

    //Cargar datos de los clientes y asignarles el numero de atencion

    queue<clienteGeneral*> lista;
    queue<clienteGeneral*> listaMostrar;
    //"D:\\Programas\\c++ workspace visual\\taller2\\TallerEstructura2\\src\\data\\clientes.txt"
    //"D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt"

    ifstream archivo("D:\\CLionProjects\\TallerEstructura2\\src\\data\\clientes.txt");
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
    ifstream arch("D:\\CLionProjects\\TallerEstructura2\\src\\data\\Bodega.txt");
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

queue<clienteGeneral *> ordenarSegunPreferencia(queue<clienteGeneral *> &lista) {

    //Numero de atencion

    int numeroAtencion = 1;

    //Ordenar la fila por orden preferencial y reasignar el numero de atencion
    queue<clienteGeneral*> terceraEdad;
    queue<clienteGeneral*> discapacidad;
    queue<clienteGeneral*> embarazada;
    queue<clienteGeneral*> normal;

    queue<clienteGeneral*> listaOrdenada;
    queue<clienteGeneral*> listaMostrar;

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

    return listaOrdenada;
}
