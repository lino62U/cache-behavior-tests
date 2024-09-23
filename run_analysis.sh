#!/bin/bash

# Crear el directorio 'result' si no existe
mkdir -p result

# Crear el entorno virtual 'venv' si no existe
if [ ! -d "venv" ]; then
    echo "Creating virtual environment..."
    python3 -m venv venv
    echo "Virtual environment created."
fi

# Activar el entorno virtual
source venv/bin/activate

# Verificar si pandas y matplotlib están instalados en el entorno virtual
if ! pip show pandas &> /dev/null || ! pip show matplotlib &> /dev/null; then
    echo "Installing required packages (pandas, matplotlib)..."
    pip install --upgrade pip
    pip install pandas matplotlib
    echo "Packages installed."
else
    echo "Required packages already installed. Skipping installation."
fi

# Ejecutar el script Python
echo "Running Python script..."
python plot_comparison.py

# Desactivar el entorno virtual
deactivate

# Imprimir mensaje de éxito
echo "Graph generated and saved in 'result/comparison_times.png'."
