---
title: grep
---
# Grep
Es un comando muy util para realizar búsquedas de patrones desde la Shell

| Parámetro | Función                                                  | Uso                                                           |
| ------ | ------------------------------------------------------------ | ----------------------------------------------------------------- |
| `-i`   | Ignora mayúsculas/minúsculas                                | `grep -i "error" log.log`                                     |
| `-n`   | Muestra el número de línea                         | `grep -n "echo" script.sh`                                     |
| `-v`   | Invierte la búsqueda (mostrar lo que **NO** coincide)   | `grep -v "error" log.log`                                        |
| `-F`   | Busqueda textual (no usa Regex)                   | `grep -F "a*b" file.txt` (busqueda textual de "a*b")       |
| `-x`   | **Coincidencia exacta** con el patrón | `grep -x "error" log.log` *(solo líneas que contengan "error")* |
| `-r`   | Busqueda recursiva                         | `grep -r "img1.png" ./imgs/`                                      |
| `-c`   | Muestra el número de líneas coincidentes                | `grep -c "error" error.log`                                      |


:::tip["Escape de carácteres"]

:::

## Extender REGEX
En grep el uso de REGEX se puede alternar entre el modo básico y el más detallado, este último se habilita haciendo uso del parámetro -E.
El uso de las **expresiones regulares extendidas** permite usar una sintaxis más moderna y acorde al uso en otros lenguajes, al usar la sintaxis
básica de grep hay que escapar algunos caracteres que con la sintaxis extendida no pasa.


| **Patrón** | **Función**                    | **Ejemplo**      | 
| ---------- | ------------------------------ | ---------------- | 
| `.`        | Cualquier carácter             | `a.b`            | 
| `^`        | Inicio                         | `^abc`           | 
| `$`        | Fin                            | `xyz$`           |
| `*`        | 0 o + repeticiones (del elemento anterior)           | `di*a`           | 
| `+`        | 1 o + repeticiones (del elemento anterior)          | `di+a`           | 
| `?`        | 0 o 1 repetición   (del elemento anterior)            | `sabou?r`        |
| `{n}`      | `n` repeticiones               | `x{10}`           | 
| `{n,}`     | `n` o + repeticiones         | `x{2,}`          | 
| `{n,m}`    | Entre `n` y `m` repeticiones   | `a{2,4}`         | 
| `[...]`    | Uno de los caracteres                 | `[aeiou]`        | 
| `[^...]`   | Cualquiera menos los de los corchetes        | `[^0-9]`         | 
| `(abc)`    | Agrupar                | `(abcd)+`          | 
| `Barra vertical`         | Barra vertical                  | OR | 
| `\.`       | Punto literal             | `\.txt`          | 
| `\\`       | Barra invertida literal       | `\\n`            | 
| `\d`       | Dígito (0–9)       | `\d{2}`          | 
| `\w`       | Palabra  | `\w+`            | 
| `\s`       | Espacio en blanco   | `\s+`            | 
| `\D`       | NO Dígito (0–9)       | `\d{2}`          | 
| `\W`       | NO Palabra  | `\w+`            | 
| `\S`       | NO Espacio en blanco   | `\s+`            | 


:::tip
Para un número inditerminado de caracteres, sin relación con el elemento anterior, la opción es: .*, de esta forma
se obtienen un número entre 1 y n de caracteres que pueden ser diferentes.
:::
:::warning
El comodín anterior se denomina **comodin codicioso** porque entra todo hay búsquedas que igual quieren ser más finas, por ello
se usa el comodín menos codicioso: .*?, que cuando se posiciona entre un catacter inicial y final, usará el comodin hasta encontrar la primera coincidencia con el caracter final. Si fuera
el codicioso le daría igual y el número de caracteres podría ser **"n"**.
:::