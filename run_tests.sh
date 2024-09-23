#!/bin/bash

# Directorios
BUILD_DIR="build"
RESULT_DIR="result"

# Archivos de resultados
TIME_FILE="${RESULT_DIR}/times.txt"

# Crear directorios si no existen
mkdir -p $BUILD_DIR $RESULT_DIR

# Configurar y compilar el proyecto con CMake
cd $BUILD_DIR
if [ ! -f "Makefile" ]; then
    cmake ..
    if [ $? -ne 0 ]; then
        echo "Error: Fallo al ejecutar cmake"
        exit 1
    fi
fi

make
if [ $? -ne 0 ]; then
    echo "Error: Fallo al ejecutar make"
    exit 1
fi

cd ..

# Limpiar archivos anteriores
> "$TIME_FILE"

# Tamaños de matrices para probar tiempos
MATRIX_SIZES=(500 1000)

# Probar tiempos
echo -e "\nProbando tiempos de los algoritmos"
for size in "${MATRIX_SIZES[@]}"
do
    echo "Probando tamaño de matriz: ${size}x${size}" | tee -a "$TIME_FILE"
    { time ./build/matrix_mult $size ; } 2>> "$TIME_FILE"
    echo "-----------------------------------" >> "$TIME_FILE"
done

# Tamaños de matrices para probar Cachegrind
CACHE_SIZES=(500)
echo -e "\nEjecutando Cachegrind"
for size in "${CACHE_SIZES[@]}"
do
    echo "Ejecutando Cachegrind para tamaño de matriz: ${size}x${size}"
    # Genera el archivo de salida de cachegrind con el formato cachegrind.out.<pid>
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