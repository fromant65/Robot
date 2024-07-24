#!/bin/bash

# Inicializa los contadores
success_count=0
failure_count=0

# Recorre todos los archivos en el directorio /tableros
for tablero in ./tableros/*; do
  output=$(./correr.sh "$tablero" 2>&1)

  # Verifica los mensajes de salida del programa sensor
  if echo "$output" | grep -q "El robot llego a su destino"; then
    success_count=$((success_count + 1))
  elif echo "$output" | grep -q "El robot no llego a su destino"; then
    failure_count=$((failure_count + 1))
    echo "Fallo $tablero: $output"
  fi
done

# Muestra los resultados finales
echo "Resultados finales:"
echo "Éxitos: $success_count"
echo "Fallos: $failure_count"
