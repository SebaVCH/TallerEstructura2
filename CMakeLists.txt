cmake_minimum_required(VERSION 3.28)
project(TallerEstructura2)

set(CMAKE_CXX_STANDARD 26)

add_executable(TallerEstructura2 src/src/main.cpp
        src/src/Producto.cpp
        src/include/Producto.h
        src/src/clienteGeneral.cpp
        src/include/clienteGeneral.h
        src/src/clienteNormal.cpp
        src/include/clienteNormal.h
        src/src/clientePreferencial.cpp
        src/include/clientePreferencial.h
        src/src/HashMap.cpp
        src/include/HashMap.h)
