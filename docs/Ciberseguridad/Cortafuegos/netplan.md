---
sidebar_position: 2
title: Netplan
---

# Netplan
## Creación de un fichero yaml
```bash
/etc/netplan/ fichero yaml
```
## Configuración del fichero yaml

```bash
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    enp0s8:  # Nombre de la interfaz de red
      addresses:
        - 192.168.1.2/24  # IP de la máquina de red, con notación CIDR
      routes:
        - to: default
          via: 192.168.1.1  # IP de la GW del Router
      nameservers:
        addresses:
          - 8.8.8.8
          - 8.8.4.4
```

## Activación de la interfaz configurada
```bash
sudo netplan apply
```