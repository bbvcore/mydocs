---
title: InfluxDB 3
---

# InfluxDB 3

## Descarga de la web
De la siguiente URL se procede a descargar los binarios adecuado al OS
```html
https://docs.influxdata.com/influxdb3/enterprise/install/
```
Escoger la versión enterprise
Requiere de un email para activar

### Opción descarga y script
```bash
curl -O https://www.influxdata.com/d/install_influxdb3.sh \
&& sh install_influxdb3.sh enterprise
```
Este proceso finaliza con la instalación de influxdb3, para ello hay que escoger si será una instalación simple o un contenedor de docker, en este caso he escogido la opción simple, quedando influxdb3 instalado en el siguiente path.
```bash
/home/userName/.influxdb/influxdb3
```
Tanto esta posibilidad como con Docker dieron problemas al contrario que la opción de los binarios.

### Comando
Una vez terminada la instalación es necesario instalar el comando que indique el proceso al finalizar, es un comando con source.

## Lanzar influxdb
### En sistemas GNU/Linux
Requiere del siguiente comando 
```bash
influxdb3 serve
```
:::tip[Atributos comando influxdb3]
    --node-id: A string identifier that distinguishes individual server instances within the cluster. This forms the final part of the storage path: <CONFIGURED_PATH>/<CLUSTER_ID>/<NODE_ID>. In a multi-node setup, this ID is used to reference specific nodes.

    --cluster-id: A string identifier that determines part of the storage path hierarchy. All nodes within the same cluster share this identifier. The storage path follows the pattern <CONFIGURED_PATH>/<CLUSTER_ID>/<NODE_ID>. In a multi-node setup, this ID is used to reference the entire cluster.

    --object-store: Specifies the type of object store to use. InfluxDB supports the following:
        file: local file system
        memory: in memory (no object persistence)
        memory-throttled: like memory but with latency and throughput that somewhat resembles a cloud-based object store
        s3: AWS S3 and S3-compatible services like Ceph or Minio
        google: Google Cloud Storage
        azure: Azure Blob Storage

    Other object store parameters depending on the selected object-store type. For example, if you use s3, you must provide the bucket name and credentials.
:::

└──╼ $sudo ./influxdb3 serve --node-id host01 --object-store file --data-dir ~/.influxdb3 --cluster-id cluster01
Catalog initialized with uuid: '2b1a2431-64e1-4bf9-94ae-ade37a5eef3f' and storage hash: 'sha256:aTbmcdXYBe-wT-Fo8N_iRg9mQPA_zJnYQR1gQBKDd-Q'

## Ayuda
```bash
influxdb3 serve --help
```


## Acceso interfaz web
Genera un problema por falta de token al acceder a la url localhost en el puerto 8181
2025-09-01T11:56:57.237083Z ERROR influxdb3_server::http: cannot authenticate token e=MissingToken

## Crear un token
### Desde la CLI de GNU/Linux
```bash
influxdb3 create token --admin
```
```bash
┌─[✗]─[borja@parrot]─[~/influxdb3-enterprise-3.4.1]
└──╼ $sudo ./influxdb3 create token --admin

New token created successfully!

Token: apiv3_hQ0EFvk15YD2V_VEHuNLH8UNmbeX7zjWD1fcUt-GneyxZnDW311BlIQeWLtjeQVqCpCGAltp-iITw3Qry9rqnA
HTTP Requests Header: Authorization: Bearer apiv3_hQ0EFvk15YD2V_VEHuNLH8UNmbeX7zjWD1fcUt-GneyxZnDW311BlIQeWLtjeQVqCpCGAltp-iITw3Qry9rqnA

IMPORTANT: Store this token securely, as it will not be shown again.
```

### Desde CMD en Windows
#### Comprobación del estado del servidor
Se comprueba el despliegue de InfluxDB3 y se obtiene el procedimiento para el adecuado lanzamiento.
```cmd
C:\Users\BorjaBasVentín\Downloads\influxdb3-core-3.4.1-windows_amd64>influxdb3 serve --help
Run the InfluxDB 3 Core server

Examples
  # Run with local file storage:
  1. influxdb3 serve --node-id node1 --object-store file --data-dir ~/.influxdb_data
  2. influxdb3 create token --admin
  3. Write and query with unhashed token

  # Run with AWS S3:
  1. influxdb3 serve --node-id node1 --object-store s3 --bucket influxdb-data \
    --aws-access-key-id KEY --aws-secret-access-key SECRET
  2. influxdb3 create token --admin
  3. Write and query with unhashed token
```

