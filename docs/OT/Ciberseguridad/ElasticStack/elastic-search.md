---
sidebar_position: 1
title: Elastic Serch 
---
# ElasticSearch 
Para comenzar a trabajar con el **Stack de Elastic** es necesario seguir una secuencia de instalación correcta, por ello se ha de comenzar con **Elasticsearch**.

## ElasticSearch

### Preparación del sistema
Antes de comenzar con su instalación como es habitual conviene actualizar el OS
```
sudo apt update && sudo apt upgrade -y
```
Una vez actualizado el sistema operativo se procede a instalar **Java** ya que es necesario como base de la suite **ELK**.
```
sudo apt install openjdk-17-jdk -y
```

### Descarga de elasticsearch

**Elasticsearch** se puede descargar de varias formas, pero en este caso la opción escogida es por **terminal**, para llevar a cabo esta descarga de forma segura es necesaria obtener la **clave pública GPG**.
```
wget -qO - https://artifacts.elastic.co/GPG-KEY-elasticsearch | sudo gpg --dearmor -o /usr/share/keyrings/elasticsearch-keyring.gpg
```
Una vez obtenida la **clave GPG** se procede a añadir el repositorio externo para la descarga de **elasticsearch** a los repositorios del OS.
```
echo "deb [signed-by=/usr/share/keyrings/elasticsearch-keyring.gpg] https://artifacts.elastic.co/packages/8.x/apt stable main" | sudo tee /etc/apt/sources.list.d/elastic-8.x.list
```

### Instalación de elasticsearch

Una vez configurados los repositorios se procede a **actualizar el OS** y a realizar la instalación de **elasticsearch**.

:::warning[Path de instalación]
Es importante instalar en la siguiente ruta.
```
/opt/elastic/agent/data/
```
:::

```
sudo apt update 
sudo apt install elasticsearch -y
```

#### Resultado instalación
:::warning[Atención a la consola durante la instalación]
Una vez realizada la instalación es muy importante prestar atención al resultado recibido por consola, ya que se proporciona una contraseña.
:::

<details>
<summary>
Información de seguridad importante en la salida por consola al finalizar la instalación
</summary>

```
Authentication and authorization are enabled. **TLS** for the transport
and **HTTP layers** is enabled and configured.

The **generated password** for the elastic built-in **superuser** is:
**J3q11Z4lUB7Vv8f5ioMh**

If this node should join an existing cluster, you can reconfigure this
with *'/usr/share/elasticsearch/bin/elasticsearch-reconfigure-node
--enrollment-token "token-here"'* after creating an enrollment token on
your existing cluster.

You can complete the following actions at any time:

**Reset the password** of the elastic built-in **superuser** with
*'/usr/share/elasticsearch/bin/elasticsearch-reset-password -u
elastic'*.

**Generate an enrollment token** for **Kibana instances** with
*'/usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s
kibana'*.

**Generate an enrollment token** for **Elasticsearch nodes** with
*'/usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s
node'*.
```

</details>

:::warning[Versión 8.x]

A partir de **Elasticsearch 8.x** se activa seguridad por defecto *(TLS + Autenticación)*.
- **Autenticación obligatoria**: elastic *(como superadmin)*
- **Comunicación cifrada SSL/TLS** *(certificados auto generados)* 
- **Enrollment tokens**: *para conectar **Kibana** o nuevosnodos al cluster*. 
:::

<details>
<summary>
Gestión de las contraseñas en <b>ELK</b>
</summary>

La **contraseña inicial** de **elasticsearch** se almacena en la siguiente ruta.
```
var/lib/elasticsearch/initial_master_nodes.password
```
En caso de perdida de la misma se puede generar una **nueva contraseña** con el siguiente comando.
```
sudo /usr/share/elasticsearch/bin/elasticsearch-reset-password -u elastic
```
</details>
<details>
<summary>
Enrollment tokens
</summary>

Los **enrollment tokens** son *tokens de duración temporal* para que
**Kibana** se pueda **unir** al *cluster de elasticsearch* de forma
segura, poseen un **tiempo de vida** de **30 minutos**.

Su mayor ventaja es la facilidad para integrar elascticsearch y kibana
sin tener que usar certificados de forma manual.


- **Creación de un enrollment token para un user Kibana**
```
sudo /usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana
```

- **Creación de un enrollment tolen para conectar nuevos nodos adicionales**
```
sudo /usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana
```
</details>

Los **enrollment tokens** son la **mejor solución** cuando se instala
**Kibana** en un entorno **ElasticSearch** *y no se quiere complicar la
configuración a través de Certificados SSL*, el uso de credenciales
*(usuario / contraseña)* de elasticsearch teniendo que editar el fichero
*kibana.yml*.

Los problemas que pueden surgir para establecer la conexión utilizando
estos **enrollment tokens** son los siguientes:

- Token expirado
- Seguridad activa de **elastic search** pero Kibana no
- Problema para reconocer certificados auto generados, para ello se usa
  **--insecure** o **-k** con curl.

  
### Soluciones de problemas

#### Obtener información sobre la instalación
```
sudo nano /etc/elasticsearch/elasticsearch.yml

    cluster.name: my-elastic-cluster  # Nombre del cluster
    node.name: my-parrot-node        # Nombre del nodo
    network.host: 0.0.0.0            # Escuchar en todas las interfaces (ajustar según necesidades)
    discovery.type: single-node      # Modo single-node (Solo 1 servidor)
```

#### Problemas de activación de la aplicación
```
sudo systemctl enable elasticsearch
sudo systemctl start elasticsearch
```
####  Problemas con password de inicio
```
sudo cat /var/lib/elasticsearch initial_master_nodes.password
```
####  Comprobar acceso Comprobar el acceso desde la terminal y conseguir
    de retorno el JSON con la información
```
curl -u elastic:TUPASSWORD -X GET "https://localhost:9200" --insecure
```

####  Cambiar contraseña (opcional)

```
curl -u elastic:TUPASSWORD -X POST "https://localhost:9200/_security/user/elastic/_password?pretty" -H "Content-Type: application/json" -d '{"password": "nuevopassword"}' --insecure
```

#### Certificados y confianza
Los certificados autogenerados **TLS** sealmacenan en el **path** de elasticsearch.

```
/etc/elasticsearch/certs
```

Kibana y otros servicios deben de **confiar** en estos **certificados**,
se ajustan las rutas en **kibana.yml**. Si siguen dando problemas una
solución temporal consiste en **desactivar** en *elasticsearch.yml* la
*seguridad*.
```
xpack.security.enabled: false
```

####  Problemas con el **cortafuegos** en **GNU/Linux**.
```
sudo ufw allow 9200/tcp
sudo ufw allow 9300/tcp
sudo ufw reload
sudo ufw allow 9200 # problemas ufw
```

####  Comprobación de los **logs** en tiempo real
```
sudo journalctl -u elasticsearch -f
```

####  Comprobar el **estado de salud** de *elastic*
```
curl -u elastic:TUPASSWORD -X GET "https://localhost:9200/_cluster/health?pretty" --insecure
```

#### Ajustar la memoria
```
sudo nano /etc/elasticsearch/jvm.options 
```
