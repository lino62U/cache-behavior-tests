# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(MatrixMultiplication)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)

# Añadir los archivos fuente
set(SOURCES
    sources/main.cpp
    sources/matrix_utils.cpp
)

# Incluir directorios de cabeceras
include_directories(sources)

# Añadir ejecutable
add_executable(matrix_mult ${SOURCES})

# Directorio de salida de binarios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)