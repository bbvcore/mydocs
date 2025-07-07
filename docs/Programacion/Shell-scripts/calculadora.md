
---
title: Script para una calculadora
---

# Script para una calculadora
```bash
#!/bin/bash

# Mostrar menú de opciones
echo "Seleccione la operación:"
echo "1. Sumar"
echo "2. Restar"
echo "3. Salir"
read -p "Ingrese el número de la operación: " operacion

# Comprobamos que la opción ingresada sea válida
if [[ ! "$operacion" =~ ^[1-3]$ ]]; then
    echo "Opción no válida"
    exit 1
fi

# Si la opción es válida, pedimos los números
read -p "Ingrese el primer número: " num1
read -p "Ingrese el segundo número: " num2

# Realizamos la operación seleccionada
case $operacion in
    1) 
        resultado=$((num1 + num2))
        echo "El resultado de la suma es: $resultado"
        ;;
    2)
        resultado=$((num1 - num2))
        echo "El resultado de la resta es: $resultado"
        ;;
    3)
        echo "Saliendo..."
        exit 0
        ;;
    *)
        echo "Opción no válida"
        exit 1
        ;;
esac
```
