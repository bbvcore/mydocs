---
sidebar_position: 1
title: Keyboard
---
# Keyboard
La configuración del teclado en GNU/Linux tiene sus particularidades según la distribución, en la mayoría de las actuales se implementa con el binario **localectl** integrado en **Systemd**.

No obstante hay distribuciones en las que la configuración con localectl no funciona correctamente al no estar integrado totalmente en la distribución, como por ejemplo en GNU/Linux Lite, en estos casos la opción para configurar correctamente el teclado es **setxkbmap**.


## Localectl
Para configurar el teclado en el idioma escogido, en este caso español, se requiere de la ejecución del comando siguiente.
```
localectl set-x11-keymap es
```
Y se debería de ajustar el idioma, en este caso Español, en el siguiente fichero
```
/etc/X11/xorg.conf.d/00-keyboard.conf
```

:::tip[LocaleCTL]
- Más información de **localectl** en la ayuda del **OS**
```
man localectl
```
:::
Esta solución se aplica a la interfaz gráfica y a la terminal, pero a veces es necesario acceder también al siguiente fichero.
```
sudo nano /etc/default/keyboard
```
Donde se obtiene el siguiente contenido.
```
XKBMODEL="pc105"
XKBLAYOUT="es"
```
Y para actualizar los cambios hace falta ejecutar el comando
```
setupcon
```
:::tip
- Para obtener más información de variables utilizables en la configuración del fichero keyboard se recomienda consultar la entrada del manual centrada en el teclado.
```
man keyboard
```
:::

## Setxkbmap
Para configurar desde la terminal el teclado para el idioma español se requiere ejecutar el comando.
```
setxkbmap es
```
### Persistencia
La configuración anterior sirve para salir del paso, pero al reiniciar el equipo el efecto se pierde ya que no se ha establecido ninguna persistencia, para solventar esta problemática, se plantea la solución de crear en el directorio del usuario (cd ~) la creación / edición de un fichero oculto denominado xprofile (.xprofile) y en ese fichero se establecera la configuración del teclado con el comando visto anteriormente.
```
setxkbmap es
```
Una vez añadido el comando, se guarda el fichero, se reinicia el equipo y el teclado ya estará correctamente configurado en el idioma escogido.
