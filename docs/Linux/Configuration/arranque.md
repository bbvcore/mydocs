---
sidebar_position: 8
title: Arranque
---

# Arranque
## SysV
El primer proceso que ejecuta el OS durante el arranque es **init**, y a continuación se consulta el fichero **inittab** donde está su configuración y se comprueba el nivel de ejecución del **OS**, en función de ello, se accede a los **/etc/rc2.d/**.

:::tip[Runleves]
- 0: runlevel 0 (apagado)
- 1: runlevel 1 (monousuario)
- 2: runlevel 2 (multiusuario sin red)
- 3: runlevel 3 (multisuario con red)
- 4: runlevel 4 (experimental, no usado)
- 5: runlevel 5 (modo gráfico)
- 6: Reinicio 6 (reinicio)
:::

Start: S##nombre
Kill: K##nombre

Acorde al nivel de runlevel se ejecutan los scripts alojados en ese directorio rcX.d, todos los scripts de rc son enlaces simbólicos de init.d

## SystemD
:::tip[Targets]
- 0: poweroff
- 1: rescue
- 2: multi-user
- 3: multi-user
- 4: multi-user
- 5: graphical
- 6: reboot
:::


