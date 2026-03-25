---
title: Metasploitable 2
---

# Metasploitable 2
## Obtención de los ficheros
Desde sourceforge se descarga: https://sourceforge.net/projects/metasploitable/files/Metasploitable2/

## Creación de una MV en virtual Box
Se crea una máquina virtual en vBox y se añade un disco duro virtual existente que se corresponde al descargado desde sourceforge.

## Credenciales
:::tip[User y password]
- User: msfadmin 
- Password: msfadmin
:::

## Configurar interface de red
<details>
<summary>
Edición del fichero /etc/network/interfaces
</summary>

```bash
auto eth0
iface eth0 inet static
    address 10.255.255.127
    netmask 255.255.255.0
    gateway 10.255.255.1
```
</details>

