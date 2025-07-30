---
title: Arkime
---
# Arkime
Arkime es una herramienta desarrollada para el **análisis de la red** y **captura de paquetes**, además es una solución Open Source.

Mediante una interfaz web se trabaja con las trazas PCAP estándar obtenidas, además mediante el uso de una **API** permite descargar y consumir datos directamente tanto en formato **JSON** como **PCAP**.

Mientras otras herramientas de analisis de tráfico como **Wireshark** se centran más en análisis locales en **Arkime** los análisis son de una dimensión más amplia y usados también 

## Instalación
### Pasos previos
#### Actualización
```bash
sudo apt update 
sudo apt upgrade -y
```

#### Dependencias
```bash
sudo apt install -y wget curl libpcap-dev libglib2.0-dev \
libmagic-dev uuid-dev cmake build-essential pkg-config \
libcurl4-openssl-dev zlib1g-dev python3 python3-pip \
apt-transport-https gnupg lsb-release
```
### Instalación de elastic search 8.x
#### Repositorio y claves GPG
```bash
curl -fsSL https://artifacts.elastic.co/GPG-KEY-elasticsearch | sudo gpg --dearmor -o /usr/share/keyrings/elastic-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/elastic-keyring.gpg] https://artifacts.elastic.co/packages/8.x/apt stable main" | \
sudo tee /etc/apt/sources.list.d/elastic-8.x.list
sudo apt update
```
```bash
sudo apt install elasticsearch
systemctl enable elasticsearch
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

### Deshabilitar TLS
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
```
:::

### Instalación de Arkime
#### Descarga de Arkime
```bash
wget https://github.com/arkime/arkime/releases/download/v5.6.4/arkime_5.6.4-1.ubuntu2204_amd64.deb
sudo apt install ./arkime_5.6.4-1.ubuntu2204_amd64.deb
```

#### Script de instalación
```bash
#!/bin/bash
set -e

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
  libpcre3-dev liblz4-dev

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
echo "   sudo /opt/arkime/db/db.pl http://localhost:9200 init"
echo "   sudo /opt/arkime/bin/capture -c /opt/arkime/etc/config.ini"
echo "   sudo /opt/arkime/bin/viewer -c /opt/arkime/etc/config.ini"

```
#### Configuración previa a su lanzamiento (init)
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


### Capture (bin/capture)





### Viewer (bin/view)

#### Crear usuario para el **viewer**
```bash
sudo /opt/arkime/bin/arkime_add_user.sh admin Admin123 --admin
```
#### Comprobar usuario del **viewer**
```bash
curl -u elastic:'E7lVN*nXOYUbRQ**skyu' -k https://localhost:9200/arkime_users/_search?q=_id:admin
{"took":26,"timed_out":false,"_shards":{"total":1,"successful":1,"skipped":0,"failed":0},"hits":{"total":{"value":1,"relation":"eq"},"max_score":1.0,"hits":[{"_index":"arkime_users_v30","_id":"admin","_score":1.0,"_source":{"userId":"admin","userName":"Admin123","passStore":"0302aafa27923a0c09cc39e0fd9b5c10.08513b24be7cbaf0d9fd73323e48330fc8f057fd3f690a9292c92dda2c7b5fc5c0d07ed2c9177691a99cebe31a7ef3ce","enabled":true,"webEnabled":true,"headerAuthEnabled":false,"emailSearch":false,"removeEnabled":false,"packetSearch":false,"welcomeMsgNum":0,"settings":{},"roles":["arkimeUser","cont3xtUser","parliamentUser","wiseUser"],"createEnabled":false,"lastUsed":1753874813351}}]}}
```
#### Eliminar usuario
```bash
curl -X DELETE -u elastic:'E7lVN*nXOYUbRQ**skyu' -k "https://localhost:9200/arkime_users_v30/_doc/admin"
{"_index":"arkime_users_v30","_id":"admin","_version":3,"result":"deleted","_shards":{"total":1,"successful":1,"failed":0},"_seq_no":2,"_primary_term":1}
```

#### Datos del fichero de configuración /opt/arkime/etc/config.ini
```bash
elasticsearchTrustCert=true
elasticsearch=https://localhost:9200
elasticsearchBasicAuth=elastic:E7lVN*nXOYUbRQ**skyu
authMode=basic
basicAuthPasswordMethod=sha256
```
#### Inicializar el viewer
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

#### Acceso web 
Se produce mediante la siguiente URL: http://localhost:8005/sessions?date=1

:::danger[descomentar]
Es necesario sí o sí que al menos un nodo tenga la opción para que Arkime funcione correctamente con tareas programadas internas, como pueden ser las búsquedas periódicas y hunts.
Arrancar sin cronQueries=true hace que el nodo no esté completamente funcional y puede provocar comportamientos extraños en la aplicación, incluyendo el login.
:::

