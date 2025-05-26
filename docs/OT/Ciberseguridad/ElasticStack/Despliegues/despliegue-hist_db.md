---
sidebar_position: 2
title: Despliegue Hist_db
---
# Despliegue Hist_db
Esta máquina esta desplegada sobre un OS Gnu/Linux Ubuntu con los servicios de Grafana e InfluxDB (junto Telegraf).

## Grafana
### Requisitos previos de instalación
```
sudo apt-get install -y apt-transport-https software-properties-common wget
```
### Clave GPG
```
sudo mkdir -p /etc/apt/keyrings/
wget -q -O - https://apt.grafana.com/gpg.key | gpg --dearmor | sudo tee /etc/apt/keyrings/grafana.gpg > /dev/null
```
#### Añadir repositorio
```
echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list
```
### Actualizar
```
sudo apt update
```
### Instalación
```
sudo apt-get install grafana
```
## Acceso a Grafana
Grafana esta accesible desde el navegador web en el puerto 3000, sus credenciales son admin/admin y en el primer acceso pide un cambio de password.
:::tip
- Acceso como proceso desde un script
```
sudo .\grafana server
```
- Acceso como servicio
```
systemctl enable grafana-server
systemctl active grafana-server
```

:::

## InfluxDb
```
sudo apt install influxdb2
```
### Telegraf
Dentro de telegraf se ha de establecer una configuración para el protocolo MQTT.

Se puede configurar de varias formas:
- Desde el fichero de configuración
```
/etc/telegraf/telegraf.conf
``
Accediendo a las secciones **inputs.mqtt_consumer** y **outputs.influxdb_v2** del fichero de configuración donde se ajustarán valores como: servers, topic, qos en la primera sección y en la segunda sección se configuran valores como: servers, token, organization y bucket. Como opcional, según las necesidades, se puede dejar sin utilizar los valores de las credenciales username/password.

- Desde la interfaz web de InfluxDB en la sección **Load Data**.