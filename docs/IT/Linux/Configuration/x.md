---
sidebar_position: 5
title: Xorg
---

# Sistema gráfico X
## Estructura
La estructura del *sistema gráfico de ventanas* **(X)** en *GNU/Linux* se integra por 3 partes principales.

- **Servidor X**: *principalmente con el paquete xserver-xorg.*
- **Display Manager**: *con el paquete gdm3.*
- **Desktop**: *en el caso del escritorio gnome con paquetes comos gnome-session, gnome-terminal, gnome-control-center, gnome-shell y network-manager-gnome.*

Por otra parte, para sistemas operativos ubuntu existe una opción de instalar todo el sistema gráfico con un simple comando.

```bash
sudo apt install ubuntu-desktop # Versión completa
sudo apt install ubuntu-desktop-minimal # Versión más ligera
```

## Ejecución del sistema gráfico
En systemd el nivel de ejecución del sistema gráfico se engloba dentro del target graphical.

### Carga inicial del sistems X en el OS
```bash
systemctl set-default graphical.target
```

### Comprobar el target actual
```bash
sudo systemctl get-default
```

### Arrancar el sistema X desde la terminal
```bash
sudo systemctl isolate <name>.target
```





