#!/bin/bash

# Define el porcentaje de archivos a ejecutar
PERCENTAGE=2

# Inicializa los contadores
success_count=0
failure_count=0

# Inicializa la lista de tableros fallidos
failed_boards=()

# Contador de iteraciones
iteration_count=0

# Obtener el número total de archivos en el directorio /tableros
total_files=$(ls ./tableros/* | wc -l)

# Calcular el número de archivos a ejecutar según el porcentaje
files_to_execute=$((total_files * PERCENTAGE / 100))

# Recorre todos los archivos en el directorio /tableros
for tablero in ./tableros/*; do
  # Incrementa el contador de iteraciones
  iteration_count=$((iteration_count + 1))

  # Solo ejecutar el script si la iteración actual es múltiplo del tamaño del paso calculado
  if (( iteration_count % (100 / PERCENTAGE) == 0 )); then
    output=$(./correr.sh "$tablero" 2>&1)

    # Verifica los mensajes de salida del programa sensor
    if echo "$output" | grep -q "El robot llego a su destino"; then
      success_count=$((success_count + 1))
    elif echo "$output" | grep -q "El robot no llego a su destino"; then
      failure_count=$((failure_count + 1))
      failed_boards+=("$tablero")
    else echo "No output from $tablero: $output"
    fi
  fi
done

# Muestra los resultados finales
echo "Resultados finales:"
echo "Éxitos: $success_count"
echo "Fallos: $failure_count"

# Muestra los tableros que fallaron
if [ ${#failed_boards[@]} -gt 0 ]; then
  echo "Tableros fallidos:"
  for board in "${failed_boards[@]}"; do
    echo "$board"
  done
fi
