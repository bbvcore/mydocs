---
sidebar_position: 2
title: Netplan
---

# &#127760; Netplan
## &#128190; Creación de un fichero yaml
```bash
/etc/netplan/ fichero yaml
```

## Networkd NetworkManager
Networkd, es del systemd para red a bajo nivel (para servidores, contenedores o cloud), la gw esta fuera de la subred
hace falta añadir on-link: true. No actua con wifi o redes dinámicas. Muy estricto.
NetworManager, es un gestor de red completo para escritorio (gnome, kde...). Actua bien con wifi y redes dinámicas (VPNs, redes móviles), ideal
para pcs de escritorio y portátiles. Más flexible.

Elemento	networkd	NetworkManager
gateway4	Se aplica tal cual	Puede añadir rutas adicionales
routes:	Se respetan exactamente	Puede ignorarlas o cambiar métricas
on-link	Necesario si el gateway no está en la subred	A veces lo ignora


## &#128225; Configuración del fichero yaml

```bash
## Uso routes
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

## Ejemplo para varias Gw
#routes: - to: 0.0.0.0/0 via: 192.168.1.1 metric: 100 - to: 0.0.0.0/0 via: 192.168.1.254 metric: 200


## Uso gateway
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    enp0s8:
      addresses:
        - 192.168.1.2/24
      gateway4: 192.168.1.1
      nameservers:
        addresses:
          - 8.8.8.8
          - 8.8.4.4

          
```

## &#128737; Activación de la interfaz configurada
```bash
sudo netplan apply
```