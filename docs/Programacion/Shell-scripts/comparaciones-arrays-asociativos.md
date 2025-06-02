---
sidebar_position: 1
title: Comparaciones While optimizado
---

# Comparaciones While
En este caso la comparación va a hacer uso de los arrays asociativos. Para ello se utilizará **declare** en combinación con el parámetro **-A**, este comando solo funciona dentro de scripts.

:::tip[Generación de arrays asociativos]
- Declare: permite definir variables con propiedades especiales.
:::

<details>
<summary>
Lista de parámetros del comando
</summary>
- A: creación de arrays asociativos
- a: creación de array indexado
- i: enteros
- r: lectura
- x: exporta la variable
</details>

## Arrays asociativos
Accediendo al valor alojado en un array asociativo mediante el nombre del campo.
```bash
declare -A discos
discos[metallica]="Master Of Puppets"
discos[korn]="KoRn"
echo ${discos[metallica]}
```
### Iterando arrays asociativos
#### Obtener solo valores
```bash
for i in "{$discos[@]}"; do
    echo "$i => ${discos[$i]}"
done
```
#### Obtener solo claves
```bash
for i in "{!$discos[@]}"; do
    echo "$i"
done
```

## Arrays numéricos
```bash
declare -a numbers=(0 1 2 3 4 5)
echo "${numbers[@]}" # Todo el array
echo "${numbers[2]}" # Contenido del indice 2
echo "${#numbers[@]}" # Tamaño del array
```

## Script comparativo con array asociativo
```bash
#!/bin/bash
declare -A file_ips
while read -r ip; do # -r evita caracteres especiales
    file_ips["$ip"]=1 # Añade de valor al indice 
done < ip_list.txt


```