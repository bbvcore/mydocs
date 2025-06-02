---
sidebar_position: 2
title: Sed
---
# Sed
Al igual que Tr permite modificar caracteres de un flujo de datos, aunque permite una mayor versatilidad que Tr al incorporar operaciones con REGEX.

## Sintaxis
```bash
sed [opciones] 'expr. regular' 'texto/fichero'
```
### Parámetros
**- s**: sustitución de un texto por otro *(importante el uso de la barra final)*.
```bash
echo "Ejemplo de sustitución" | sed 's/plo/plos/'
```
**- s/g**: sustitución global, después de la barra final se añade la g de global.
```bash
echo "Ejemplo de sustitución de caracteres" | sed 's/de/??/g'
```
**- i**: reemplaza en archivos
```bash
sed -i 's/a/x/g' fichero.txt
```
**- d**: eliminar líneas
```bash
echo -e 'una\ndos\ntres' | sed '/tres/d'
```
**- //**: expresiones regulares con mayor complejidad
```bash
echo 'abc1234' | sed 's/[0-3]*$//'
````