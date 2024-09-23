#!/bin/bash

# Directorios
BUILD_DIR="build"
RESULT_DIR="result"

# Archivos de resultados
TIME_FILE="${RESULT_DIR}/times.csv"
TIME_FILE_RC="${RESULT_DIR}/times_row_column.csv"

# Crear directorios si no existen
mkdir -p $BUILD_DIR $RESULT_DIR

##############################
# COMPILACIÓN DEL PROYECTO
##############################
cd $BUILD_DIR
echo -e "\n=============================="
echo "Configurando y compilando el proyecto con CMake"
echo "=============================="

# Configurar el proyecto con CMake
if [ ! -f "Makefile" ]; then
    cmake ..
    if [ $? -ne 0 ]; then
        echo "Error: Fallo al ejecutar cmake"
        exit 1
    fi
fi

# Compilar el proyecto con make
make
if [ $? -ne 0 ]; then
    echo "Error: Fallo al ejecutar make"
    exit 1
fi

cd ..
echo -e "Compilación finalizada con éxito."
echo -e "==============================\n"

##############################
# PRUEBAS Y EJECUCIONES
##############################

# Borrar el archivo CSV y escribir el encabezado
echo "Tamaño,Clásica,Bloques" > $TIME_FILE
echo "Tamaño,Time Row-Major,Time Column-Major" > $TIME_FILE_RC

# Tamaños de matrices para probar tiempos
MATRIX_SIZES=(100 500 1000 5000 10000)

# Probar tiempos de multiplicación por filas y columnas
echo -e "\nProbando comparación de tiempos de multiplicación por filas y columnas"
for size in "${MATRIX_SIZES[@]}"
do
    echo "Probando tamaño de matriz: ${size}x${size}"
    ./build/main_row_column $size
    echo "-----------------------------------"
done

MATRIX_SIZES=(100 500 1000 1500 2000)
# Probar tiempos de multiplicación clásica y por bloques con opción de guardar
echo -e "\nProbando comparación de tiempos de multiplicación clásica y por bloques"
for size in "${MATRIX_SIZES[@]}"
do
    echo "Probando tamaño de matriz: ${size}x${size}"
    ./build/matrix_mult $size --save
    echo "-----------------------------------"
done

# Tamaños de matrices para probar Cachegrind
CACHE_SIZES=(100 500 1000 1500 2000)
echo -e "\nEjecutando Cachegrind"
for size in "${CACHE_SIZES[@]}"
do
    echo "Ejecutando Cachegrind para tamaño de matriz: ${size}x${size}"
    valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes --cachegrind-out-file="$RESULT_DIR/cachegrind_${size}.out" ./build/matrix_mult $size
    echo "Archivo Cachegrind generado: $RESULT_DIR/cachegrind_${size}.out"
    echo "-----------------------------------"
done

# Mensaje final destacado
echo -e "\n===================================\n"
echo "Pruebas completadas. Resultados guardados en la carpeta 'result'."
echo -e "\nPara visualizar los resultados de Cachegrind, usa el siguiente comando:"
for size in "${CACHE_SIZES[@]}"
do
    echo "  kcachegrind $RESULT_DIR/cachegrind_${size}.out"
done
echo -e "\n===================================\n"