---
title: Modbus
---
# Modbus
Protocolo de interconexión utilizado ampliamente dentro de la automatización industrial para poder permitir la comunicación entre dispositivos electrónicos como PLCs o sensores.

## Arquitectura
Se basa en una relación master / slave donde el maestro es el responsable de iniciar la comunicación, para ello el master envía solicitudes a varios slaves que responden a las preguntas del master.

## Funcionamiento
Un master envía una trama (mensaje estructurado) donde se incluye:
- Dirección del esclavo
- Código de función (acción a realizar)
- Datos


## Tipos de ModBus
El protocolo ModBus se puede aplicar de diferentes formas acorde al medio físico sobre el que funcione.

### ModBus RTU
Se utiliza principalmente sobre interfaces serial RS-232 / RS-485, con formato de datos binarios, detección de errores (CRC) y la comunicación por tramas.

### ModBus ASCII 
Opera sobre las interfaces serila RS-232 y RS-485, el formato de datos esta codificado en ASCII (es más legible para las personas pero también es más lento que ModBus RTU), para detección de errores utiliza LRC (Longitudinal Redundancy Check) que es menos eficaz que CRC y la comunicación por tramas se gestiona con controles (':' al inicio y para finalizar CR+LF)

### ModBus TCP
Funciona sobre redes Ethernet (TCP/IP) con lo cual su comunicación funciona en red local o internet, la comunicación es por medio de paquetes TCP/IP, posee más ventajas que los anteriores (más rápido, mayor distancia, mejor integración en la estructura estándar y posibilita el acceso de varios maestros a un mismo esclavo) y la gestión de errores se basa en las técnicas aplicadas en TCP/IP.

## Direccionamiento
En el protocolo ModBus los esclavos disponen de un identificador único (ID), además almacenan la información en tablas de memoria con direcciones específicas, principales tipos:
- Coils (bobinas): valores booleanos para representar ON/OFF mediante 0/1. El master las puede leer y escribir. Son del tipo 0XXXX.
- Discrete Inputs (entradas discretas): valores booleanos solo de lectura para el master. Son del tipo 1XXXX.
- Input Registers (registros de entradas): registros analógicos de 16 bits para lecturas de sensores. Solo de lectura para el master. Son del tipo 3XXXX.
- Holding Registers (registros de retención): registros analógicos de 16 bits de configuración. Pueden ser leídos y escritos por el master. Son del tipo 4XXXX.

## Códigos de función
Son números que el master envía a los slaves para estipular que acción ha de realizar. Algunos ejemplos:
- 01(0x01): lectura de varios coils.
- 05(0x05): escribir un solo coil.

## Características destacadas
ModBus aporta una serie de ventajas como las siguientes:
- Es abierto y libre, implementación gratuita.
- Aporta simpleza y ligereza, además de sencillo también es fiable.
- Es muy compatible, se trata de unos de los principales protocolos de la industria.
- Versatilidad: se puede adaptar a diferentes medios físicos (serial, ethernet)