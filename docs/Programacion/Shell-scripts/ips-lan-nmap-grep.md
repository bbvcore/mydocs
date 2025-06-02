---
sidebar_position: 1
title: Comparaciones GREP
---
# Comparaciones GREP
## Obtención de las IPs
Para obtener la IP se utiliza el escaneo Nmap de la red interna.
```bash
sudo nmap -sn -n 172.23.195.0/24 | awk '/report/ {gsub(/[()]/, ""); print $5}'
```

Se procede a almacenar las IPs con los escaneos.
```bash
sudo nmap -sn -n 172.23.195.0/24 | awk '/report/ {gsub(/[()]/, ""); print $5}' > nmap-ips.txt
```

## Búsqueda de coincidencias
```bash
grep -Fvxf ip-file.txt nmap-ips.txt
```
:::tip[Leyenda parámetros]
- F: coincidencia literal
- v: muestra las NO coincidencias
- x: exactitud de la línea coincidente
- f: nombre del fichero con la lista de patrones
:::

<details>
<summary>
Ejemplo de uso
</summary>

En este ejemplo se puede comprobar la efectividad de este método, además de la limpieza, al usar un par de líneas de código para construir un script completamente funcional.

```bash
┌──(kali㉿PC-1160322)-[/mnt/c/Users/Borja]
└─$ grep -Fvxf ip-file.txt nmap-ips.txt

┌──(kali㉿PC-1160322)-[/mnt/c/Users/Borja]
└─$ cat ip-file.txt
172.23.195.149
192.168.1.45
127.0.0.242
10.10.31.32

┌──(kali㉿PC-1160322)-[/mnt/c/Users/Borja]
└─$ cat nmap-ips.txt
172.23.195.149
8.8.8.8.

┌──(kali㉿PC-1160322)-[/mnt/c/Users/Borja]
└─$ grep -Fxf ip-file.txt nmap-ips.txt
172.23.195.149
```
</details>

