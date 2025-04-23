---
sidebar_position: 1
title: Jaula Root
---
# JAULA ROOT

## Inicio
Montaje de directorio **chroot**
``` 
sudo mkdir /mnt/chroot
```
// Montar partición raíz en el directorio creado para el montaje en /mnt
// bind permite enlazar el raíz a mnt/chroot, de esta forma se puede acceder bidireccionalmente de uno a otro
sudo mount --bind / /mnt/chroot

// Montar principales directorios del sistema para poder utilizar la utilidad de root
// el parámetro "-t tipo ficheros" es "opcional" pero le da más robustez y evita problemas al intentar
// montar el sistema de ficheros
sudo mount -t proc proc /mnt/chroot/proc
sudo mount -t sysfs sys /mnt/chroot/sys
sudo mount -o bind /dev /mnt/chroot/dev

// Pseudo terminales (emulaciones de PTY's)
// No usar mount --bind /dev/pts porque compromete todo el sistema de pty
sudo mount -t devpts devpts /mnt/chroot/dev/pts

// Acceso a la jaula
sudo chroot /mnt/chroot
Welcome to Linux Lite 7.4
 
You are running in superuser mode, be very careful.
 
Friday 11 April 2025, 09:20:01
Memory Usage: 3117/3915MB (79.62%)
Disk Usage: 23/29GB (82%)

// Cambio passwd
 passwd root
New password: 
Retype new password: 
passwd: password updated successfully


// exit para salir
// sudo umount /mnt/chroot/ todos directorios montados


