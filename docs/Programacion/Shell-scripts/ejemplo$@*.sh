#!/bin/bash

# Definimos un array
files=("archivo1.md" "archivo2.md" "archivo con espacios.md")

# Imprimir usando $@
echo "Usando \$@:"
for file in "$@"; do
  echo "Archivo: $file"
done

# Imprimir usando \$*
echo "Usando \$*:"
for file in $*; do
  echo "Archivo: $file"
done

