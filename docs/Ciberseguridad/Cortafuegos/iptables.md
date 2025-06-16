---
sidebar_position: 2
title: Iptables
---

# Iptables

## Principales parámetros
-L
-S
-F
-A
-D
-J
-v
-n
--line-number
-t 


## Tablas básicas:
<table border="1">
  <tr>
    <th>Tabla</th>
    <th>Uso</th>
    <th>Cadenas Admitidas</th>
  </tr>
  <tr>
    <td>Filter</td>
    <td>Realiza el filtrado de paquetes, permitiendo o denegando el acceso. (tabla por defecto)</td>
    <td>INPUT, FORWARD, OUTPUT</td>
  </tr>
  <tr>
    <td>Nat</td>
    <td>Realiza la traducción de direcciones de red, modificando la dirección de los paquetes (DNAT, SNAT, Masquerade)</td>
    <td>PREROUTING, OUTPUT, POSTROUTING</td>
  </tr>
  <tr>
    <td>Mangle</td>
    <td>Realiza la modificación de la cabecera de los paquetes (ToS, TTL, QoS, etc.)</td>
    <td>PREROUTING, INPUT, FORWARD, OUTPUT, POSTROUTING</td>
  </tr>
  <tr>
    <td>Raw</td>
    <td>Realiza el seguimiento y exclusión del seguimiento de conexiones</td>
    <td>PREROUTING, OUTPUT</td>
  </tr>
</table>

## Casos de uso
### Tabla Filter
Realizando la comunicación entre una red interna y un red externa.

- La red interna corresponde a una de **clase C** y utiliza la interfaz **eth0**.
- La red externa corresponde a una de **clase A** y utiliza la interfaz **eth1**.

#### Bloqueo de externa a interna
```bash
iptables -A FORWARD -i eth1 -o eth0 -j DROP 
```

#### Permitir solo tráfico de entrada por la interfaz externa
```bash
iptables -A FORWARD -i eth1 -o eth0 -p tcp --dport 22 -d 192.168.1.100 -j ACCEPT
```

#### Impedir acceso de una máquina local a otra
```bash
iptables -A INPUT -s 192.168.1.4 -d 192.168.1.5 -p icmp -j DROP
iptables -A INPUT -s 192.168.1.5 -d 192.168.1.4 -p icmp -j DROP
```

### Tabla NAT: redirección de la red interna (DNAT,SNAT,MASQUERADE)
#### Conexiones entrantes 
Dirigidas al puerto 8080 de la IP escogida en la red local
```bash
iptables -t NAT -A PREROUTING -p tcp --dport 8080 -j DNAT --to-destination IpLocal:80
```

#### Ocultar la Ip privada
Los paquetes salen con la **IP** pública del servidor, por **eth0** hacía internet y por la **eth1** hacía la red interna.
```bash
iptables -t NAT -A POSTROUTING -o eht0 -j MASQUERADE
```

Redirigir el tráfico de salida de toda la red local por una IP, es decir el origen es toda la red y el destino la interfaz de salida.

- s: source, 192.168.1.0/24 
- o: eth0, interfaz de salida

```bash
iptables -t NAT -A POSTROUTING -s 192.168.1.0/24 -o eth0 -j SNAT --to-source "IP de salida a internet (10.0.0.1)"
```

Redireccion de tráfico HTTP de la máquina local a un proxy, salida del puerto  80/tcp al puerto 3232 (proxy)
```bash
iptables -t NAT -A OUTPUT -p tcp --dport 80 -j REDIRECT --to-port 3232
```

### Tabla MANGLE: gestiona cabeceras 

Duplicar el tráfico de un equipo con server web a otro equipo de la misma red
```bash
iptables -t mangle -A PREROUTING -s serverLocalWebIp -p tcp --dport 80 -j TEE -gateway IPotroequipoRed
iptables -t mangle -A PREROUTING -d serverLocalWebIp -p tcp --sport 80 -j TEE -gateway IPotroequipoRed
```


### Tabla RAW: gestiona conexiones
#### Evitar el seguimiento de conexión
Todo el tráfico que llegue al 80 no se debe de seguir (NOTRACK)
```bash
iptables -t raw PREROUTING -p tcp --dport 80 -j NOTRACK 
```

#### Seguir conexiones
Se siguen las conexiones para udp 53 (DNS)
```bash
iptables -t raw -A PREROUTING -p udp --dport 53 -j CT --notrack
```

### Desactivar seguimiento de todas las conexiones
Para así evitar la sobrecarga de la red
```bash
iptables -t raw -A PREROUTING -j NOTRACK
```


### Reactivar el seguimiento  de todas las conexiones
```bash
iptables -t raw -A POSTROUTING -j CT --track
```
:::tip []
**NOTRACK** y **-j CT --no-track**, hacen lo mismo, uno es la versión más antigua y otro la más actual. Simplemente son dos formas de hacer lo mismo.
:::

