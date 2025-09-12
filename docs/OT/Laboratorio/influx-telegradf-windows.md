---
title: Práctica Influxdb3 en Windows
---

# InfluxDB, Telegraf y Grafana en Windows
La obtención de **Influx** se realiza a través de la descarga de los **binarios** de la página web. 

## InfluxDB 
### Uso en sistemas Windows
Al ser ejecutado desde unos binarios no hay un servicio lanzado de forma automática entonces se ha de inicializar con el siguiente comando.

### Creación / lanzamiento
```powershell
.\influxdb3.exe serve --object-store file --node-id node1 --data-dir ".\data-influxdb-storage" --cluster-id cluster-01
```

### Token 
Para poder interaccionar desde la **CLI** mediante el **protocolo en línea** es necesario obtener un **token** con *privilegios para el usuario administrador*, para ello se ejecuta el siguiente comando.

```powershell
influxdb3 create token --admin

Token: apiv3_DpL_GZWjqn47MT-RXRxdszxooa51CMHspyAu5eHnyPH7zOnN3j8exyU-WSbXLEG6nK-lKfoUfZ5ECyUuBdv1mg
HTTP Requests Header: Authorization: Bearer apiv3_DpL_GZWjqn47MT-RXRxdszxooa51CMHspyAu5eHnyPH7zOnN3j8exyU-WSbXLEG6nK-lKfoUfZ5ECyUuBdv1mg
```

### Creación de una base de datos
Para crear una base de datos se utiliza el siguiente comando
```powershell
influxdb3 create database influxDB --token apiv3_DpL_GZWjqn47MT-RXRxdszxooa51CMHspyAu5eHnyPH7zOnN3j8exyU-WSbXLEG6nK-lKfoUfZ5ECyUuBdv1mg
```

### Consulta bases datos
influxdb3 show databases --token apiv3_DpL_GZWjqn47MT-RXRxdszxooa51CMHspyAu5eHnyPH7zOnN3j8exyU-WSbXLEG6nK-lKfoUfZ5ECyUuBdv1mg

### Consulta de las tablas

### Consulta datos de tablas



:::warning[Non-Sucker Server Manager]
Para la creación de un servicio en sistemas operativos Windows y de esta forma que el propio InfluxDB3 se levante con cada inicio del OS se va a usar la aplicación NSSM.
### Lanzamiento de la APP
```powershell
nssm install influxdb3
```
### Configuración
Una vez lanzada se han de rellenar 3 inputs: el path, los argumentos y el directorio de arranque.
### Lanzamiento del servicio
```powershell
nssm start influxdb3
```
### Comprobación del servicio
```powershell
PS C:\Windows\system32> get-process influxdb3

Handles  NPM(K)    PM(K)      WS(K)     CPU(s)     Id  SI ProcessName
-------  ------    -----      -----     ------     --  -- -----------
    153      11    13660      22832       0,08   3952   0 influxdb3
```
:::



## Telegraf
### Descarga
Para conseguir telegraf para usar junto InfluxDB3 se requiere de su descarga desde la siguiente URL.
```html
https://www.influxdata.com/downloads/
```
:::tip[Path Telegraf]
Habitualmente está accesible desde la siguiente ruta.
```powershell
 C:\Program Files\InfluxData\telegraf\telegraf-1.35.4>
```
:::

### Configuración de plugins
Se puede configurar el conjunto de plugins en el fichero de configuración telegraf.conf, pero en este caso se va a aplicar la modularidad, para ello se crea un directorio telegraf.d y dentro del mismo se colocaran los ficheros de input y output.

#### Fichero de input
```powershell
# system.conf
[[inputs.cpu]]
  percpu = true
  totalcpu = true
  collect_cpu_time = false
  report_active = true

[[inputs.mem]]

[[inputs.disk]]
  # Ignorar sistemas de archivos típicos de Linux que no existen en Windows
  ignore_fs = ["tmpfs", "devtmpfs"]

[[inputs.system]]
```

#### Fichero de output
En este caso se va a usar el protocolo en línea y por ello se almacenarán las métricas en un fichero llamado metics.pl.
```powershell
[[outputs.file]]
  files = ["C:\\Program Files\\InfluxData\\telegraf\\metrics.lp"]
  data_format = "influx"
```

##### Comprobación de los ficheros input
```powershell
.\telegraf.exe --config "C:\Program Files\InfluxData\Telegraf\telegraf.conf" --test
```
### Ejecución 
```powershell
.\telegraf.exe --config-directory "C:\Program Files\InfluxData\telegraf\telegraf-1.35.4\telegraf.d"
```
#### Fichero metrics.lp
En el fichero se puede comprobar el almacenamiento de las métricas
```powershell
system,host=DESKTOP-8LR0L2R load1=0,load5=0,load15=0,n_cpus=4i 1757588370000000000
system,host=DESKTOP-8LR0L2R uptime=2681i 1757588370000000000
system,host=DESKTOP-8LR0L2R uptime_format=" 0:44" 1757588370000000000
mem,host=DESKTOP-8LR0L2R used=2623168512i,used_percent=61.0821003356348,available_percent=38.9178996643652,total=4294496256i,available=1671327744i 1757588370000000000
disk,device=C:,fstype=NTFS,host=DESKTOP-8LR0L2R,mode=rw,path=\C: inodes_used_percent=0,total=53044621312i,free=23435309056i,used=29609312256i,used_percent=55.819631705621475,inodes_total=0i,inodes_free=0i,inodes_used=0i 1757588370000000000
disk,device=D:,fstype=CDFS,host=DESKTOP-8LR0L2R,mode=ro,path=\D: free=0i,used=60225536i,used_percent=100,inodes_total=0i,inodes_free=0i,inodes_used=0i,inodes_used_percent=0,total=60225536i 1757588370000000000
```








