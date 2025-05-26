---
sidebar_position: 10
title: Bind
---

# BIND
En este documento se realiza la instalación y configuración de 2 servidores DNS (master/slave) en GNU/Linux, concretamente en 2 equipos que ejecutan la distribución Ubuntu Server.
## Instalación
```bash
sudo apt update
sudo apt upgrade
sudo apt install bind9
```
## Servidor master
En el fichero **named.conf.local** se van a crear las zonas del servidor, en este caso del principal que va a actuar como **master**.

Además de la zona principal, también se creara la zona para la resolución de inversa, cubriendo así todo tipo de consultas a servidores, tanto por el nombre de dominio como por la dirección IP

### Contenido named.conf.local 
:::warning[IPs]
- La **IP** del **master** en este caso es: **192.168.1.100**.
- La **IP** del **slave** en este caso es: **192.168.1.101**.
:::

```bash
zone "bbvnet.local" {
    type master;
    file "/etc/bind/zones/db.bbvnet.local";
    allow-transfer { 192.168.1.101; };
};

zone "1.168.192.in-addr.arpa" {
    type master;
    file "/etc/bind/zones/db.192.168.1";
    allow-transfer { 192.168.1.101; };
};
```
En este fichero se establece el nombre de la zona, con el nombre de dominio local y con la resolución de inversa.

Además se especifica la ubicación de los ficheros de configuración de estas zonas, que es donde se establecerán las características de la **zona de autoridad**.

### Contenido de db.bbvnet.local
```bash
$TTL 86400

bbvnet.local.         IN    SOA     ns1.bbvnet.local. admin.bbvnet.local. (
                      2025051201 ; Serial
                      3600       ; Refresh
                      1800       ; Retry
                      604800     ; Expire
                      86400 )    ; Negative Cache TTL

bbvnet.local.         IN    NS      ns1.bbvnet.local.
bbvnet.local.         IN    NS      ns2.bbvnet.local.

ns1.bbvnet.local.     IN    A       192.168.1.100
ns2.bbvnet.local.     IN    A       192.168.1.101
```

### Contenido de db.192.168.1
```bash
$TTL 86400

1.168.192.in-addr.arpa.     IN    SOA     ns1.bbvnet.local. admin.bbvnet.local. (
                          2025051201 ; Serial
                          3600       ; Refresh
                          1800       ; Retry
                          604800     ; Expire
                          86400 )    ; Negative Cache TTL

1.168.192.in-addr.arpa.     IN    NS      ns1.bbvnet.local.
1.168.192.in-addr.arpa.     IN    NS      ns2.bbvnet.local.

100.1.168.192.in-addr.arpa.   IN    PTR     ns1.bbvnet.local.
101.1.168.192.in-addr.arpa.   IN    PTR     ns2.bbvnet.local.
```

## Servidor slave
Los ficheros de ambas zonas, tanto el de la directa como el de la inversa ya están en el maestro, estos fichero se replicarán en el **slave** en el directorio **/var/cache/bind**, esa ruta puede variar si se edita en el fichero **named.conf.options**.
```bash
zone "bbvnet.local" {
    type slave;
    file "/var/cache/bind/db.bbvnet.local";
    masters { 192.168.1.100; };
};

zone "1.168.192.in-addr.arpa" {
    type slave;
    file "/var/cache/bind/db.192.168.1";
    masters { 192.168.1.100; };
};


```


## Consultas externas
Las consultas externas, fuera de la zona de autoridad creada para las resoluciones DNS internas, se configuran en el siguiente fichero.
```bash
sudo nano named.conf.options
```
Y allí en el apartado de forwarders se especifican los servidores DNS para tal fin.
```bash
// Fichero para la replicación
directory "/var/cache/bind";

// Permitir recursividad
recursion yes;

// Redes permitidas para consultas
allow-query { any; };

// DNS externos
forwarders {
    8.8.8.8;        
    8.8.4.4;       
    1.1.1.1;       
};
```