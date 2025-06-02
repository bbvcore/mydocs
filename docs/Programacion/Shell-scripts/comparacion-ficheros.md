---
sidebar_position: 1
title: Comparaciones COMM
---
# Comm
Comando de GNU/Linux se utiliza para comparar 2 archivos línea a línea mostrando las diferencias y similitudes.
```bash
comm [opcs] file1 file2
```

:::tip[Opciones]
**- 1**: Oculta la primera columna (file1)
**- 2**: Oculta la segunda columna (file2)
**- 3**: Oculta la tercera columna (ambas)
:::

## Opcion recomendada
```bash
comm -12 file1 file2
```

## Ejemplo de uso
```bash
comm -12 <(sort ip-file.txt) <(nmap -sn -n 192.168.1.0/24 | awk '/report/ {gsub(/[()]/, ""); print $5}' | sort)
```