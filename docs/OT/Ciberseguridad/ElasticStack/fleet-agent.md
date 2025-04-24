---
sidebar_position: 2
title: Fleet y Elastic Agent
---
# Fleet y Elastic Agent
## Información Elastic Agent
Los **Elastic Agents** son agentes ligeros en el **Stack de Elastic** que sustituyen a los **Beats**.

:::info[Funciones principales]
- **Recolectar datos** *(logs, métricas, eventos de seguridad)*.
- **Enviarlos a ElasticSearch/Kibana**
- **Ejecutar integraciones preconfiguradas**
:::

## Información Fleet
Es una **herramienta centralizada** de *Kibana* para gestionar agentes *(Elastic Agents)* que recolectan datos.

:::info[Funciones]
- Administrar múltiples agentes de forma centralizada.
- Establecer las políticas de recolección de datos.
- Monitorización del estado de los agentes.
:::

### Estructura a lograr
Para el correcto funcionamiento de **Fleet** se requiere lograr una estructura funcional que es la siguiente:
- **Host**: *es el **host** donde se crea el elastic agent.*
- **Agent Policy**: requiere de **flet server policy**
- **Integrations**: aquí se añaden las integraciones necesarias para la obtención de datos, es importante que exista la **Fleet Server** para lograr la funcionalidad de una administración centralizada de los agentes.



## Aplicaciones prácicas
<details>
<summary>
Listado de aplicaciones prácticas posibles
</summary>

- **Agentes instalados en servidores que envian métricas del sistema**: *RAM, uso de la CPU*.
- Uso de **dahsboards** para ver esos datos.
- **Centralización** de los **logs** al ser indexados en elasticsearch.
- Permite **múltiples integraciones**.

</details>


## Configuración e instalación
Una vez se tiene instalados tanto **ElasticSearch** como **Kibana** se procede a configurar un **Elastic agent** en **Fleet**. 

:::info[Acceso Kibana]
- http://localhost:5601
:::

Por ello, hace falta **loguearse** en **Kibana** y acceder a la siguiente ruta a través del menú lateral accesible a través del icono hamburguesa.
```
Management > Fleet
```

### Add a Fleet Server
Una vez aquí se procede a **Add a Fleet Server** y para ello se usa la opción **Quick Start** creando una política nueva donde se han de especificar varios datos.

:::tip[Datos necesarios para la política]
- Nombre del host
- URL + Puerto (8220)
:::

Una vez creada la política esta será accesible desde la siguiente URL.
```
https://localhost:8220
```

:::warning[Ojo al protocolo]
El protocolo web al específicar la máquina con el puerto ha de ser **HTTPS**.
:::

Siempre que esté instalado en la misma máquina que **Fleet**, sino habría que poner la **IP** de la máquina donde esta instalado **Fleet**.

Una vez introducidos los datos se pulsa el botón de **Generate** y se obtendrá un **Token** y mostrará la configuración del Host y la ruta de acceso, que será la específicada anteriormente. Además se informa de que se podrán realizar ajustes en **Fleet Settings**.

## Instalación para la administración centralizada
Se recomienda instalar *Fleet Server* para **centralizar la administración** de los agentes, para ello procedemos a descargar el agente desde la shell mediante **CURL** apuntando a la **URL** *artifacts.elastic.con/downloads/beats/elastic-agent* y una vez obtenido el tarball se ejecutan los siguientes comandos que comprenden la instalación del mismo a través del correspondiente **script** y con varios **argumentos** como *la IP:puerto, el token o la política asignada*.

Una vez se han llevado todos estos pasos la shell pedirá la contraseña de **root** o del usuario con privilegios elevados para poder **instalar** el *agente* de **forma local** en la siguiente ruta.
```
/opt/Elastic/Agent
```
Una vez finalizada la instalación se recibe un mensaje del estado del proceso.
```
Elastic Agent has been succesfully installed.
```

### Posibles problemas
A veces el proceso no va tan automático y se queda con la obtención del tarball
```
tar -xzf elastic-agent-8.13.4-linux-x86_64.tar.gz
```
Entonces se descomprime y se accede a el directorio obtenido para ejecutar la instalación
```
sudo ./elastic-agent install \
  --url=https://<IP>:8220 \
  --enrollment-token=TOKEN_OBTENIDO_CON_KIBANA
```

## Acceso al agente instalado
!["Agentes instalados"](../Img/despliegues/fleet-2-agentes.png)

Una vez se ha instalado el agente de forma satisfactoría se puede acceder a el en la sección **Fleet > Agents**.
<details>
<summary>
Información relevante sobre el agente
</summary>

- **Status**: Healthy, Unhealthy, Updating, Offline, Inactive o Unenrolled.
- **Host**
- **Política del Agente**
- **Uso de CPU**
- **Uso de Memoría**
- **Última actividad**
- **Versión**

</details>


## Integraciones

!["Imagen con ejemplo de integraciones"](../Img/despliegues/fleet-server-policy-details.png)

Una vez establecida correctamente la instalación y configuración del agente, en la sección **Fleet** de **Kibana** se puede comprobar el **host** y su correspondiente **status** *(Healthy es el estado deseable)*.

En este caso se procede a las integraciones, por defecto es necesario tener la integración de **Fleet Server** y luego ya el resto de integraciones van en consonancia con la funcionalidad requerida y el objetivo trazado. Existen integraciones para Suricata, Nginx, MySQL, AWS, Azure, etc...



