---
sidebar_position: 2
title: Interfaces red
---

# Configuración interfaces red (GNU/Linux)
Las opciones de configuración de las interfaces de red en GNU/Linux son variadas, en este caso dentro de la rama Debian se dispone de las siguientes opciones.

## Configuración directa desde la terminal
### Mediante el comando IP
#### Limpiar la configuración previa
```
sudo ip addr flush dev <interface>
```
#### Añadir una interfaz de red
```
sudo ip addr add <IP/mask> dev <interface>
```
#### Añadir una puerta de enlace
```
sudo ip route add default via <IP del GW>
sudo ip route add 0.0.0.0 via <IP del GW>
```
:::tip
- **default**: se usa como un alias para facilitar
:::
#### Levantar una interface
```
sudo ip link set <interface> up
```
#### DNS
Configurar el fichero **resolv.conf**, el cual a veces solo guarda los cambios hasta el próximo renicio del OS, para ello tener en cuenta el uso del comando **chattr +i**
```
nameserver 8.8.8.8
```

## Método clásico, interfaces en "/network"
Aquí las dos configuraciones base son configurar con IP estática o IP dinámica.

### Configuración para IP estática
```
auto <interface>
iface <interface> inet static
    address
    netmask
    gateway
    dns-nameservers
```
### Configuración para IP dinámica
```
auto <interface>
iface <interface> inet dhcp
```
## Método moderno, NetPlan
```
network:
    version: 2
    renderer: networkd
    ethernets:
        <interface>
            #dhcp: false # Afecta tanto a IPv4 como a IPv6
            dhcp4: no # Si se necesita dhcp se ajusta a 'yes'
            addresses:
                - <IP/MasK>
            #gateway4: <IP>
            routes:
                - to: 0.0.0.0/0
                  via: <IP del GW>
            nameservers:
                addresses: 
                    - 8.8.4.4
                    - 8.8.8.8
```
Y luego toca aplicar los cambios con el comando siguiente
```
sudo neplan apply
```
### Comprobaciones
```
ip -br a
ip addr
ip addr show <interface>
ip route
ip link
ip link show <interface>
```

## Extra
### Cambio MAC
```
ip link set dev <interface> address <MAC>
```
```
ifconfig <interface> hw ether <MAC>
```