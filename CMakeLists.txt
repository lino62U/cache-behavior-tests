# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(MatrixMultiplication)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 11)

# Incluir directorios de cabeceras
include_directories(sources)

# Añadir los archivos fuente
set(SOURCES
    sources/main.cpp
    sources/matrix_utils.cpp
    sources/row_column.cpp
)

# Crear ejecutable para la multiplicación de matrices
add_executable(matrix_mult ${SOURCES})

# Crear ejecutable para la multiplicación por filas y columnas
add_executable(main_row_column sources/main_row_column.cpp sources/row_column.cpp sources/matrix_utils.cpp)

# Directorio de salida de binarios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
