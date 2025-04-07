---
sidebar_position: 2
title: Fleet y Elastic Agent
---
# Fleet y Elastic Agent
## Información Elastic Agent
Los Elastic Agents son agentes ligeros en el Stack de Elastic que sustituyen a Beat.

:::info[Funciones principales]
- **Recolectar datos** *(logs, métricas, eventos de seguridad)*.
- **Enviarlos a ElasticSearch/Kibana**
- **Ejecutar integraciones preconfiguradas**
:::

## Información Fleet
Es una herramienta centralizada de Kibana para gestionar agentes *(Elastic Agents)* que recolectan datos.
:::info[Funciones]
- Administrar múltiples agentes de forma centralizada.
- Establecer las políticas de recolección de datos.
- Monitorización del estado de los agentes.
:::

## Aplicaciones pŕacicas
<details>
<summary>
Listado de aplicaciones pŕacticas posibles
</summary>

- Agentes instalados en servidores envian métricas del sistema: RAM, uso de la CPU.
- Uso de dahsboards para ver esos datos.
- Centralización de los logs al ser indexados en elasticsearch.
- Permite múltiples integraciones

</details>


## Configuración e instalación
Una vez se tiene instalados tanto **ElasticSearch** como **Kibana** toca configurar un **Elastic agent** en **Fleet**. 

:::info[Acceso Kibana]
- http://localhost:5601
:::

Para ello hace falta loguearse en Kibana y acceder a la siguiente ruta a través del menú lateral accesible a través del icono hamburguesa.
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
El protocolo al específicar la máquina con el puerto ha de ser **HTTPS**.
:::

Siempre que esté instalado en la misma máquina que **Fleet**, sino habría que poner la **IP** de la máquina donde esta instalado **Fleet**.

Una vez introducidos los datos se pulsa el botón de **Generate** y se obtendrá un **Token** y mostrará la configuración del Host y la ruta de acceso, que será la específicada anteriormente.

Además se informa de que se podrán realizar ajustes en **Fleet Settings**.

## Instalación para la administración centralizada
Se recomienda instalar Fleet Server para centralizar la administración de los agentes, para ello procedemos a descargar el agente desde la shell mediante CURL apuntando a la URL **artifacts.elastic.con/downloads/beats/elastic-agent** y una vez obtenido el tarball se ejecutan los siguientes comandos que comprenden la instalación del mismo a través del correspondiente script y con varios argumentos como la IP:puerto, el token o la política asignada.

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
Una vez se ha instalado el agente de forma satisfactoría se puede acceder a el en la sección **Fleet > Agents**.
<details>
<summary>
Información relevante sobre el agente
</summary>

- Status: Healthy, Unhealthy, Updating, Offline, Inactive o Un
- Host
- Política del Agente
- Uso de CPU
- Uso de Memoría
- Última actividad
- Versión

</details>


