---
title: Manual
---
# Manual
La consulta del manual permite encontrar mucha ayuda referente a los comandos del sistema, existen varios parámetros que pueden ser muy útiles para este fin.
- k / apropos "palabra": busca en las descripciones.
- f "comando": buscar info de un comando y en que sección está.
- "number section" "tema de la section".
- a "comando": todas las opciones posibles de ese comando.

:::warning[Falta de entradas en el manual]
sudo apt update
sudo apt install man-db
sudo apt install  manpages-es
sudo apt install  manpages-dev
:::

Dentro de man es muy util realizar búsqueda dentro de la entrada, para poder encontrar algunos conceptos de forma rápida, para ello es interesante
```bash
Utilizar "/" dentro de la entrada
```