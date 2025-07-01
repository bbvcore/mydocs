---
sidebar_position: 1
title: IDS/IPS
---

# :globe_with_meridians:IDS/IPS 
En un intento de **disminuir** las **vulnerabilidades** a las que se enfrenta un sistema **IT** surgen los sistemas **IDS** para detectar anomalías y usos indebidos.

Debido a la dificultad de disminuir dichas vulnerabildiades surgen los **IPS**, hoy en día se usan indistintamente **IDS/IPS**, dado que los equipamientos son idénticos, y las diferencias solo se aprecian en el despliegue y en algunos de los parámetros de configuración.


## :pager: SIEM 
Son **sistemas** que permiten **centralizar la información** relacionando eventos de diferentes fuentes **y** *de esta forma* **generar alertas personalizadas**.

:::tip[Ventaja entorno OT]
Estos sistemas poseen una ventaja en **OT** sobre **IT**, y es la variabilidad, reduciendo con ello el número de falsos positivos.
:::

## :pushpin: Arquitectura base 

Basada en la norma **IEC 62443**, norma de ciberseguirdad para sistemas industriales.

<details>
<summary>
Características de la norma 62443
</summary>

- <b>Segmentación de la red</b>: división en zonas dependiendo de su nivel crítico. Utilizar: routers y switches gestionados.

- <b>Defensa</b>: diversificar, no confiar solo en un punto de seguridad. Utilizar: Autenticación, Firewalls...

- <b>Niveles de madurez de seguridad</b>: de SL1 (protección contra errores consecuencia de accidentes) hasta SL4 (protección contra ataques organizados).

- <b>Control de acceso mediante roles</b>: solo las personas autorizadas pueden operar ciertos sistemas.

- <b>Gestionar el ciclo de vida</b>: mantener y controlar los sistemas desde su instalación hasta el presente día.


</details>


## :beginner: Arquitectura para sistemas de control 
Todo el tráfico que pasa por los **routers/switches** se lleva al **IDS** haciendo uso de los **puertos espejo** para recibir información y así poder controlar el tráfico intercambiado con la red **(IT)**.

:::note[Port Mirroring]
Los puertos espejo permiten clonar el tráfico de un puerto determinado a otro, el cual esta controlado por un sistema de análisis (SIEM, IDS, Analizador de tráfico)
:::


El **IDS** debe de estar correctamente configurado y contar con las alertas necesarias para mostrar al administrador.


## &#128272; Arquitectura de seguridad con IDS
El **IDS** ha de ser capaz de poder bloquear el tráfico, así los los sensores se ubican en medio del tráfico.

Los **sensores** son dispositivos,físicos o virtuales, que permiten capturar, monitorear y analizar el tráfico de la red de forma pasiva.

Se suelen ubicar en puertos espejo, en DMZ o en zonas críticas para alertar de comportamientos anómalos.

:::tip[Herramientas comunes]
- Wireshark
- Zeek, Suricata, Snort
- Nozomi Networks, Claroty, Dragos
:::














