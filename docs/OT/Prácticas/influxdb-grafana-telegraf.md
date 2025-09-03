---
title: Aplicación IoT
---

# Aplicación IoT
Esta es una aplicación que utilizará InfluxDB3, telegraf y grafana.

## InfluxDB
### Instalación y despliegue
Se lleva a cabo la descarga de los binarios necesarios desde la página web oficial, para más información leer la entrada correspondiente en esta documentación: [Instalación, configuración y despliegue de InfluxDB3](../IIOT/influxDB3-nativo.md).


## Telegraf
### Instalación y despliegue
Para instalar telegraf es necesario obtener la clave GPG y añadir el repositorio a la lista de repositorios, para consultar el procedimiento acudir a: [Instalación, configuración y despliegue de Telegraf](../IIOT/telegraf.md).

En este caso concreto se dejará sin tocar el fichero de configuración base en /etc/telegraf.conf y se usará el directorio para ficheros modulares /etc/telegraf/telegraf.d.

:::tip[Consulta ficheros de configuración que carga Telegraf]
```bash
sudo nano /lib/systemd/system/telegraf.service
```
:::


#### Fichero cpu.conf
```bash
# Plugin para las  métricas de CPU
[[inputs.cpu]]
  percpu = true            # Métrica x  núcleo
  totalcpu = true          # Totales
  collect_cpu_time = false
  report_active = false

# Puglin para ver los datos en  consola
[[outputs.file]]
  files = ["stdout"]
  data_format = "influx"
```


#### Fichero outputs.conf
```bash 
[[outputs.file]]
  files = ["stdout"]
  data_format = "influx"
```
:::warning[Problemas con los ficheros de configuración]
Si hay problemas con los ficheros de configuración es conveniente cargarlos de la siguiente forma
```bash
sudo telegraf --config /etc/telegraf/telegraf.conf --config-directory /etc/telegraf/telegraf.d
```
:::


## Enviar datos a InfluxDB3
Para enviar datos a InfluxDB3 no se usa el plugin outpus.influxdb_v2 ni outputs.influxdb ya que el CLI usa el método de escritura con influxdb3 write, por ello es necesario usar [[outputs.exec]] y redirigir a un script de inserción.

### InfluxDB en mismo equipo que Telegraf
#### Fichero exec_output.conf
Esta opción funcionaría si estuviera todo en el mismo equipo. Requiere también de un scrip para realizar la inserción.
```bash
[[outputs.exec]]
  command = ["/usr/local/bin/telegraf-to-influx.sh"]
  data_format = "influx"
```
#### Script
```bash
#!/bin/bash
influx write \
  --host http://10.255.255.174:8181 \
  --database basDB \
  --token apiv3_V4DVNM2i0sHYYy-JpYXlOqOy2D1c-PZqphigqLyTIRZsndgafdrx1M51E5XQ_h2O43rv_iXyAEiI9pJyIHqZ6Q \
  --precision ns \
  --format line \
  --file -
```

### InfluxDB3 en distinto equipo 
:::tip[Token]
- Token: apiv3_wwp9ne4-2j7GlkkQzcVFHgXdfwrSEuiONa8jvjCYoVZS-ymzgpRn-KQuofm6L1sIMri2f-BxMY9GrdqWPThhrQ
- HTTP Requests Header: Authorization: Bearer apiv3_wwp9ne4-2j7GlkkQzcVFHgXdfwrSEuiONa8jvjCYoVZS-ymzgpRn-KQuofm6L1sIMri2f-BxMY9GrdqWPThhrQ
:::

#### Creación base de datos para la inserción
```cmd
influxdb3 create database telegrafDB --token apiv3_wwp9ne4-2j7GlkkQzcVFHgXdfwrSEuiONa8jvjCYoVZS-ymzgpRn-KQuofm6L1sIMri2f-BxMY9GrdqWPThhrQ
Database "telegrafDB" created successfully

influxdb3 show databases --token apiv3_wwp9ne4-2j7GlkkQzcVFHgXdfwrSEuiONa8jvjCYoVZS-ymzgpRn-KQuofm6L1sIMri2f-BxMY9GrdqWPThhrQ
+---------------+
| iox::database |
+---------------+
| _internal     |
| telegrafDB    |
+---------------+
```


Para poder insertar en un equipo distinto se utiliza el plugin outputs.http
```bash
[[outputs.http]]
  url = "http://10.255.255.174:8181/api/v2/write?db=telegrafDB&precision=ns"
  method = "POST"
  data_format = "influx"
  headers = { "Authorization" = "Bearer apiv3_wwp9ne4-2j7GlkkQzcVFHgXdfwrSEuiONa8jvjCYoVZS-ymzgpRn-KQuofm6L1sIMri2f-BxMY9GrdqWPThhrQ" }

```
Y se deben de recibir las métricas correctamente ya que mediante line protocol ya genera la serie, los campos, las etiquetas y asocia el timestamp automáticamente. Solo requiere de una base de datos y de un token con permiso de escritua. En este caso se generaría algo así:
Measurement	Campos típicos	Etiquetas comunes
cpu	usage_user, usage_system, usage_idle	cpu, host
mem	used, free, available, cached	host
disk	used_percent, free, total	device, path, host
system	uptime, load1, load5, load15	host


Se podría consultar a través de una sentencia SQL como la siguiente
```bash
SELECT * FROM cpu
```
### Consultar datos en la tabla
```cmd
curl -G "http://10.255.255.174:8181/api/v3/query_sql"   -H "Authorization: Bearer apiv3_wwp9ne4-2j7GlkkQzcVFHgXdfwrSEuiONa8jvjCYoVZS-ymzgpRn-KQuofm6L1sIMri2f-BxMY9GrdqWPThhrQ"   --data-urlencode "db=telegrafDB"   --data-urlencode "q=SHOW TABLES"
```


## Grafana


