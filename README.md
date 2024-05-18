README
Integrantes:
Sebastián Vega Chepillo; 21.349.057-5; sebastian.vega03@alumnos.ucn.cl
Maximiliano Alfredo Pasten Nayem; 20.169.262-8; maximiliano.pasten@alumnos.ucn.cl

Sistema de Gestión de Ventas para Farmacia
Informacion sobre los Objetos
Durante el inicio del programa, se crean los siguientes objetos que están presentes en los archivos clientes y Bodega (ambos .txt):
Contenido de Bodega.txt:
Categoría: Medicamentos
    - Ibuprofeno, 5.99, 10
    - Paracetamol, 4.50, 10
    - Aspirina, 3.75, 10
    - Amoxicilina, 10.25, 10
    - Azitromicina, 15.50, 10
Categoría: Cuidado Personal
    - Pasta de dientes, 2.99, 10
    - Cepillo de dientes, 1.50, 10
    - Crema hidratante, 8.75, 10
    - Protector solar, 12.99, 10
Categoría: Primeros Auxilios
    - Vendaje adhesivo, 3.25, 10
    - Gasas esteriles, 2.50, 10
    - Alcohol isopropilico, 4.99, 10
    - Solucion de yodo, 5.75, 10
Categoría: Vitaminas y Suplementos
    - Centrum, 9.99, 10
    - One A Day, 8.50, 10
    - Calcio + Vitamina D, 7.25, 10
    - Calcio masticable, 6.99, 10
Categoría: Material de Curacion
    - Tijeras de curacion, 6.50, 10
    - Pinzas de diseccion, 8.99, 10
    - Algodon en rollo, 3.99, 10
    - Gasas quirurgicas, 4.25, 10

Contenido de clientes.txt:
Juan
María,Discapacidad
Pedro
Ana
Luis,Tercera edad
Carolina
David,Embarazada
Carlos
Elena,Tercera edad





Contenido de los Archivos
El proyecto se compone de varios archivos que cumplen funciones específicas:
main.cpp: Contiene el programa principal que controla la lógica del sistema y las funciones que se usarán al ejecutar el código.
Persona.cpp y Persona.h: Implementan y definen la clase Persona que representa a los individuos que asisten a los eventos.
Evento.cpp y Evento.h: Implementan y definen la clase Evento que representa los eventos organizados.
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
Agregar cliente, Llamar siguiente cliente, Productos en Bodega, Agregar Productos Bodega, Generar Boleta
3. Sigue las instrucciones proporcionadas por el programa para realizar las diferentes acciones y los resultados se guardarán en el .txt.

