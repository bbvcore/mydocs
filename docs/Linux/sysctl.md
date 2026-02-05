---
title: Sysctl
---
# Sysctl
Permite leer y modificar parámetros de kernel a través de /proc/sys.
## Parámetros
- sysctl -a
- sysctl kernel.ostype`
### Cambios en caliente
```bash
sudo sysctl net.ipv4.ip_forward=1
```
### Sysctl.conf
Modificar el fichero añadiendo línea como esta para permitir port forwarding 
```bash
net.ipv4.ip_forward = 1
```
Y luego se aplican los cambios
```bash
sudo sysctl -p
```