#### Lanzamiento de InfluxDB y creación de Nodo
Se crea un nodo y un sistema de almacenamiento de los datos
```cmd
C:\Users\BorjaBasVentín\Downloads\influxdb3-core-3.4.1-windows_amd64>.\influxdb3.exe serve --object-store file --node-id node1 --data-dir "C:\influxdb3\data"
2025-09-03T07:17:03.304520Z  INFO influxdb3_lib::commands::serve: InfluxDB 3 Core server starting node_id=node1 git_hash=7617104990a8e2ca4944571cb1dc75bf3e229eba version=3.4.1 uuid=bab9a93c-e4fc-49db-ac18-7fd10f7eccfc num_cpus=20
2025-09-03T07:17:03.304796Z  INFO influxdb3_clap_blocks::object_store: Object Store db_dir="C:\\influxdb3\\data" object_store_type="Directory"
```
#### Generación de Token en CMD
```bash
C:\Users\BorjaBasVentín\Downloads\influxdb3-core-3.4.1-windows_amd64>influxdb3 create token --admin

New token created successfully!

Token: apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q
HTTP Requests Header: Authorization: Bearer apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q

IMPORTANT: Store this token securely, as it will not be shown again.
```




### Desde un contenedor docker
```bash
docker exec -it CONTAINER_NAME influxdb3 create token --admin
```


### Exportar token
```bash
export INFLUXDB3_AUTH_TOKEN=YOUR_AUTH_TOKEN
```
## Gestión a través API
### Consultar Bases de datos
```bash
┌─[✗]─[trabajo@parrot]─[~/influxdb3-enterprise-3.4.1]
└──╼ $sudo ./influxdb3 show databases --token  apiv3_hQ0EFvk15YD2V_VEHuNLH8UNmbeX7zjWD1fcUt-GneyxZnDW311BlIQeWLtjeQVqCpCGAltp-iITw3Qry9rqnA
+---------------+
| iox::database |
+---------------+
| _internal     |
+---------------+
```
### Crear DB
```bash
└──╼ $sudo ./influxdb3 create database basDB  --token  apiv3_hQ0EFvk15YD2V_VEHuNLH8UNmbeX7zjWD1fcUt-GneyxZnDW311BlIQeWLtjeQVqCpCGAltp-iITw3Qry9rqnA
Database "basDB" created successfully
```

```cmd
C:\Users\BorjaBasVentín\Downloads\influxdb3-core-3.4.1-windows_amd64>influxdb3 create database basDB --token apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q
Database "basDB" created successfully
```


### Escribir DB
Para insertar datos hay que respetar la siguiente secuencia.
```bash
nameTable,¹tag1=value,tag2=value² fieldset="v1",fied2=v2³ timestamp
```
:::tip
- 1: primera coma
- 2: primer espacio en blanco
- 3: segundo espacio en blanco
:::

```bash
┌─[✗]─[borja@parrot]─[~/influxdb3-enterprise-3.4.1]
└──╼ $sudo ./influxdb3 write --database basDB  --token  apiv3_hQ0EFvk15YD2V_VEHuNLH8UNmbeX7zjWD1fcUt-GneyxZnDW311BlIQeWLtjeQVqCpCGAltp-iITw3Qry9rqnA --precision ns "cpu,name=server01 temperature=40.6,voltaje=5"
success
```

```cmd
C:\Users\BorjaBasVentín\Downloads\influxdb3-core-3.4.1-windows_amd64>influxdb3 write --database basDB --token apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q --precision ns "cpu,name=server01 temperature=40.6,voltaje=5"
success
```

También se puede escribir desde un fichero en vez de escribir los registros en la línea de comandos
```bash
influxdb3 write \
  --database DATABASE_NAME \
  --token TOKEN \
  --precision s \ 
  --accept-partial \
  --file path/data.file 
  ```
Los métodos para escribir datos en la inserción de la base de datos pueden ser la API HTTP (endpoint /api/v3/write_lp), las librerías de clientes de InfluxDB (nodejs, python...) y telegraf.

#### Usando la API HTTP para insertar
:::warning
Opción con API nativa, usando endpoint /write** puede fallar por el mapeo del bucket a la base de datos, cosa que gestiona muy bien el comando en CLI, pero en API HTTP no, y se requiere específicar el bucket para la inserción. En la CLI cuando se crea una base datos se crea un bucket automático con --database.
:::

```bash
└─$ curl -X POST "http://10.255.255.174:8181/api/v3/write_lp?db=basDB&precision=nanosecond"   -H "Authorization: Bearer apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q"   -H "Content-Type: text/plain; charset=utf-8"   --data-raw "cpu,name=server01 temperature=90.6,voltaje=5"
```

