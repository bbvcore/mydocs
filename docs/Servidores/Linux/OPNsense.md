---
sidebar_title: 1
title: OPNsense
---
# OPNsense
OPNsense es una distribución FreeBSD que se utiliza como Firewall.
## Descarga
La descarga se realiza desde su propia página web, la cual está accesible en la siguiente URL.
```
https://opnsense.org/download
```

## Requisitos
### Mínimos
<table>
<tr>
    <td>Procesador</td>
    <td>1 GHz dual core</td>
</tr>
<tr>
    <td>RAM</td>
    <td>2 GB</td>
</tr>
<tr>
    <td>HDD</td>
    <td>4 GB</td>
</tr>
</table>

### Deseables / Recomendados
<table>
<tr>
    <td>Procesador</td>
    <td>1.5 GHz multi core</td>
</tr>
<tr>
    <td>RAM</td>
    <td>4GB / 8GB RAM</td>
<tr>
</tr>    
    <td>HDD</td>
    <td>40GB / 120GB</td>
</tr>
</table>

## Interfaces de red
Mínimo se requieren de 2 tarjetas Ethernet, una para hacer de **WAN** *(la que tendrá que salida a internet)* y otra que hará de **LAN** *(la que conectará con nuestra la red local)*.

Inicialmente la interfaz de **WAN** en entorno simulado será con **Bridge* y la interfaz de **LAN** será en modo red interna.

:::warning[Credenciales]
En OPNsense, de serie hay 2 usuarios, uno es **root** y otro es **installer**. Las credenciales son las siguientes:
- User: root, Password: opnsense
- User: installer, Password: opnsense
:::


## Instalación
Dejar bootear normal la live CD y comprobar que detecte las dos interfaces de red. Una vez finaliza se muestra un login.

:::[LAGGs y VLANs]
- LAGGs: Permite concentrar varios enlaces de red físicos en uno lógico.
- WLANs: Redes virtuales mediante enlaces troncales gestionadas a través de etiquetas de 4 bytes.
:::

### Login
Como vamos a realizar la instalación hacemos login con el usuario **installer**. Una vez accedido al sistema nos sale un asistente de instalación en la shell.

### Seleccionar la distribución del teclado
En este caso se escoge español con acentos, una vez escogido nos muestra una sección donde podemos comprobar que el teclado funcione correctamente insertando simbolos o palabras con tildes.

### Formato instalación
- **UFS**: por defecto GPT/UEFI hybrid
- **ZFS**: más robusto y también GPT/UEFI hybrid
- **Import config**: para recuperar una instalación
- **Password reset**: permite resetear la password
- **Force reboot**: forzar el reinicio

### Instalar la opción ZFS
Ofrece varias opciones de particionado, acorde al hardware que se dispone, suelen ser sistemas **RAID**, en este caso como solo hay un disco uso la opción **Stripe**. Una vez seleccionado el instalador mostrará el tipico mensaje de advertencia.

### Cambio de contraseña
Una vez escogido el disco se nos ofrece la posibilidad de cambiar la contraseña del usuario **root**.

### Escoger completar instalación
Una vez completada la instalación se reiniciará la distribución y se podrá hacer login en nuestra instalación, con la cuenta root y con el password modificado.

### Menú de configuración
Una vez logueado vemos un menú de configuración, pero justo antes unas llaves SHA256 para HTTPS y SSH.

En cuanto al menú vamos a proceder a configurar nuestras 2 interfaces, la de la WAN y la de la LAN.

### Configuración de interfaces de red
Se van a usar las opciones del menú de configuración 1 y 2, que permitirán "asignar inferfaces" y "asignar una dirección Ip a una interfaz".

### Asignar interfaces de red
Se escoge la opción 1 del menú de opciones y se responde a las siguientes cuestiones:
- Configurar protocolo LAGGs?, No
- Configurar protocolo VLANs?, No
- Escribir nombre WAN: em0
- Escribir nombre LAN: em1
- Añadir otra interfaz opcional?, intro (que es lo mismo que no asignar nada).

Se muestran los resultados de la asignación y si son correctos se aceptan.

### Asignar dirección IP
Se escoge la opción 2 del menú de configuración y se responden a las siguientes cuestiones:
- Escoger la interfaz a modificar introduciendo un número (1,2,n) acorde a como sean listadas.
- Configurar DHCP?, No
- Introducir datos de la configuración de la IP, si hubiese algún conflicto con otra dirección de la red lo comunicaría la distro por terminal.
- Número de bits a asignar a la máscara de subred, responder entre 1 y 32 bits.
- Configurar otra interfaz?, según sea el caso sí o no.
- Configurar IPv6?, No
- Cambiar HTTPS por HTTP?, No
- Nuevo certificado para la GUI?, Sí
- Resetear los valores por defecto de la GUI?, No
