README
Integrantes:
Sebastián Vega Chepillo; 21.349.057-5; sebastian.vega03@alumnos.ucn.cl
Maximiliano Alfredo Pasten Nayem; 20.169.262-8; maximiliano.pasten@alumnos.ucn.cl

Sistema de Gestión de Ventas para Farmacia

Informacion sobre los objetos creados al iniciar el programa

Durante el inicio del programa, se crean los siguientes objetos que están presentes en los archivos clientes y Bodega (ambos .txt):
Contenido de Bodega.txt:
Categoria: Cuidado Personal:
- {subcategoria: Higiene Oral, idProducto: 006, nombreProducto: Pasta de dientes, precio: 2.99, cantEnStock: 10}
- {subcategoria: Higiene Oral, idProducto: 007, nombreProducto: Cepillo de dientes, precio: 1.50, cantEnStock: 10}
- {subcategoria: Cuidado de la Piel, idProducto: 008, nombreProducto: Crema hidratante, precio: 8.75, cantEnStock: 10}
- {subcategoria: Cuidado de la Piel, idProducto: 009, nombreProducto: Protector solar, precio: 12.99, cantEnStock: 10}

Categoria: Material de Curacion:
- {subcategoria: Instrumentos quirurgicos, idProducto: 018, nombreProducto: Tijeras de curacion, precio: 6.50, cantEnStock: 10}
- {subcategoria: Instrumentos quirurgicos, idProducto: 019, nombreProducto: Pinzas de diseccion, precio: 8.99, cantEnStock: 10}
- {subcategoria: Gasas y algodon, idProducto: 020, nombreProducto: Algodon en rollo, precio: 3.99, cantEnStock: 10}
- {subcategoria: Gasas y algodon, idProducto: 021, nombreProducto: Gasas quirurgicas, precio: 4.25, cantEnStock: 10}

Categoria: Medicamentos:
- {subcategoria: Analgesicos, idProducto: 001, nombreProducto: Ibuprofeno, precio: 5.99, cantEnStock: 10}
- {subcategoria: Analgesicos, idProducto: 002, nombreProducto: Paracetamol, precio: 4.50, cantEnStock: 10}
- {subcategoria: Analgesicos, idProducto: 003, nombreProducto: Aspirina, precio: 3.75, cantEnStock: 10}
- {subcategoria: Antibioticos, idProducto: 004, nombreProducto: Amoxicilina, precio: 10.25, cantEnStock: 10}
- {subcategoria: Antibioticos, idProducto: 005, nombreProducto: Azitromicina, precio: 15.50, cantEnStock: 10}

Categoria: Primeros Auxilios:
- {subcategoria: Vendajes y apositos, idProducto: 010, nombreProducto: Vendaje adhesivo, precio: 3.25, cantEnStock: 10}
- {subcategoria: Vendajes y apositos, idProducto: 011, nombreProducto: Gasas esteriles, precio: 2.50, cantEnStock: 10}
- {subcategoria: Desinfectantes, idProducto: 012, nombreProducto: Alcohol isopropilico, precio: 4.99, cantEnStock: 10}
- {subcategoria: Desinfectantes, idProducto: 013, nombreProducto: Solucion de yodo, precio: 5.75, cantEnStock: 10}

Categoria: Vitaminas y Suplementos:
- {subcategoria: Multivitaminicos, idProducto: 014, nombreProducto: Centrum, precio: 9.99, cantEnStock: 10}
- {subcategoria: Multivitaminicos, idProducto: 015, nombreProducto: One A Day, precio: 8.50, cantEnStock: 10}
- {subcategoria: Suplementos de Calcio, idProducto: 016, nombreProducto: Calcio + Vitamina D, precio: 7.25, cantEnStock: 10}
- {subcategoria: Suplementos de Calcio, idProducto: 017, nombreProducto: Calcio masticable, precio: 6.99, cantEnStock: 10}

Contenido de clientes.txt:
{Nombre: Ana}
{Nombre: Carolina}
{Nombre: Carlos}
{Nombre: David, Tipo: Embarazada}
{Nombre: Elena, Tipo: Tercera edad}
{Nombre: Juan}
{Nombre: Luis, Tipo: Tercera edad}
{Nombre: María, Tipo: Discapacidad}
{Nombre: Pedro}

Contenido de los Archivos
El proyecto se compone de varios archivos que cumplen funciones específicas:
main.cpp: Contiene el programa principal que controla la lógica del sistema y las funciones que se usarán al ejecutar el código.
clienteGeneral (.cpp y .h): Sirve como una clase base para las clases clienteNormal y clientePreferencial, proporcionan una estructura básica común que comparten estas clases.
clienteNormal(.cpp y .h): Representa un cliente común sin ninguna preferencia especial y hereda de clienteGeneral.
clientePreferencial(.cpp y .h): Representa un cliente con un tipo de preferencia específico, que afecta su experiencia de compra, especificamente su atención en la caja.
Producto(.cpp y .h): Define la estructura de los productos que se venden en la tienda, almacenando información como la categoria, sub-categoria, nombre, precio, etc.
Hashmap(.cpp y .h): Es una clase diseñada para almacenar y gestionar los productos, donde se utilizan métodos para agregar, buscar, eliminar productos, entre otros.

clientes.txt: Archivo de texto que contiene la información de los clientes.
Bodega.txt: Archivo de texto que contiene la información de los productos en bodega.

Instrucciones para Compilar y Ejecutar
Para compilar y ejecutar el programa, sigue estos pasos:
 
1. Abre la terminal en el directorio del proyecto.
2. Compila el programa utilizando el siguiente comando:
g++ src/src/*.cpp -o taller
3. Ejecuta el programa con el siguiente comando:
./taller 
Instrucciones de Uso
1. Ejecuta el programa.
2. Se mostrará un menú de opciones, donde se podrá elegir entre varias opciones
Agregar cliente, Llamar siguiente cliente, Productos en Bodega, Agregar Productos Bodega
3. Sigue las instrucciones proporcionadas por el programa para realizar las diferentes acciones y los resultados se guardarán en el .txt.

