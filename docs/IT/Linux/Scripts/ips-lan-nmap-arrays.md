---
sidebar_position: 1
title: IPs internas
---

# IPs internas
Script para obtener las **direcciones IPs** en un escaneo de **LAN**, almacenando las mismas en un **array**.

## Script
```bash
#!/bin/bash
# Comprobación BASH para la ejecución
if [ -z "$BASH_VERSION" ]

# Red a escanear
red="10.0.2.0/24" # Optimizar a argumento $1

# Método terminal old school
# array=($(nmap -sn "$red" | grep "report" | awk '{print $5 ":" $6}'))

# Método más moderno readarray
readarray -t array < <(
    nmap -sn "$red" |
    awk '/report/ {gsub(/[()]/,""); print $5 ":" $6}'
)

for i in "${array[@]}";do
    echo "$i"
done
```

### Mejora
Utilizar **nmap** con el *parámetro* **n** sirve para que Nmap **no resuelva direcciones DNS** ayudando así a evitar los problemas relacionados con los espacios durante la obtención de las IPs.