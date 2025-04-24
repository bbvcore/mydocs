---
sidebar_position: 1
title: Elastic Serch y Kibana
---
# ElasticSearch y Kibana
Para comenzar a trabajar con el **Stack de Elastic** es necesario seguir una secuencia de instalación correcta, por ello se ha de comenzar con **Elasticsearch** y luego continuar con **Kibana**.

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
estos enrollment tokens son los siguientes:

- Token expirado
- Seguridad activa de elastic search pero Kibana no
- Problema para reconocer certificados auto generados, para ello se usa
  **--insecure** o **-k** con curl.

## Kibana

### Token para instalar Kibana

Generar un token justo antes de instalar Kibana, justo antes porque posee un tiempo útil de 30 minutos.
```
sudo /usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana
```
Si se produce un error tipo **"exit 69"** o **"problemas de cluster"** hay que comprobar que **elasticsearch** está correctamente habilitado y activo.
```
sudo systemctl status elasticsearch
sudo systemctl enable elasticsearch
sudo systemctl start elasticsearch
```
### Instalar Kibana
1.  Ejecutar **setup** de *Kibana*. Previamente se **actualiza** también el *OS*.
```
sudo apt update && sudo apt install kibana
```

2.  Una vez instalado se obtiene una **KeyStore**.
```
Kibana KeyStore en /etc/kibana/kibana.keystore
```

3.  Ahora se configura **Kibana** con el token previamente obtenido.
```
sudo /usr/share/kibana/bin/kibana-setup --enrollment-token "pegar token"
```

4.  Si el proceso ha resultado satisfactorio se obtiene un mensaje de éxito.

```
Kibana configured successfully
    To start Kibana run:
    bin/kibana
```

:::tip[Ubicación Kibana]
 - /usr/share/kibana 
:::
 
5. Acceder via web
```
    localhost:5601
```
6.  Credenciales
```
    User: elastic
    Password: Generada en la instalación
```

## Posibles problemas durante el procedimiento
En todo proceso pueden suceder algunos problemas, los más destacados relacionados con este software son los siguientes.

### Kibana
1.  Si falla el acceso a kibana comprobar que está activo
```
    enable kibana
    start kibana
```

2.  Si falla reiniciar Kibana y revisar logs
```
sudo sistemctl restart kibana
sudo journalctl -u kibana -f
```

### ElasticSearch

1.  Obtener información sobre la instalación
```
sudo nano /etc/elasticsearch/elasticsearch.yml

    cluster.name: my-elastic-cluster  # Nombre del cluster
    node.name: my-parrot-node        # Nombre del nodo
    network.host: 0.0.0.0            # Escuchar en todas las interfaces (ajustar según necesidades)
    discovery.type: single-node      # Modo single-node (Solo 1 servidor)
```

2.  Problemas de activación de la aplicación
```
sudo systemctl enable elasticsearch
sudo systemctl start elasticsearch
```
3.  Problemas con password de inicio
```
sudo cat /var/lib/elasticsearch initial_master_nodes.password
```
4.  Comprobar acceso Comprobar el acceso desde la terminal y conseguir
    de retorno el JSON con la información
```
curl -u elastic:TUPASSWORD -X GET "https://localhost:9200" --insecure
```

5.  Cambiar contraseña (opcional)

```
curl -u elastic:TUPASSWORD -X POST "https://localhost:9200/_security/user/elastic/_password?pretty" -H "Content-Type: application/json" -d '{"password": "nuevopassword"}' --insecure
```

6.  Certificados y confianza
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

7.  Problemas con el **cortafuegos** en **GNU/Linux**.
```
sudo ufw allow 9200/tcp
sudo ufw allow 9300/tcp
sudo ufw reload
sudo ufw allow 9200 # problemas ufw
```

8.  Comprobación de los **logs** en tiempo real
```
sudo journalctl -u elasticsearch -f
```

9.  Comprobar el **estado de salud** de *elastic*
```
curl -u elastic:TUPASSWORD -X GET "https://localhost:9200/_cluster/health?pretty" --insecure
```

10. Ajustar la memoria
```
sudo nano /etc/elasticsearch/jvm.options 
```