### Query DB
```bash
┌─[borja@parrot]─[~/influxdb3-enterprise-3.4.1]
└──╼ $sudo ./influxdb3 query --host http://localhost:8181  --database basDB  --token  apiv3_hQ0EFvk15YD2V_VEHuNLH8UNmbeX7zjWD1fcUt-GneyxZnDW311BlIQeWLtjeQVqCpCGAltp-iITw3Qry9rqnA "SELECT * FROM cpu"
+----------+-------------+-------------------------------+---------+
| name     | temperature | time                          | voltaje |
+----------+-------------+-------------------------------+---------+
| server01 | 40.6        | 2025-09-01T12:15:26.318525578 | 5.0     |
+----------+-------------+-------------------------------+---------+
```

```cmd
C:\Users\BorjaBasVentín\Downloads\influxdb3-core-3.4.1-windows_amd64>influxdb3 query --database basDB --token apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q  "select * from cpu ORDER BY time DESC LIMIT 5"
+----------+-------------+-------------------------------+---------+
| name     | temperature | time                          | voltaje |
+----------+-------------+-------------------------------+---------+
| server01 | 90.6        | 2025-09-02T12:04:45.286480    | 5.0     |
| server01 | 80.6        | 2025-09-02T12:04:15.908230100 | 5.0     |
| server01 | 80.6        | 2025-09-02T11:43:07.431872900 | 5.0     |
| server01 | 40.6        | 2025-09-02T10:54:25.599954900 | 5.0     |
+----------+-------------+-------------------------------+---------+
```

#### Query con la API
:::tip[API V3]
El endpoint de la API para las Query esta en: /api/v3/query_sql
:::
```bash
┌──(kali㉿PC-1160322)-[/mnt/c/Users/BorjaBasVentín]
└─$ curl -G "http://10.255.255.174:8181/api/v3/query_sql" \
  -H "Authorization: Bearer apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q" \
  --data-urlencode "db=basDB" \
  --data-urlencode "q=SELECT * FROM cpu"
[{"name":"server01","temperature":40.6,"time":"2025-09-02T10:54:25.599954900","voltaje":5.0}]
```
:::warning[Parámetro G]
El parámetro -G indica que se devuelvan los datos urlencode como query params en la URL
:::
Se ha de usar este parámetro G y no -X GET porque la API no espera un JSON en el body sino parámetros codificados en la consulta, por ello no se usa -X GET, de esta forma se convierte los data en data-urlencode.

## Gestión token en variables del OS (Linux)
Se puede añadir al ~/.profile, al ~/.bashrc o al /etc/profile
```bash
# Ejemplo en /etc/profile
export INFLUXDB_TOKEN="TOKEN"
export INFLUXDB_HOST="http://localhost:8181"
```
Para el profile de usuario o las sesiones de bash del usuario se puede usar
```bash
echo 'export INFLUXDB_TOKEN="TOKEN"' >> ~/.bashrc #  o ~/.profile
echo 'export INFLUXDB_HOST="http://localhost:8181"' >> ~/.bashrc #  o ~/.profile
source ~/.bashrc # o ~/.profile
```


## Problemas con la virtualización (MV)
Con la virtualización hay problemas de instrucciones, entonces con estos comandos se realizan ciertas comprobaciones.
```bash
uname -m
ldd influxdb3
file influxdb3
```
Así se puede comporbar como existen problemas con Virtual Box y la experimentación de  problemas con las instrucciones AVX
```bash
admin@dabian-mint:~/influxdb3-enterprise-3.4.1$  grep -o -E 'sse4_2|avx|avx2' /proc/cpuinfo | sort -u 
sse4_2
```

## Tipos de datos permitidos
    
- String dictionary (tag)
- int64 (field)
- float64 (field)
- uint64 (field)
- bool (field)
- string (field)
- time (time with nanosecond precision)

## Línea de protocolo
table: A string that identifies the table to store the data in.

tag set: Comma-delimited list of key value pairs, each representing a tag. Tag keys and values are unquoted strings. Spaces, commas, and equal characters must be escaped.

* field set: Comma-delimited list of key value pairs, each representing a field. Field keys are unquoted strings. Spaces and commas must be escaped. Field values can be one of the following types:

    strings (quoted)
    floats
    integers
    unsigned integers
    booleans

timestamp: Unix timestamp associated with the data. InfluxDB supports up to nanosecond precision

### Ejemplo
```bash
home,room=Living\ Room temp=21.1,hum=35.9,co=0i 1756713600
```

## Comandos relevantes
```bashq

write / w → insertar datos
query / q → consultar datos
create → crear recursos (por ejemplo, base de datos)
show → listar recursos (como bases de datos y tablas)
```

## Conceptos
La base de datos se corresponde con el bucket y la tabla al measurement
