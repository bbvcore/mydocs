---
sidebar_position: 1
title: Comparaciones FOR anidado
---

# Comparaciones IPs con FOR
Para ello son necesarias fuentes de datos, la primera serán las IPs escaneadas con nmap en la red local y la segunda será un fichero con una dirección de IPs permitidas.

## Obtener IPs de la red local
Almacenamiento de los datos en un array tras escanear la red con nmap.
```bash 
readarray -t nmap_ips < <(
    nmap -sn -n "$1" |
    awk '/report/ {gsub(/[()]/, ""); print $5}' 
)
```

:::tip[Explicación generación Array]
- **readarray -t nmap-ips**: *creación de un array con el nombre nmap-ips*
- **nmap**: Escaneo de la red sin resolver **DNS** acorde a la dirección pasada como argumento **$1** durante la ejecución del script desde la terminal.
- **awk '/report/'**: búsqueda en los resultados de nmap de las líneas con la palabra **report**.
:::

## Obtener las IPs desde un fichero de texto
Leer las **IPs** desde un *fichero de texto* y almacenarlo en un array.
```bash 
readarray -t file_ips < ips.txt
```
## Comparación de los arrays
```bash
for ip_nmap in "${nmap_ips[@]}"; do
    counter=0
    for ip_list in "${file_ips[@]}"; do
        if [[ "$ip_nmap" == "$ip_list" ]]; then
            echo "IP coincidente: $ip_nmap"
            counter=1
            break
        fi
    done
    [[ $counter -eq 0 ]] && echo "IP no encontrada"
done
```