---
title: Arkime
---
# Arkime
Arkime es una herramienta desarrollada para el **análisis de la red** y **captura de paquetes**, además es una solución Open Source.

Mediante una interfaz web se trabaja con las trazas PCAP estándar obtenidas, además mediante el uso de una **API** permite descargar y consumir datos directamente tanto en formato **JSON** como **PCAP**.

Mientras otras herramientas de analisis de tráfico como **Wireshark** se centran más en análisis locales en **Arkime** los análisis son de una dimensión más amplia y usados también 

## &#x1F9E9; Componentes 

Arkime posee **tres componentes** base en su arquitectura:
- **init**: se ejecuta solo cuando se configuras Arkime o se realizan modificaciones importantes.
```bash
sudo /opt/arkime/db/db.pl http://localhost:9200 init
```
- **capture**: realiza la captura de los datos a través de la interfaz específicada.
```bash
sudo /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini
```
- **viewer**: permite la visualización de los datos.
```bash
sudo node /opt/arkime/viewer/viewer.js -c /opt/arkime/etc/config.ini
```


## &#x1F4E5; Instalación 

###  Pasos previos
#### &#x1F501;  Actualización
```bash
sudo apt update 
sudo apt upgrade -y
```

#### &#x1F4E6; Dependencias
```bash
sudo apt install -y wget curl libpcap-dev libglib2.0-dev \
libmagic-dev uuid-dev cmake build-essential pkg-config \
libcurl4-openssl-dev zlib1g-dev python3 python3-pip \
apt-transport-https gnupg lsb-release
```
### &#x1F517; Instalación de elastic search 8.x 

#### &#x27A1; Repositorio y claves GPG
```bash
curl -fsSL https://artifacts.elastic.co/GPG-KEY-elasticsearch | sudo gpg --dearmor -o /usr/share/keyrings/elastic-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/elastic-keyring.gpg] https://artifacts.elastic.co/packages/8.x/apt stable main" | \
sudo tee /etc/apt/sources.list.d/elastic-8.x.list
sudo apt update
```
```bash
sudo apt install elasticsearch
systemctl enable elasticsearch
systemctl start elasticsearch
systemctl status elasticsearch
```

<details>
<summary>
Datos de acceso a elastic search
</summary>

```bash 
--------------------------- Security autoconfiguration information -------------
-----------------

Authentication and authorization are enabled.
TLS for the transport and HTTP layers is enabled and configured.

The generated password for the elastic built-in superuser is : E7lVN*nXOYUbRQ**s
kyu

If this node should join an existing cluster, you can reconfigure this with
'/usr/share/elasticsearch/bin/elasticsearch-reconfigure-node --enrollment-token 
<token-here>'
after creating an enrollment token on your existing cluster.

You can complete the following actions at any time:

Reset the password of the elastic built-in superuser with 
'/usr/share/elasticsearch/bin/elasticsearch-reset-password -u elastic'.

Generate an enrollment token for Kibana instances with 
 '/usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana'.

Generate an enrollment token for Elasticsearch nodes with 
'/usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s node'.

--------------------------------------------------------------------------------
-----------------
```
</details>

### &#x1F512; Deshabilitar TLS 

Para deshabilidar la seguridad **TLS** si hay problemas de acceso, en **elasticsearch** es necesario editar el siguiente fichero
```bash
sudo nano /etc/elasticsearch/elasticsearch.yml
xpack.security.enabled: false
xpack.security.transport.ssl.enabled: false
```
:::warning[Comprobación de acceso]
Para comprobar que funciona correctamente se ha de acceder la siguiente URL
```bash
curl http://localhost:9200
curl -s http://127.0.0.1:9200/_cluster/health?pretty
```
:::

### &#x1F4E5; Instalación de Arkime
#### Descarga de Arkime
```bash
wget https://github.com/arkime/arkime/releases/download/v5.6.4/arkime_5.6.4-1.ubuntu2204_amd64.deb
sudo apt install ./arkime_5.6.4-1.ubuntu2204_amd64.deb
```

