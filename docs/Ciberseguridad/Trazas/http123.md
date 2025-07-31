---
title: Versiones del protocolo HTTP
---
# Versiones del protocolo HTTP
| Características versión             | HTTP/1.1         | HTTP/2            | HTTP/3              |
|---------------------------|------------------|-------------------|---------------------|
| Transporte                | TCP              | TCP               | QUIC (sobre UDP)    |
| Multiplexación            |  No             |  Sí              |  Sí (SIN bloqueo)  |
| Compresión de headers   |  No             |  HPACK           |  QPACK             |
| Cifrado obligatorio     |  No             |  No (pero común) |  Sí (TLS 1.3)       |
| Server Push               |  No             |  Sí              |  Sí                |
| Latencia y Rendimiento    | Bajo           | Mejorado        | Optimizado    |


## Server push
Server Push es una técnica que permite enviar datos a un servidor sin haber sido solicitados de forma explicita, es información
enviada por el servidor a los clientes de forma activa.

Sin necesidad de realizar un pull se obtiene la información del servidor, su funcionalidad principal es en aplicaciones dinámicas como
pueden ser chats, sistemas de notificación, videojuegos online, streaming....

## Información de las versiones
### HTTP/1.1

Usa **TCP** como protocolo base de transporte, soporta conexiones persistentes que permiten la reutilización de la conexión para múltiples solicitudes. No dispone de multiplexación, así que cada solicitud debe esperar a que la anterior termine (bloqueo de línea). No requiere cifrado, aunque puede usarse HTTPS, y las cabeceras no admiten compresión.

### HTTP/2
Usa de base también TCP pero mejora en relación a HTTP/1.1, introduce multiplexación además de usar HPACK para compresión de cabeceras. Permite Server Push, el cifrado no es obligatorio aunque suele combinarse frecuentemente con TLS.

### HTTP/3
Esta basado en **QUIC**, un protocolo desarrollado por Google que utiliza UDP y elimina el bloqueo al multiplexar datos de forma independientemente, además implementa TLS 1.3 de forma nativa y obligatoría. Comprime cabeceras con QPACK, reduce latencia y mejora las conexiones. Es el protocolo utilizado por las grandes aplicaciones y empresas tecnológicas.