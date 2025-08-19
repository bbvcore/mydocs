---
title: Particionamiento disco
---
# Particionamiento disco
Los discos necesitan establecer unos sistemas para organizar la información, pero antes de ello hay que dotarlos de una estructura, para ello existen 2 módelos, MBR y GPT, que permiten organizar la división del disco además de gestionar como arranca el mismo.

- MBR: es el método tradicional, posee una tabla de particiones y el bootloader en el primer sector del disco. Sector 0. Este sistema posee unas limitaciones de un más de 4 particiones primarias (permitía más lógicas) y de un uso de discos duros con una capacidad máxima de 2 Terabytes. Además funcionan con el sistema tradicional de BIOS.

- GPT: es el método moderno, las tablas de particiones poseen identificadores únicos, permiten un número elevado de particiones, soporta discos duros de mayor tamaño y a su vez es capaz de almacenar información de seguridad. Funciona con el sistema moderno UEFI.

## Tabla y bootloader
El MBR posee el bootloader dentro del primer sector del disco, sector de arranque coloquialmente. 

:::info
Un bootloader es una porción minima de código que se encarga de arrancar un sistema operativo.
:::

En el sistema MBR tanto la tabla de particiones como el bootloader se encuentran dentro del mismo sector.

El sistema GPT no mezcla el bootloader con la tabla de particiones. Utiliza una partición especial llamada ESP (EFI System Partition) donde se almacena el bootloader (grubx64.efi en Linux) y este sistema, GPT, mantiene varias copias de seguridad.

## Estructura de bloques
### Master Boot Record
Como se ha comentado anteriormente el sector 0 contiene todo:
- Bootloader primario: código de arranque mínimo (446 bytes)
- Tabla de particiones: hasta 4 particiones (64 bytes)
- Firma del disco: 55 AA marca el final del disco (2 bytes)

## GUID Partition Table
El sector 0 contiene un protective MBR, que no se usa para arrancar pero sí para ser compatible con software antiguo, y de esta forma no tener problemas de reconocer GPT.

Sector 1 posee el Primary GPT Header donde está la tabla de particiones e información del disco además del GUID único.

Sectores 2-33 contienen la tabla primaria de particiones, cada entrada posee una partción con un GUID.

Al final del disco se establace una copia del encabezado GPT y de la tabla de particiones, siendo un sistema redundante.

El arranque va en la partición ESP mencionada anteriormente, que es una partición que va en el espacio de los datos, de las particiones.