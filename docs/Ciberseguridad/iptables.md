
// Iptables: principales parámetros
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


// Tablas básicas:
<table border="1">
  <tr>
    <th>Tabla</th>
    <th>Uso</th>
    <th>Cadenas Admitidas</th>
  </tr>
  <tr>
    <td>filter</td>
    <td>Filtrado de paquetes, permite o deniega el acceso. (tabla firewall principal)</td>
    <td>INPUT, FORWARD, OUTPUT</td>
  </tr>
  <tr>
    <td>nat</td>
    <td>Traducción de direcciones de red, modifica la dirección de los paquetes (DNAT, SNAT, Masquerade)</td>
    <td>PREROUTING, OUTPUT, POSTROUTING</td>
  </tr>
  <tr>
    <td>mangle</td>
    <td>Modificación de la cabecera de los paquetes (ToS, TTL, QoS, etc.)</td>
    <td>PREROUTING, INPUT, FORWARD, OUTPUT, POSTROUTING</td>
  </tr>
  <tr>
    <td>raw</td>
    <td>Para el seguimiento y exclusión de seguimeinto de conexiones</td>
    <td>PREROUTING, OUTPUT</td>
  </tr>
</table>

// Ejemplos de tablas
//------------------------------------------------
// Tabla FILTER: filtra el tráfico
//------------------------------------------------
// Caso 1: Entre red interna/externa
Red interna (192) y eth0
Red externa (10) y eth1
// 1. Bloqueo de externa a interna, el tráfico interface 1 a 0 prohibido
iptables -A FORWARD -i eth1 -o eth0 -j DROP 
// 2. Permitir solo tráfico de entrada por la interfaz externa 1 y que salga a la red interna 0 para tcp/22 en la Ip local 100
iptables -A FORWARD -i eth1 -o eth0 -p tcp --dport 22 -d 192.168.1.100 -j ACCEPT
// Caso 2: misma red
// Impedir acceso de una máquina local a otra
iptables -A INPUT -s 192.168.1.4 -d 192.168.1.5 -p icmp -j DROP
iptables -A INPUT -s 192.168.1.5 -d 192.168.1.4 -p icmp -j DROP

//------------------------------------------------
// Tabla NAT: redirección de la red interna (DNAT,SNAT,MASQUERADE)
//------------------------------------------------
// Conexiones entrantes al puerto 8080 directos a la IpLocalX:80
iptables -t NAT -A PREROUTING -p tcp --dport 8080 -j DNAT --to-destination IpLocal:80

// Ocultar la Ip privada: los paquetes salen con la IP pública del Servidor
eth0: a internet
eth1: red interna
iptables -t NAT -A POSTROUTING -o eht0 -j MASQUERADE

// Redirigir el tráfico de salida de toda la red local por una IP, es decir el origen es toda la red y el destino la interfaz de salida
// -s: source 192.168.1.0/24 : toda la red
// -o: eth0 interfaz de salida
iptables -t NAT -A POSTROUTING -s 192.168.1.0/24 -o eth0 -j SNAT --to-source "IP de salida a internet (10.0.0.1)"

// Redireccion de tráfico HTTP de la máquina local a un proxy
// salida de 80/tcp al puerto 3232 (proxy)
iptables -t NAT -A OUTPUT -p tcp --dport 80 -j REDIRECT --to-port 3232

//------------------------------------------------
// Tabla MANGLE: gestiona cabeceras 
//------------------------------------------------
// Duplicar tráfico de un equipo con server web a otro equipo de la misma red
iptables -t mangle -A PREROUTING -s serverLocalWebIp -p tcp --dport 80 -j TEE -gateway IPotroequipoRed
iptables -t mangle -A PREROUTING -d serverLocalWebIp -p tcp --sport 80 -j TEE -gateway IPotroequipoRed




//------------------------------------------------
// Tabla RAW: gestiona conexiones
//------------------------------------------------
// evitar seguimiento de conexión de VPN, todo lo que llegue al 80 no seguir esas conexiones.(NOTRACK)
iptables -t raw PREROUTING -p tcp --dport 80 -j NOTRACK 

// desactivar ciertas conexiones (CT:connection tracking): se siguen las conexiones udp 53 para dns
iptables -t raw -A PREROUTING -p udp --dport 53 -j CT --notrack

// Desactivar seguimiento de todas las conexiones para evitar sobrecarga de la red
iptables -t raw -A PREROUTING -j NOTRACK

// Reactivar seguimiento  de todas las conexiones
iptables -t raw -A POSTROUTING -j CT --track

:::tip []
NOTRACK y -j CT --no-track, hacen lo mismo, uno versión vieja y otro nueva
:::

