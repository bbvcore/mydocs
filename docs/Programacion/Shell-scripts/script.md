---
title: Iteraciones arrays
---

# Iteraciones arrays ShellScripts
Gestión de los argumentos y el manejo de los mismos desde la cli del OS.

```bash
#!/bin/bash

files=("file1.md" "file2.md" "file3.md")  # Puedes añadir más ficheros

# Iterar sobre cada archivo en el array
for file in "${files[@]}"; do # @ extrae uno a uno los elemnentos arrays

  base_name=$(basename "$file" .md)
  
  # Ejecutar pandoc para convertir a HTML
  pandoc "$file" -o "${base_name}.html"
  
  echo "Archivo ${file} convertido a ${base_name}.html"
done

# $* = todos como string concatenado por espacios los elementos como 1 sola cadena separada por espacios,"s*" todos elementos como una sola cadena separa por delimitados (por defecto espacio) en este caso es solo un único valor, $@ todos como lista/array elementos separados por espacios, si "$@" como elemento individual de una lista/array.
# lo mismo como $*, entonces adaptado a "$files[@]"
# $@ para elementos de un script, $array[@] para los de un array
# "${files[@]}" extraer cada valor independiente en el array
# $file=document, ${file}1=document1, $file1 = error
# Para extensión usar pattern matchin ${file##*.}, ##* elimina todo antes del punto,
# incluido el punto
```