#### Paquetes necesarios
En el Script están añadidos, pero si se hace a mano hacen falta añadir los siguientes paquetes.
```bash
sudo apt update
sudo apt install -y meson ninja-build build-essential \
    libpcap-dev libmagic-dev zlib1g-dev libssl-dev \
    pkg-config
```

#### &#x27A1; Script de instalación
```bash
#!/bin/bash
set -e # Si hay un error el script se detiene

# Configuración de variables
ARKIME_DIR="/opt/arkime"
ARKIME_REPO="https://github.com/arkime/arkime.git"
BRANCH="main"
NODE_VERSION="20.19.0"  
NODE_DIST="node-v$NODE_VERSION-linux-x64"
NODE_URL="https://nodejs.org/dist/v$NODE_VERSION/$NODE_DIST.tar.xz"

# Dependencias necesarias
echo "Realizando la instalación de paquetes necesarios..."
apt update
apt install -y \
  build-essential git curl wget \
  libssl-dev libpcap-dev libmagic-dev \
  zlib1g-dev libffi-dev \
  libyaml-dev libmaxminddb-dev \
  libcurl4-openssl-dev \
  pkg-config python3 python3-pip \
  libidn2-0-dev liblua5.3-dev \
  libcap-dev libnetfilter-queue-dev \
  brotli libbrotli-dev libnghttp2-dev \
  libpcre3-dev liblz4-dev \
   meson ninja-build

# 2. Clonando Arkime del repositorio
echo "Comenzando la clonación de Arkime..."
mkdir -p "$ARKIME_DIR"
cd "$ARKIME_DIR"
if [ ! -d "$ARKIME_DIR/arkime" ]; then
  git clone "$ARKIME_REPO"
fi
cd arkime
git fetch
git checkout "$BRANCH"

# 3. Instalación de NodeJS
echo "Comenzando la instalación de Node.js $NODE_VERSION..."
cd "$ARKIME_DIR/arkime"
mkdir -p node
cd node
wget -q "$NODE_URL"
tar -xf "$NODE_DIST.tar.xz"
ln -sf "$PWD/$NODE_DIST/bin/node" /usr/local/bin/node
ln -sf "$PWD/$NODE_DIST/bin/npm" /usr/local/bin/npm
ln -sf "$PWD/$NODE_DIST/bin/npx" /usr/local/bin/npx

# 4. Compilando Arkime
echo "Realizando la compilación de Arkime..."
cd "$ARKIME_DIR/arkime"
./easybutton-build.sh

# 5. Instalando y configurando
echo "Instalación de Arkime..."
make install
make config

echo "OK, se ha instalado Arkime correctamente. Fichero de configuración en /opt/arkime/etc/config.ini"
echo " Comandos de inicialización, captura y visualización "
echo "   sudo /opt/arkime/db/db.pl http://localhost:9200 init"  # Igual hace falta https
echo "   sudo /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini"
echo "   sudo /opt/arkime/bin/viewer -c /opt/arkime/etc/config.ini"

```
#### &#x2699; Configuración previa a su lanzamiento (init)
```bash
 sudo /opt/arkime/db/db.pl http://localhost:9200 init"
 sudo -E /opt/arkime/db/db.pl https://localhost:9200 init
It is STRONGLY recommended that you stop ALL Arkime captures and viewers before proceeding.  Use 'db.pl https://localhost:9200 backup' to backup db first.

There is 1 OpenSearch/Elasticsearch data node, if you expect more please fix first before proceeding.

This is a fresh Arkime install
Erasing
Creating
Finished
 ```
Aquí se especifica una clave secreta usada para encriptar, la interfaz de red a utilizar y los datos de elasticsearch.
```bash
- user: elastic
- password: E7lVN*nXOYUbRQ**skyu
```


### &#x1F4F8; Capture (bin/capture) 

La instalación realizada dió muchos problemas entonces no tiene habilitada la captura activa, pero si pasiva, mediante la opción **offline**.

