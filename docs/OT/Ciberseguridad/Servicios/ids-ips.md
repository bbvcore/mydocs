---
sidebar_position: 1
title: IDS/IPS
---

# IDS/IPS :globe_with_meridians:
Para intentar paliar las vulnerabilidades a las que se enfrenta un sistema **IT** surgen los sistemas **IDS** para detectar anomalías y usos indebidos.

Actualmente debido a las dificultades a las que se enfrentan se desarrollaron los **IPS**, que hoy en día se usan indistintamente **IDS/IPS** dado que los equipamientos son idénticos, cambiando el modo de funcionamiento en función del despliegue y de unos pocos parámetros de configuración.

Ante las amenazas que se enfrentan en **OT** se implementan estas herramientas en redes indsutriales examinando los protocolos y transmisiones que circulan por la red.


## SIEM :pager:
Estos sistemas permiten centralizar la información y son capaces de relacionar eventos de diferentes fuentes para generar alertas personalizadas además de incorporar inteligencia para reducir paulatinamente los falsos positivos.

:::tip[Ventaja entorno OT]
Estos sistemas poseen una ventaja en el entorno **OT** sobre el entorno **IT** ya que suelen presentar menor variabilidad y con ello un número menor de falsos positivos.
:::

## Arquitectura base de sistema de control :pushpin:

Esta arquitectura está basada en la norma **IEC 62443**. Presenta una segmentación mediante cortafuegos para separar las zonas de control y corporativa, con 2 **DMZ** para el intercambio de información entre ambas zonas.



## Arquitecturas seguridad para sistemas de control :beginner:
En esta arquitectura todo el tráfico que pasa por los routers/switches se lleva al **IDS** a través de los puertos espejo, además de añadir una sonda para recibir información del cortafuegos para poder controlar el tráfico intercambiado con la red empresarial **(IT)**.

:::tip[]
El **IDS** debe de estar configurado con las alertas oportunas para mostrar al administrador.
:::

## Arquitectura de seguridad con IDS
La evolución del IDS pasa por bloquear el tráfico por ello los sensores pasen a estar en medio del tráfico en vez de estar escuchando los puertos espejos.












