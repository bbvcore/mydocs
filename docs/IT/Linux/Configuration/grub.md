---
sidebar_position: 1
title: Grub
---

# Grub

```
// 2. Ocultar GRUB
GRUB_DEFAULT=0
GRUB_TIMEOUT_STYLE=hidden # menu, para mostrarlo
GRUB_TIMEOUT=0 # número segundos, o -1 para espera sin límite de tiempo


// 3. Añadir Password al grub

grub-mkpasswd-pbkdf2

 grub-mkpasswd-pbkdf2
Enter password: 
Reenter password: 
PBKDF2 hash of your password is grub.pbkdf2.sha512.10000.13AEC5F2BE1907044C047C2CB343A6DB004A104F3A056D274C465E04A9208E71EF70E121EC62C7C3C787B9FF9A318FD277CC6A4FD4B85C22183174356E9AB995.FC2B83D02B9E9D190455EB8D32B96250BA1A50F360F7D52A9472309A993B5B67FD747DAF64448466DAD3BB16F94C73CCD572CE5BD1D461642AE4DD6002F8674D

// Añadir a grub en fichero de configuración // etc/grub.d/40_custom
set superusers="root"  # "root" o usuario de GRUB
password_pbkdf2 root <hash-generado>  # Añadir el hash

sudo upgrade-grub

resultado:
Sourcing file `/etc/default/grub'
Generating grub configuration file ...
Found background: /boot/grub_linux_lite.png
Found background image: /boot/grub_linux_lite.png
Found linux image: /boot/vmlinuz-6.8.0-57-generic
Found initrd image: /boot/initrd.img-6.8.0-57-generic
Found linux image: /boot/vmlinuz-6.8.0-56-generic
Found initrd image: /boot/initrd.img-6.8.0-56-generic
Found memtest86+x64 image: /boot/memtest86+x64.bin
Warning: os-prober will not be executed to detect other bootable partitions.
Systems on them will not be added to the GRUB boot configuration.
Check GRUB_DISABLE_OS_PROBER documentation entry.
Adding boot menu entry for UEFI Firmware Settings ...
done


// Teoría
los archivos de /etc/grub.d generan el fichero grub.cfg, en etc/grub.d existen una serie de scripts numerados

00_header	Configuración básica de GRUB (variables como GRUB_TIMEOUT, GRUB_CMDLINE_LINUX, etc.).
10_linux	Detecta kernels de Linux instalados y genera entradas de arranque automáticas.
20_memtest86+	Añade opción para Memtest86+ (si está instalado).
30_os-prober	Detecta otros sistemas operativos (Windows, otro Linux) en discos.
30_uefi-firmware	Añade opción para entrar al firmware/BIOS UEFI.
40_custom	Para añadir entradas personalizadas manualmente (como usuarios, contraseñas o menús custom).
41_custom	Similar a 40_custom, pero se ejecuta después (útil para override).



// NOTA
El grub oculto se puede sacar con "escape" o "shift"
En el grub, si se presiona "e" se puede 

```