Entonces de esta forma se puede analizar el tráfico pasándole los ficheros **PCAP** directamente
```bash
sudo /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini -r <fileName.pcap> # Fichero individual
sudo /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini -R </DirectoryCaps> # Directorio de capturas
```
#### &#x1F4F8; &#x23F0;Captura en tiempo real
Hay problemas con permisos para escribir en el directorio raw, solucionados con el siguiente comando
```bash
sudo setcap cap_net_raw,cap_net_admin=eip /opt/arkime/bin/capture
```
&#x27A1; **Lanzamiento de la captura**
```bash
admin@admin-cross:/opt/arkime/viewer$ /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini
```
&#x27A1; **Funcionando la captura**
```bash
root@admin-cross:/opt/arkime/viewer# sudo /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini
Jul 31 10:14:08 main.c:263 parse_args(): WARNING: gethostname doesn't return a fully qualified name and getdomainname failed, this may cause issues when viewing pcaps, use the --host option - admin-cross
Jul 31 10:14:08 http.c:1114 arkime_http_create_server(): WARNING - Using insecure mode for https://localhost:9200
Jul 31 10:14:08 http.c:318 arkime_http_send_sync(): 1/1 SYNC 200 https://localhost:9200/_template/arkime_sessions3_template?filter_path=**._meta 0/96 0ms 13ms
Jul 31 10:14:08 http.c:318 arkime_http_send_sync(): 1/1 SYNC 200 https://localhost:9200/arkime_sequence/_doc/fn-admin-cross 0/114 0ms 3ms
Jul 31 10:14:08 http.c:318 arkime_http_send_sync(): 1/1 SYNC 200 https://localhost:9200/arkime_sequence/_doc/fn-admin-cross 2/168 0ms 7ms
Jul 31 10:14:08 http.c:318 arkime_http_send_sync(): 1/1 SYNC 200 https://localhost:9200/arkime_stats/_doc/admin-cross 0/913 0ms 2ms
```



### &#x1F441; Viewer (bin/view)

#### &#x2795;&#x1F464; Crear usuario para el **viewer**
```bash
sudo /opt/arkime/bin/arkime_add_user.sh admin Admin123 --admin
```
#### &#x2705; &#x1F464;Comprobar usuario del **viewer**
```bash
curl -u elastic:'E7lVN*nXOYUbRQ**skyu' -k https://localhost:9200/arkime_users/_search?q=_id:admin
{"took":26,"timed_out":false,"_shards":{"total":1,"successful":1,"skipped":0,"failed":0},"hits":{"total":{"value":1,"relation":"eq"},"max_score":1.0,"hits":[{"_index":"arkime_users_v30","_id":"admin","_score":1.0,"_source":{"userId":"admin","userName":"Admin123","passStore":"0302aafa27923a0c09cc39e0fd9b5c10.08513b24be7cbaf0d9fd73323e48330fc8f057fd3f690a9292c92dda2c7b5fc5c0d07ed2c9177691a99cebe31a7ef3ce","enabled":true,"webEnabled":true,"headerAuthEnabled":false,"emailSearch":false,"removeEnabled":false,"packetSearch":false,"welcomeMsgNum":0,"settings":{},"roles":["arkimeUser","cont3xtUser","parliamentUser","wiseUser"],"createEnabled":false,"lastUsed":1753874813351}}]}}
```
#### &#x1F5D1; &#x1F464;Eliminar usuario
```bash
curl -X DELETE -u elastic:'E7lVN*nXOYUbRQ**skyu' -k "https://localhost:9200/arkime_users_v30/_doc/admin"
{"_index":"arkime_users_v30","_id":"admin","_version":3,"result":"deleted","_shards":{"total":1,"successful":1,"failed":0},"_seq_no":2,"_primary_term":1}
```

#### &#x1F4CB; Datos del fichero de configuración /opt/arkime/etc/config.ini
```bash
elasticsearchTrustCert=true
elasticsearch=https://localhost:9200
elasticsearchBasicAuth=elastic:E7lVN*nXOYUbRQ**skyu
authMode=basic
basicAuthPasswordMethod=sha256
```
#### &#x23FB; Inicializar el viewer
&#x27A1; **Path absoluto**
```bash
sudo node /opt/arkime/viewer/viewer.js -c /opt/arkime/etc/config.ini
```
:::[Path ejecución del Viewer]
**The viewer app MUST be run from inside the viewer directory**
:::


