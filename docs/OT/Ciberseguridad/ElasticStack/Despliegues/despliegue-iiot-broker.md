---
sidebar_position: 3
title: Despliegue iiot-broker
---
# IIoT Broker
Máquina desplegada con el OS base de GNU/Linux Ubuntu y el establecimiento de un servidor Mosquitto que actua como servidor broker.

## Mosquitto
Se trata de un broker MQTT que utiliza el puerto estándar 1883 para ejercer de broker.
```
sudo apt update
sudo apt install mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
sudo systemctl status mosquitto
```
### Test sin clientes desde terminal
```
mosquitto_sub -t test
mosquitto_pub -t test -m "Hola desde el broker"
```
### Cortafuegos
```
sudo ufw allow 1883
```

## Ejemplo de uso
### Fichero de configuración anterior a la versión 2.0 
El fichero de configuración de Mosquitto está ubicado en /etc/mosquitto y se llama mosquitto.conf.
<details>
<summary>
Ejemplo de configuración para Mosquitto y un ESP32
</summary>

```
# File: mosquitto.conf
# Estado: Base del proyecto IIoT 

# Listener en el puerto por defecto para MQTT
listener 1883

# Dirección de escucha (0.0.0.0 - cualquier origen)
bind_address 0.0.0.0

# Desactivar autenticación y TLS 
allow_anonymous true
password_file /dev/null

# Logs para depuración
log_dest file /var/log/mosquitto/mosquitto.log
log_type error
log_type warning
log_type notice
log_type information

# Persistencia en las sesiones
persistence true
persistence_location /var/lib/mosquitto/

```
</details>



### Fichero de configuración versión 2.0 o superiores
Se comienza creando un fichero de configuración propio en la ruta /etc/mosquitto/mosquitto.d con el siguiente contenido.

```
# Listener en el puerto por defecto para MQTT
listener 1883
allow anonymous true
```

Mientras que se deja el fichero mosquitto.conf como esta por defecto, que incluye la persistencia, el log y el enlace al directorio de configuración. Se omite la línea
```
bind_address 0.0.0.0
```
Porque a partir de la versión 2.0 o superior no puede convivir con la siguiente línea
```
listener 1883
```
Es redundante, ya que al poner listerner 1883 ya permite, la versión 2.0 o superior, la conexión de cualquier IP a ese servicio.

### Ejemplo de testeo del fichero de configuración modificado en mv IIoT-broker
```
mosquitto_sub -h localhost -t "sensores/esp32/dht11" -v
mosquitto_pub -h localhost -t "sensores/esp32/dht11" -m '{"temp":22.5,"hum":58}'
```

### Ejemplo de JSON para el payload en Arduino para el ESP32
```
{
  "temperatura": 27.2,
  "humedad": 75,
  "dispositivo": "DHT-11",
  "localizacion": "office-primera-planta"
}
```

### En Telegraf
``` 
[[inputs.mqtt_consumer]]
  servers = ["tcp://IP_DEL_BROKER:1883"]
  topics = ["sensores/esp32/dht11"]
  qos = 0
  data_format = "json"
  json_string_fields = ["dispositivo", "localización"]
```
Tags: dispositivo, localización
Campos: temperatura y humedad

#### Test de Mosquitto a Telegraf
```
mosquitto_pub -h localhost -t "iot/esp32/dht11" -m '{"temperature": 23.5, "humidity": 60, "device": "esp32-dht11", "location": "salon"}'

```

#### Comprobación en Telegraf
```
influx query 'from(bucket: "nombre_del_bucket") |> range(start: -5m)'
```

