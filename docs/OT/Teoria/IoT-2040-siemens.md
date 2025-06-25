---
sidebar_position: 2
title: Siemens IoT 2040
---

# Siemens IoT 2040
Se trata de una pasarela inteligente desarrollada por Siemens para IoT, aportando una solución industrial para trabajar con PLCs.

:::tip[Imágenes]
<a href="https://support.industry.siemens.com/cs/document/109741799/downloads-for-simatic-iot20x0?dti=0&lc=en-ES">Descargas para Simatic IoT 20xx</a>
:::

## Software disponible
<details>
<summary>
Lista de imágenes disponibles para la descarga
</summary>

 - IOT2040_Example_Image_V3.1.17.zip (639,4 MB)(SHA-256)
 - IOT2040_SDK_Windows_V3.1.17.zip (1,5 GB)(SHA-256)
 - IOT2040_SDK_Linux_V3.1.17.zip (1,2 GB)(SHA-256)
 - IOT2040_Eclipse_Plugin_V2.2.0.zip (10,9 KB)(SHA-256)
 - IOT2040_OpenSourceSoftware_V3.1.17.zip (3,7 GB)(SHA-256)
 - IOT2040_ReadMe_OSS_Multilanguage_V3.1.17.zip (9,7 MB)(SHA-256)

 </details>

<table>
  <thead>
    <tr>
      <th>Característica</th>
      <th>Especificación</th>
    </tr>
  </thead>
  <tbody>
    <tr><td>&#129504; <strong>Procesador</strong></td><td>Intel Quark X1020 (x86, 32 bits), 400 MHz, monocore</td></tr>
    <tr><td>&#129518; <strong>Arquitectura de la CPU</strong></td><td>IA-32 (x86), compatible con GNU/Linux de 32 bits</td></tr>
    <tr><td>&#129504; <strong>Memoria RAM</strong></td><td>1 GB DDR3 (no es ampliable)</td></tr>
    <tr><td>&#128190; <strong>Memoria eMMC</strong></td><td>4 GB eMMC integrada</td></tr>
    <tr><td>&#128190; <strong>Almacenamiento adicional</strong></td><td>Ranura microSD (máximo 32 GB)</td></tr>
    <tr><td>&#128267; <strong>USB</strong></td><td>2 × USB 2.0 tipo A</td></tr>
    <tr><td>&#127760; <strong>Ethernet</strong></td><td>2 × RJ45 (10/100 Mbit/s), admite funciones como NAT o DHCP</td></tr>
    <tr><td>&#128229; <strong>Serial</strong></td><td>1 × RS232, 1 × RS485</td></tr>
    <tr><td>&#128495; <strong>GPIO / I/O</strong></td><td>20 pines GPIO (incluye SPI, I²C o PWM)</td></tr>
    <tr><td>&#128268; <strong>Alimentación</strong></td><td>9–36 VDC (conector con tornillo)</td></tr>
    <tr><td>&#127777; <strong>Temperaturas</strong></td><td>-20°C a +60°C</td></tr>
    <tr><td>&#128207; <strong>Dimensiones</strong></td><td>101 × 111 × 45 mm (para montaje DIN)</td></tr>
    <tr><td>&#9881;&#65039; <strong>OS</strong></td><td>Yocto Linux (preinstalado) o Debian/Armbian</td></tr>
    <tr><td>&#128274; <strong>Seguridad industrial</strong></td><td>Watchdog hardware, secure boot, accesos restringidos por red</td></tr>
    <tr><td>&#128241; <strong>Protocolos</strong></td><td>MQTT, OPC UA (cliente), Modbus TCP/RTU, REST API, Node-RED, etc.</td></tr>
    <tr><td>&#128736;&#65039; <strong>Tools</strong></td><td>Node-RED, C/C++, Python, Java, Arduino (a través de MRAA/UPM), Docker limitado</td></tr>
    <tr><td>&#128295; <strong>Mantenimiento</strong></td><td>Actualizable por USB, SD, o vía remota (SSH, web, etc.)</td></tr>
    <tr><td>&#128279; <strong>Certificaciones</strong></td><td>CE, UL, RoHS</td></tr>
  </tbody>
</table>

## Descarga de la Imagen
La imagen usada es la imagen de example, que ocupa unos **600 MB** y descomprimida unos **3.5GB**. Para su descompresión pueden surgir problemas ya que esta comprimida con **deflate-64** que otorga una gran compresión pero no todos los descompresores lo soportan. En **GNU/Linux** hace falta instalar **dtrx**

```bash
sudo apt install dtrx # Descarga
dtrx file.zip # Uso
```
## Comprobar la imagen
```bash
fdisk from util-linux 2.38.1
lsblk -f iot2000-image-v3.1.17.wic
file iot2000-image-v3.1.17.wic

```
## Instalación en la SD
```bash
sudo dd if=iot2000-image-v3.1.17.wic of=/dev/sdX bs=4M status=progress conv=fsync
```
También se puede usar win32disk, rufus.io o balenaEtcher

## Acceso al dispositivo IOT Siemens 2040
```bash
ssh root@192.168.200.1
```

## Interfaces de red
eth0: 192.168.200.1
eht1: down
sit0NONE: down



