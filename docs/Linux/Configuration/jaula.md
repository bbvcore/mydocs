---
sidebar_position: 1
title: Jaula Root
---
# JAULA ROOT

## Terminales
Montaje de directorio **chroot**.
``` 
sudo mkdir /mnt/chroot
```
### Montar partición raíz en el directorio creado en /mnt
```
sudo mount --bind / /mnt/chroot
```
El parámetro **bind** permite enlazar el **directorio raíz** al directorio creado en el punto de montaje **mnt/chroot**, de esta forma la comunicación será bidireccionalmente. 

### Montar principales directorios del sistema para poder utilizar la utilidad de root

```
sudo mount -t proc proc /mnt/chroot/proc
sudo mount -t sysfs sys /mnt/chroot/sys
sudo mount -o bind /dev /mnt/chroot/dev
```

Ell parámetro **-t** especifica el tipo de ficheros, es opcional pero permite otorgar a la jaulan una mayor robustez y ayudará a evitar problemas durante la implementación del sistema de ficheros

## Pseudo terminales (emulaciones de PTY's)
```
sudo mount -t devpts devpts /mnt/chroot/dev/pts
```
## Acceso a la jaula creada
```
sudo chroot /mnt/chroot
Welcome to Linux Lite 7.4
 
You are running in superuser mode, be very careful.
 
Friday 11 April 2025, 09:20:01
Memory Usage: 3117/3915MB (79.62%)
Disk Usage: 23/29GB (82%)
```

### Cambio passwd
``` 
passwd root
New password: 
Retype new password: 
passwd: password updated successfully
```
## Salir de la jaula
Para salir de la jaula se utiliza el comando **exit** y a continuación se procede a desmontar la jaula con el comando
```
sudo umount /mnt/chroot/ todos directorios montados
```

