---
title: Sistema de ficheros
---
# Sistema de ficheros
Un sistema de ficheros en un sistema operativo es la estructura lógica y el conjunto de métodos que permiten organizar, almacenar y recuperar datos en un dispositivo de almacenamiento (como un disco duro, SSD, o memoria USB).

De manera complementaria, el sistema de ficheros se apoya en varias estructuras internas para gestionar la información:

Tabla de bloques:
Mantiene un registro de qué bloques de memoria del dispositivo están libres o ocupados. Es esencial para localizar espacio disponible y asignarlo a nuevos archivos o extender los existentes.

Directorios:
Son estructuras jerárquicas que almacenan las entradas de archivos y subdirectorios. Cada entrada de directorio contiene información básica como el nombre del archivo y un puntero (por ejemplo, hacia un inodo).

Inodos (nodos de índice):
Son estructuras que almacenan la metadata de cada archivo (permisos, propietario, fechas de acceso/modificación, tamaño, punteros a bloques de datos, etc.), pero no el nombre. El nombre del archivo se asocia a su inodo a través de la entrada en un directorio.

## Tabla de sistemas de ficheros
| Elementos                                | FAT32                                                     | NTFS                                                                             | EXT4                                                                               | Descripción                                                         |
| ---------------------------------------- | --------------------------------------------------------- | -------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------- | ------------------------------------------------------------------------------- |
| **Sector**                               | 512 B (o 4 KB actualmente)                         | 512 B / 4 KB                                                                     | 512 B / 4 KB                                                                       | Unidad mínima  en disco                             |
| **Cluster / Bloque**                     | 4 KB – 32 KB (hasta 64 KB)                                | 4 KB (configurable)            | 4 KB (Hasta 1 MB)                                                     | Unidad mínima de asignación del FS; agrupa sectores                             |
| **Número de sectores x cluster**       | En función del tamaño del cluster                            | Según  tamaño del cluster                                                   | Según tamaño del bloque                                                      | Cluster = n° de sectores × tamaño sector                                        |
| **Tamaño mínimo  archivo** | 1 cluster                                                 | 1 cluster                                                                        | 1 bloque                                                                           | Si el archivo es más pequeño, se usa el cluster completo |
| **Desperdicio máximo x* archivo**      | Cluster - 1 B                                             | Cluster - 1 B                                                                    | Bloque - 1 B                                                                       | Espacio no usado  (desperdiciado)                        |
                        