&#x27A1; **Path relativo**
```bash
admin@admin-cross:/opt/arkime/arkime/viewer$ sudo node viewer.js -c /opt/arkime/etc/config.ini
WARNING - Using authMode=digest since not set, add to config file to silence this warning.
WARNING - No cronQueries=true found in /opt/arkime/etc/config.ini, one and only one node MUST have cronQueries=true set for cron/hunts to work
WARNING
WARNING - No users are defined, use `/opt/arkime/bin/arkime_add_user.sh` to add one
WARNING
/opt/arkime/arkime/viewer/viewer.js listening on host :: port 8005 in development mode
Wed, 30 Jul 2025 11:23:24 GMT - GET / 401 - bytes 18.983 ms
AUTH: User elastic doesn't exist
Wed, 30 Jul 2025 11:24:36 GMT - GET / 401 - bytes 31.115 ms
AUTH: User elastic doesn't exist
Wed, 30 Jul 2025 11:24:43 GMT - GET / 401 - bytes 4.838 ms
Wed, 30 Jul 2025 11:24:46 GMT - GET / 401 - bytes 17.944 ms
AUTH: User elastic doesn't exist
Wed, 30 Jul 2025 11:24:59 GMT - GET / 401 - bytes 4.310 ms
```

#### &#x1F310; Acceso web 
Se produce mediante la siguiente URL: http://localhost:8005/sessions?date=1

:::danger[descomentar]
Es necesario sí o sí que al menos un nodo tenga la opción para que Arkime funcione correctamente con tareas programadas internas, como pueden ser las búsquedas periódicas y hunts.
Arrancar sin cronQueries=true hace que el nodo no esté completamente funcional y puede provocar comportamientos extraños en la aplicación, incluyendo el login.
:::


## &#x1F9EA; Tests
### Comprobación Elastic
Se ejecuta el siguiente comando pasando las credenciales del usuario de elastic y aplicando el parámetro -k para evitar problemas por seguridad y encriptación.
```bash
$ curl -u elastic:E7lVN*nXOYUbRQ**skyu -X GET https://localhost:9200/_cluster/health -k
```
Resultado del comando
```bash
{"cluster_name":"elasticsearch","status":"green","timed_out":false,"number_of_nodes":1,"number_of_data_nodes":1,"active_primary_shards":19,"active_shards":19,"relocating_shards":0,"initializing_shards":0,"unassigned_shards":0,"unassigned_primary_shards":0,"delayed_unassigned_shards":0,"number_of_pending_tasks":0,"number_of_in_flight_fetch":0,"task_max_waiting_in_queue_millis":0,"active_shards_percent_as_number":100.0}
```
Comprobación de todos los usuarios
```bash
curl -u elastic:E7lVN*nXOYUbRQ**skyu -X GET https://localhost:9200/arkime_users/_search -k | jq
```

### &#x1F464; Resetar users 

#### &#x1F5D1; &#x1F464; Borrar admin viejo
```bash
curl -X DELETE 'http://localhost:9200/arkime_users/_doc/admin'
```
#### &#x2795;&#x1F464;Añadir nuevo
Importante crearlo con el **script** de **Arkime** para que sea creado correctamente el **passStore** que genera una contraseña cifrada con su propio algoritmo y no con bcrypt o sha256.
```bash
sudo /opt/arkime/bin/arkime_add_user.sh admin "Admin User" admin
```
#### &#x2705; &#x1F464; Comprobar
```bash
curl -X POST 'http://localhost:9200/_aliases' -H 'Content-Type: application/json' -d '
{
  "actions": [
    {
      "add": {
        "index": "arkime_users_v30",
        "alias": "arkime_users"
      }
    }
  ]
}'
```
#### &#x2795;&#x1F512; Añadir seguridad
/opt/arkime/bin/arkime_add_user.sh admin "Admin User" nuevaPassword
:::warning[Problemas Pass]
- Campos importantes:
```
userId: <NameUser> y enabled: true.
```
:::