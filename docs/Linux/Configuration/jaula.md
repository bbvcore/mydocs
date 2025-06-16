---
sidebar_position: 1
title: Jaula Root
---
# JAULA ROOT

## Jaula para recuperación del Sistema
### Montaje de directorio **chroot**.
```bash 
sudo mkdir /mnt/chroot
```
### Montar partición raíz en el directorio creado en /mnt
```bash
sudo mount --bind / /mnt/chroot
```
El parámetro **bind** permite enlazar el **directorio raíz** al directorio creado en el punto de montaje **mnt/chroot**, de esta forma la comunicación será bidireccionalmente. 

### Montar principales directorios del sistema para poder utilizar la utilidad de root

```bash
sudo mount -t proc proc /mnt/chroot/proc
sudo mount -t sysfs sys /mnt/chroot/sys
sudo mount -o bind /dev /mnt/chroot/dev
```

Ell parámetro **-t** especifica el tipo de ficheros, es opcional pero permite otorgar a la jaulan una mayor robustez y ayudará a evitar problemas durante la implementación del sistema de ficheros

## Pseudo terminales (emulaciones de PTY's)
```bash
sudo mount -t devpts devpts /mnt/chroot/dev/pts
```
## Acceso a la jaula creada
```bash
sudo chroot /mnt/chroot
Welcome to Linux Lite 7.4
 
You are running in superuser mode, be very careful.
 
Friday 11 April 2025, 09:20:01
Memory Usage: 3117/3915MB (79.62%)
Disk Usage: 23/29GB (82%)
```

### Cambio passwd
```bash
passwd root
New password: 
Retype new password: 
passwd: password updated successfully
```
## Salir de la jaula
Para salir de la jaula se utiliza el comando **exit** y a continuación se procede a desmontar la jaula con el comando
```bash
sudo umount /mnt/chroot/ todos directorios montados
```


## Anexo: Jaula rápida para cambiar password
```bash
sudo mkdir -p /home/jaula/bin
sudo cp /bin/bash /home/jaula/bin/ # Ejecutables necesarios
sudo chroot /home/jaula /bin/bash
```
### Manipulación del root
#### Deshabilitar root
```bash
 sudo passwd -l root
```
#### Habilitar root
```bash
sudo passwd -u root
```
