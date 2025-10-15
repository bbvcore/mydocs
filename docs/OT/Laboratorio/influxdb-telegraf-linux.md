---
title: Influx, Telegraf y Grafana en GNU/Linux
---

# Práctica Influxdb3 en GNU/Linux
Esta es una aplicación que utilizará InfluxDB3, telegraf y grafana.

## InfluxDB
### Instalación y despliegue
Se lleva a cabo la descarga de los binarios necesarios desde la página web oficial, para más información leer la entrada correspondiente en esta documentación: [Instalación, configuración y despliegue de InfluxDB3](../IIOT/influxDB3-nativo.md).



## Telegraf
### Instalación y despliegue
Para instalar telegraf es necesario obtener la clave GPG y añadir el repositorio a la lista de repositorios, para consultar el procedimiento acudir a: [Instalación, configuración y despliegue de Telegraf](../IIOT/telegraf.md).

<details>
<summary>
Resumen breve de los pasos necesarios
</summary>

- **Importar la clave GPG**
```bash
wget -qO- https://repos.influxdata.com/influxdata-archive_compat.key | sudo gpg --dearmor -o /usr/share/keyrings/influxdata-archive-keyring.gpg
```

- **Añadir repositorio**
```bash
echo "deb [signed-by=/usr/share/keyrings/influxdata-archive-keyring.gpg] https://repos.influxdata.com/debian stable main" | sudo tee /etc/apt/sources.list.d/influxdata.list
```

- **Actualizar e instalar**
```bash
sudo apt update
sudo apt install telegraf -y
```

- **Servicio**
```bash
sudo systemctl enable telegraf
sudo systemctl start telegraf
```

</details>


En este caso concreto se dejará sin tocar el *fichero de configuración base* en **/etc/telegraf.conf** y se usará el *directorio para ficheros modulares* **/etc/telegraf/telegraf.d.**

:::tip[Consulta ficheros de configuración que carga Telegraf]
```bash
sudo nano /lib/systemd/system/telegraf.service
```
:::

#### Fichero input
<details>
<summary>
Fichero de configuración para obtener las métricas de sistema: <b>system.conf</b>.
</summary>

- <b>System.conf</b>
```bash
[[inputs.cpu]]
  percpu = true
  totalcpu = true
  collect_cpu_time = false
  report_active = true

[[inputs.mem]]

[[inputs.disk]]
  ignore_fs = ["tmpfs", "devtmpfs", "overlay"]

[[inputs.system]]
```
</details>

#### Fichero output
<details>
<summary>
Fichero de salida para inyectar en influx las métricas del sistema: <b>uotput.conf</b>.
</summary>

- <b>System.conf</b>
```bash
[[outputs.file]]
  files = ["/tmp/telegraf_metrics.lp"]
  data_format = "influx"
```

</details>

:::warning[Problemas con los ficheros de configuración]
- Si hay problemas con los ficheros de configuración es conveniente matizar las rutas para cargarlos correctamente.
```bash
sudo telegraf --config /etc/telegraf/telegraf.conf --config-directory /etc/telegraf/telegraf.d
```
- Pruebas y testeo de los los ficheros
```bash
telegraf --config-directory /etc/telegraf/telegraf.d --test
```
- Editar el servicio
```bash
sudo systemctl edit telegraf
```
- Prubeas de funcionamiento de Telegraf
```bash
telegraf --config </path/*.conf> --test
```
- Verificación del fichero telegraf
```bash
ls -l /tmp/telegraf_metrics.lp
head -n 10 /tmp/telegraf_metrics.lp
```
:::

## Inserción de datos (vía CLI) en InfluxDB
Una vez que se han obtenido las métricas del sistema con Telgraf se procede a insertarlas en la base de datos de InfluxDB3.

### Carga de 1 registro manual (Test)
Como prueba se puede realizar una insercción manual con un registro no real a modo de ejemplo, para comprobar la correcta inserción.
```bash
echo "cpu,host=parrot usage_idle=99" > /tmp/test_metrics.lp
./influxdb3 write --database telegrafDB \
  --token apiv3__X6I69COivovOniLvPiMkE0diBg1iVeIqQVYBjnIaKXAk3tXsOfUX1a2VI88BPHFtUkOY0h2DmEArue0xEeOfg\
  --precision s \
  --file /tmp/test_metrics.lp`
```
### Carga de valores almacenados en fichero
Para proceder a insertar los valores en InfluxDB se procede a realizar la inserción del fichero generado con Telegraf para las métricas en la base de datos previamente creada en InfluxDB3.

```bash
└──╼ $./influxdb3 write --database telegrafDB \
 --token apiv3__X6I69COivovOniLvPiMkE0diBg1iVeIqQVYBjnIaKXAk3tXsOfUX1a2VI88BPHFtUkOY0h2DmEArue0xEeOfg\
  --precision s \
  --file /tmp/telegraf_metrics.lp
success
```



