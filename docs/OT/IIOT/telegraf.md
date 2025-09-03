---
sidebar_position: 1
title: Telegraf
---

# Telegraf 
## Instalación
```bash
sudo apt update && sudo apt upgrade -y # Actualización

wget -qO- https://repos.influxdata.com/influxdata-archive.key | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/influxdata.gpg # Descargar clave GPG

echo "deb [signed-by=/etc/apt/trusted.gpg.d/influxdata.gpg] https://repos.influxdata.com/debian bookworm stable" | sudo tee /etc/apt/sources.list.d/influxdata.list  # Añadir clave GPG


sudo apt install telegraf # Instalar telegraf

sudo systemctl enable telegraf # 
sudo systemctl start telegraf # 

systemctl status telegraf # Comprobar estado del servicio
```
## Comprobar los ficheros de configuración
Telegraf se puede configurar en el fichero /etc/telegraf.conf, pero también existe
un directorio telegraf.d para una funcionalidad modular. 
:::tip[Comprobación de ambas rutas en el servicio]
Para realizar la comprobación se usa el siguiente comando.
```bash
cat /lib/systemd/system/telegraf.service
```
:::



## Despliegue modular
Para el despliegue modular se aplica una configuración minimalista en el fichero **telegraf.conf** y dentro del directorio **conf.d** se alojarán ficheros de configuracón para la recepción de los datos de los sistemas mediante el uso de **agentes**.

### Fichero telegraf.d
<details>
<summary>
Fichero del agente
</summary>

```bash
[agent]
  interval = "10s"
  round_interval = true
  metric_batch_size = 1000
  metric_buffer_limit = 10000
  collection_jitter = "0s"
  flush_interval = "10s"
  flush_jitter = "0s"
  precision = ""
  hostname = "hist-db"
  omit_hostname = false
  debug = true
  logfile = ""

# Directorio que contiene las configuraciones modulares
# Se encarga de habilitar la carga de los ficheros alojados en `telegraf.d/*.conf`
[global_tags]

# Salidas (si quieres, puedes ponerlas aquí también o en .d/)
# [[outputs.influxdb_v2]]
#    urls = ["http://localhost:8086"]
#    token = "tu-token"
#    organization = "tu-org"
#    bucket = "mi-bucket"
```
</details>

### Fichero mqtt.confls
<details>
<summary>
Fichero de configuración para el protocolo MQTT
</summary>

```bash
[[inputs.mqtt_consumer]]
  servers = ["tcp://192.168.56.106:1883"]
  topics = ["/sensores/#"]
  qos = 0
  data_format = "json"
```
</details>

### Fichero influxdb.conf
<details>
<summary>
Fichero de configuración para la salida de los datos hacía InfluxDB
</summary>

```bash
[[outputs.influxdb_v2]]
  urls = ["http://localhost:8086"]
  token = "Añadir el Token de InfluxDB"
  organization = "Añadir la organización"
  bucket = "Añadir el bucket"
```
</details>

### Fichero system.conf
<details>
<summary>
Fichero de configuración de los datos del sistema.
</summary>

```bash
[[inputs.cpu]]
  percpu = true
  totalcpu = true
  collect_cpu_time = false
  report_active = false

[[inputs.mem]]
[[inputs.disk]]
[[inputs.diskio]]
[[inputs.processes]]
[[inputs.system]]
```

:::warning[Revisar permisos de Usuario]
En este fichero hay que tener en cuenta los permisos del usuario que ejecuta el agente dado que puede haber problemas para acceder a ciertos datos.
:::
</details>

## Chuleta de comandos para Telegraf
```bash
telegraf --config /etc/telegraf/telegraf.conf --test
```
```bash
telegraf --config /etc/telegraf/telegraf.conf --debug
```
```bash
sudo systemctl restart telegraf
```
```bash
journalctl -u telegraf -f
```
```bash
sudo systemctl status telegraf
```



## Opción compatible con telegraf.conf

Configuración de **telegraf** para almacenar en **conf.d** en compatibilidad con el fichero 
**telegraf.conf**.

<details>
<summary>
Fichero de configuración
</summary>

```bash
[agent]
  interval = "5s"
  debug = true

[[outputs.file]]
  files = ["stdout"]
  data_format = "influx"

[[inputs.mqtt_consumer]]
  servers = ["tcp://192.168.56.106:1883"]
  topics = ["#"]
  data_format = "json"
  topic_tag = "topic"
```
</details>