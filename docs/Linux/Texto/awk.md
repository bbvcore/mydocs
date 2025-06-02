---
sidebar_position: 3
title: AWK
---
# AWK
Permite realizar la manipulación de ficheros de forma compleja mediante la manipulación de patrones, es considerado un lenguaje de programación de proposito específico para texto estructurado en campos.

## Imprimir datos
### De una columna particular
Para imprimir datos de una columna particular se utiliza el simbolo del dolar más el número que hace de indice de la posición de dicha columna en el encabezado obtenido o analizado.

#### Por defecto el delimitador es un espacio en blanco
```
awk `{print:$1}' fichero.txt
```
#### Especificar otro delimitador
```
awk -F ',' '{print $2}' fichero.csv
```
#### Cumplir una condición 
```
awk '$2>5' notas.txt
```
#### Contar líneas
```
awk 'END {print NR}' fichero.txt
```
:::tip[Parámetros]
- **END**: *acciones después de procesar todas las líneas, para operaciones acumulativas*.
- **NR**: *número de líneas leídas*.
:::

Una vez finalizada la ejecución se procede a mostrar el **número de líneas**. Es similar al resultado obtenido con el comando **wc**.

```
cat fichero.txt | wc -l
```

#### Sumar columnas
```
awk '{suma += $2} END {print suma}' fichero.txt
```
Se realiza la suma acumulativa de los valores del campo 2 y una vez finalizado se muestra el resultado acumulado en la variable suma.

## Función GSUB
La función **GSUB** en **AWK** cumple la función de buscar y reemplazar similar a los editores de texto.  Su sintaxis básica es la siguiente.

```bash
gsub(/LoBuscado/, <"LoQueAñadir">, <"DondeBuscarlo">)
```
Si no se utiliza donde buscar se usa por defecto el **nombre del script** en *ejecución* ya que usa el valor devuelto por **$0**.

### Casos prácticos GSUB
#### Eliminar paréntesis
```
gsub(/[()]/, "", $5)
```
- El primer argumento se utiliza para buscar cualquier paréntesis. Las barras son *por defecto* y los *corchetes* para indicar cualquier caracter incluido dentro de ellos, en este caso los paréntesis.

- El segundo argumento, permite reemplazar los paréntesis por nada, al ser comillas dobles sin espacio, es decir elimina los paréntesis si los encuentra.

- El tercer argumento específica donde se ha de aplicar la acción, en este caso en el campo número 5 de la cabecera gestionada por AWK

#### Eliminar comas
```
gsub(/,/, "",$2)
```
#### Reemplazar vocales
```
gsub(/aeiou/, "X", $3)
```

#### Reemplazar un simbolo por otro
```
gsub(/-/, "/", $1)
```

## Consejo
Si se va a utilizar un patrón que utilice **slash** como una ruta se recomienda utilizar otro delimitador en vez del **slash**, como por ejemplo las **pipeline**.