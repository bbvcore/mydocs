---
title: Calculadora con select/case
---

# Calculadora
Calculadora realizada con seletc/case en shellscript.

```bash
#!/bin/bash

# Mostrar un menú con select
echo "Seleccione una operación:"
select operacion in "Sumar" "Restar" "Salir"; do
    case $operacion in
        "Sumar")
            # Solicitar los dos números para sumar
            read -p "Ingrese el primer número: " num1
            read -p "Ingrese el segundo número: " num2
            resultado=$((num1 + num2))
            echo "El resultado de la suma es: $resultado"
            ;;
        "Restar")
            # Solicitar los dos números para restar
            read -p "Ingrese el primer número: " num1
            read -p "Ingrese el segundo número: " num2
            resultado=$((num1 - num2))
            echo "El resultado de la resta es: $resultado"
            ;;
        "Salir")
            echo "Saliendo..."
            break
            ;;
        *)
            echo "Opción no válida"
            ;;
    esac
done
```

