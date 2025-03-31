---
sidebar_position: 4
title: Problemas y soluciones
---
# Problemas y soluciones
En este punto se recopilan una serie de problemáticas surgidas y de algunas posibles soluciones.

## Con VirtualBox
Los problemas en las pruebas de virtualización con **Virtual Box** son susceptibles de ocurrir con varias de las configuraciones de red ofrecidas.

- **Con la configuración de la interfaz de red como NAT**: *La **NAT** de Virtual Box no permite entradas **TCP/IP** y solo permite salidas **TCP/IP**. Por este motivo desde una máquina cliente no se puede acceder a la máquina de **Security Onion** con la configuración como **NAT**. Cabría la posibilidad de configurar **Port Forwarding** en Virtual Box e intentar que funcionase, pero no se ha probado porque aún funcionando el rendimiento se vería condicionado*. **Estado de las pruebas**: *NO Funciona*.

- **Con la configuración de red como bridge**: con esta configuración funciona perfectamente muy parecida a un entorno real, pero el problema que aquí sucede es que la máquina necesita una **IP** proporcionada por el *DHCP** del router de la red y en el **entorno de la red de IT** no se puede obtener esa asignación de dirección de IP debido a la configuración y administración de la misma. **Estado de las pruebas**: *SÍ Funciona*, pero faltan IPs adicionales para llevar a cabo las pruebas.

- **Con la configuración de red como red interna**: *existe un problema porque cuando se accede a la máquina de **Security Onion** para lanzar el asistente de configuración de la red, saliendo de el y comprobando la **interfaz ip** asignada por **virtual box** a la máquina para así conocer la dirección IP, la de red y la Gateway para asignar en las configuraciones el retorno del comando es simplemente el nombre de la interfaz y el estado de la misma **(UP)** pero no la IP. Además este mismo problema también se experimenta desde otra máquina, en este caso una **distro Kali** habilitada en la misma red para poder comprobar si se le asignaba IP y tampoco fue posible*. **Estado de las pruebas**: *NO Funciona*.

- **Con la configuración Host-only**: *pendiente de probar*

## Durante la instalación.

- Si la instalación se realiza con acceso a **internet** he sufrio en algunos de los intentos el error siguiente.

:::warning
Install had a problem. Please see /root/sosetup.log for details.
A summary of errors can be found in /root/errors.log.
Press Ok to exit. 
::::

Para solucionar este problema no queda otra que revisar el log mencionado, no obstante pueden ser un **problema grave** *como los relacionados con la creación de los microservicios de docker* o algo tan liviano como que algún *contenedor no se ha inicializado correctamente* y simplemente se tiene que lanzar.



