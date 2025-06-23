---
sidebar_position: 1
title: PLC Siemnes
---

# PLC Siemens


## Áreas de memoria en PLC Siemens
Cada área de memoria representa un espacio específico del procesador del PLC para llevar a cabo la realización de ciertas tareas.

#### Áreas de entradas (I)
- **Process Image Input Table**, asociado a la letra (I), le las señales de entradas. Solo lectura.

- **Process Image Output Table**, asociado a la letra (Q), escribe datos a las salidas físicas (actuadores, reles). Escritura y refresco físico.

- **Merker**, el área de marcas es la memoria interna del PLC (la RAM) para almacenameinto temporal.

- **Área de bloque de datos**, estructura de memoría definida por el programador. Maneja DB locales (usado en bloques FC/FB para encapsular los datos) y globales (accesibles desde todo el programa).


- **Área de Temporizadores**, son temporizadores utilizados para el control de retardos o establecer una determinada temporización. No acceden directamente a bits individuales.

- **Área de Contadores**, pueden ser ascendentes (CTU) o descendentes (CTD), se acceden por número.

- **Área local de Pila (L)**, memoria TEMPORAL para variables dentro de un bloque de función. Solo accesible durante la ejecución de bloque. 
```bash
L 7.0
```


- **Área de parámetros (P)**, parámetros de entrada / salida en bloque, las variables que se pasan a funciones o bloques. Suele usar código IN, OUT, IN_OUT.

- **Área de punteros y acumuladores (AR)**, registros de direcciones y acumuladores. Registro especial para el direccionamiento indirecto (sobretodo en STL) del PLC. 


## DataBlocks
Un DB es una estructura de datos utilizada en el PLC para almacenar la información. Cada bloque poseé una dirección fija y dentro de ella se pueden declarar variables.

### Ejemplo
#### Bloque de datos 
```bash
DB1 # Bloque de datos número 1
```
#### Valores contenidos en el DB
```bash
Temperatura: REAL
```

### Dirección de memoria y notación
En los PLCs de Siemens se utiliza la siguiente estructura para la notación.
```bash
DB1.DBX0.0 # DB1 es el bloque 1, DBX0.0 es el BIT 0 del BYTE 0
DB1.DBB0 # Es el BYTE 0 completo
DB1.DBW2 # Es un WORD partiendo en el Byte 2 (16 bits = W)
DB1.DBD4 # Es un DOBLE WORD partiendo desde el Byte 4 (32 bits = W)
```

#### Notación absoluta
Se utiliza el carácter del tanto por ciento **%** acorde a la norma IEC61131-3 para indicar una ruta absoluta. Muy utilizado en lenguajes como ST.

```bash
%DB1.DBX0.0 # Es desde el inicio del bloque, de la posición inicial, DB1, Bit 0, Byte 0
%M0.0 # Merker, Bit 0 del Byte 0
```


## Tipos de memoria en PLC Siemens
### Formato de datos
- **Bit**: 0.0
- **Byte**: B0
- **Word**: W0
- **Double Word**: D0

## Estructura física
### Entradas físicas (I)
Son las señales que proceden de sensores o pulsadores.
```bash
I0.0 # Primera entrada del Byte 0
I1,2 # Tercera entrada del Byte 1
```
### Salidas físicas (Q/O)
Son las señales transmitidas por el PLC a elementos actuadores.
```bash
Q0.0 # Primera salida del Byte 0
Q2.7 # Salida Bite 2, Bit 8 (último Bit)
```

### Marcas (Merkers)
Es la memoria interna del PLC útil para almacenar estados intermedios o flags.
```bash
M10.1 # Segundo Bit, Byte 10
MB10 # Byte10
```
### Temporizadores (Timers)
Son temporizadores internos del PLC. Su configuración se lleva a cabo con un conjunto de instruciones que incluyen TON, TOF o TP.


### Contadores (Counters)
Se trata de contadores internos e incluyen instrucciones como CTU, CTD o CTUD.

### Bloques de datos
Estructuras complejas para almacenar datos definidios por el usuario



## Tabla resumen

| Memoria        | Descripción                                 | Notación |
| -------------- | ------------------------------------------- | --------------- |
| **I** (Input)  | Entradas físicas del PLC                            | `%I0.0`, `%IB0` |
| **Q** (Output) | Salidas físicas del PLC                           | `%Q0.0`, `%QB0` |
| **M** (Marcas) | Memoria intermedia (Ej: variables globales) | `%M0.0`, `%MW2` |
| **DB**         | Bloques de datos    | `%DB1.DBD4`     |
| **T**, **C**   | Temporizadores y contadores                 | `%T1`, `%C3`    |

