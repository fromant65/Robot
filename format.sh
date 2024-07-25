#!/bin/bash

# Directorio base
base_dir="."

# Encuentra todos los archivos .c y .h y ejecuta el comando indent en cada uno
find "$base_dir" -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d '' file; do
    indent -kr -brf -i2 -l80 -nut "$file"
    if [ $? -eq 0 ]; then
        echo "Processed $file successfully"
    else
        echo "Error processing $file" >&2
    fi
done
