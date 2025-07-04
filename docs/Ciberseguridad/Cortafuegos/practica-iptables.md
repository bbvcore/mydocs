---
sidebar_position: 3
title: IPtables
---

# &#9881; Práctica IPtables
## &#128221; Pasos previos
### &#128736; Configuración de VirtualBox
#### &#128421; Creación de las máquinas virtuales
Crear 4 máquinas virtuales con Ubuntu Server para que sea más liviano el entorno de pruebas.

<details>
<summary>
Configuración del laboratorio de pruebas
</summary>

- **MV que hace de Router**: 2 adaptadores de red.
- **MV que hace de atacante**: 1 adaptador red.
- **MV con Web Server**: 1 adaptador de red.
- **Monitorización**: 1 adaptador de red.
</details>


### &#128421; Máquina Router
#### &#8594; Habilitar el Ip Forwarding

Editar el archivo /etc/sysctl.conf y permitir el  reenvío de paquetes
```bash
sudo nano /etc/sysctl.conf
```
A continuación agregar o descomentar lo siguiente
```bash
net.ipv4.ip_forward = 1
``` 
Aplicar los cambios
```bash
sudo sysctl -p
```

#### &#8594; Configuración de las IPs
La interfaz en modo NAT usará DHCP, la interfaz de la red interna tendrá una IP estática.

```bash
sudo nano /etc/netplan/01-netcfg.yaml
```

```yaml 
network:
  version: 2
  ethernets:
    enp0s8:
      addresses: [192.168.1.1/24]
      dhcp4: no
```

```bash
sudo netplan apply
```

### &#128214; Reglas

#### &#128221; Reglas NAT

```bash
sudo iptables -t nat -A POSTROUTING -o enp0s3 -j MASQUERADE
sudo iptables -A FORWARD -i enp0s8 -o enp0s3 -j ACCEPT
sudo iptables -A FORWARD -i enp0s3 -o enp0s8 -m state --state RELATED,ESTABLISHED -j ACCEPT
```


### &#128421; Máquina atacante
Acceso a la red externa en la que está la interfaz externa del Router y que recibe la dirección IP por DHCP.

#### &#8594; Preparación de herramientas
```bash
sudo apt install nmap hping3 netcat -y
```

### &#128421; Máquina Web Server
#### &#8594; IP estática dentro de la LAN
```bash
sudo nano /etc/netplan/01-netcfg.yaml
```
```bash
network:
  version: 2
  ethernets:
    enp0s3:
      addresses: [192.168.1.2/24] # Corchetes como alternativa a guiones
      gateway4: 192.168.1.1
      nameservers:
        addresses: [8.8.8.8]
```

```bash
sudo netplan apply
```

#### Instalación Apache:
```bash
sudo apt install apache2 -y
```

###  &#128421;Monitorizador
#### &#8594; Herramientas de monitorización
Instalar herramientas como tcpdump, iftop, nagios, zabbix.



## &#128257; Enrutamiento interno con IPtables
### &#8594; Bloquear Fordward
```bash
sudo iptables -P FORWARD DROP
```
### &#8594; Redirección NAT a Servidor Web
Se procede a redirigir al puerto 80 del servidor el tráfico antes de enrutarse.

```bash
sudo iptables -t nat -A PREROUTING -p tcp --dport 80 -i enp0s3 -j DNAT --to-destination 192.168.2.3:80 (máquina virtual con apache)
```

:::tip[Comprobación]
Se comprueba el acceso con curl http://IP_server_router:80, en este
caso es la IP del Router del ISP por DHCP (red externa a las MVs), 
curl http://192.168.1.77:80
:::

### &#8594; Permitir tráfico entre interfaces misma máquina
```bash
sudo iptables -A FORWARD -i enp0s8 -o enp0s3 -j ACCEPT - funciona
sudo iptables -A FORWARD -i enp0s3 -o enp0s8 -j ACCEPT - funciona
```

### &#8594; Reenvió en las reglas de forwarding
El sistema reenvía el tráfico actuando como  **router** al haber previamente **bloqueado** todo tráfico con **forward drop** es decir se accede desde WAN al server.
```bash
sudo iptables -A FORWARD -p tcp -d 192.168.2.3 --dport 80 -j ACCEPT 
```

### &#8594; Duplicar paquetes para Suricata
```bash
sudo iptables -t mangle -A PREROUTING -i enp0s3 -p tcp --dport 80 -j TEE --gateway IP_suricata - Funciona
```

:::warning
Puede ser necesario añadir el módulo xt_TEE
```bash
sudo modprobe xt_TEE
```
:::


### &#8594; Cambiar IP de origen de los paquetes de salida
Para que los paquetes salgan con la IP del Router
```bash
sudo iptables -t nat -A POSTROUTING -o enp0s8 (wan) -p tcp --sport 80  -j SNAT --to-source <IP WAN / IP pública router ".77"> 
```

## Resumen Final
### &#128421; Máquinas virtuales
ubuntu server: 192.168.2.1(red interna borja) y una interfaz NAT
ubuntu apache: 192.168.2.3 y de gw la 192.168.2.1 (red interna borja)
ubuntu suricata: 192.168.2.2 y de gw la 192.168.2.1 (red interna borja)

### &#10004;Apache
sudo apt install apache 2
service apache2 status (comprobar ejecución servicio)
browser -> localhost (ver fichero index.html de apache en browser)

### &#10004; Suricata
```bash
sudo apt install suricata
suricata --build-info (comprobar instalación)
/etc/suricata/suricata.yaml (fichero de configuración)
```

#### &#8594; Monitorizar una interfaz
Se puede usar la etiqueta "af-packet" o "pcap", los modos de captura pueden ser "pfring, af-packet y pcap" y aunque pueden usarse la misma interfaz para todos los modos es mejor usar interfaces diferentes.

#### &#8594; Actualizar suricata
```bash
sudo suricata-update
```

#### &#8594; Uso de Suricata
```bash
sudo suricata -c /etc/suricata/suricata.yaml -i (interface configurada)
(previamente se ha de configurar suricata.yaml)
```

#### &#8594; Datos de suricata
Localizados los datos recopilados por suricata en los siguientes ficheros.
```bash
eve.json
suricata.fast.log
suricata.alert.log
```
Que están alojados en la siguiente ruta
```bash
/var/log/suricata
```







