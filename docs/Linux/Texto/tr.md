---
sidebar_position: 1
title: Tr
---
# Tr
Este comando permite la sustitución de determinados caracteres en un flujo de datos por otros. Básicamente se puede decir que sirve para una transformación de datos.

## Sintaxis
```
tr [opciones] 'entrada' 'salida'
```
<details>
<summary>
Modificadores interesantes
</summary>


**- s**: permite eliminar caracteres duplicados

```bash
tr -s ' ' # Elimina los espacios superiores a 1
```

**'a-z' 'A-Z'**: permite pasar de minúsculas a mayúsculas
```bash
echo "A mayúsculas todo el texto" | tr 'a-z' 'A-Z'
```

**- d**: permite eliminar ciertos caracteres
```bash
echo "abcd123x45Yz" | tr -d 'a-z'
```
**[a] [b]**: permite sustituir un conjunto de caracteres por otros
```bash
echo "Esto es un ejemplo" | tr 'e' '3'
```
</details>