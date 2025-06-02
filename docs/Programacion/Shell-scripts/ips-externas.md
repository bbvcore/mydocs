---
sidebar_position: 1
title: IPs Externas
---

# Obtener IPs externas
## Sistemas clásicos
<details>
<summary>
Scripts compatibles con sistemas antiguos
</summary>

```bash
#!/bin/bash
# Array con las IPs de las conexiones establecidas
ips=($((ss -tuln | grep ESTAB | awk '{print $5}'  | cut -d':' -f1 )))

# Visualización de IPs
echo "IPs de las conexiones establecidas"
for ip in "${ips[@]}"; do
    echo "$ip"
done
```
</details>

## Sistemas actuales
<details>
<summary>
Scripts compatibles con sistemas modernos
</summary>

```bash
#!/bin/bash
# Array con las IPs de las conexiones establecidas
readarray -t ips < <(
    ss -tan state established |
    grep -Ev '^(127\.|::1|0\.0\.0\.0|::)$' |
    sort -u
)
# Mostrar las IPs almacenadas 
echo "Conexiones establecidas: "
for ip in "${ip_array[@]}"; do
    echo "$ip"
done
```
</details>

## Consejo
Utilizar nmap con el parámetro n para que no resuelva direcciones DNS evita problemas en la gestión de los espacios, si solo hacen falta las IPs es una solución más limpia utilizar dicho modificador para Nmap.

