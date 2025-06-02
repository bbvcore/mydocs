---
sidebar_position: 1
title: InfluxDB
---

# InfluxDB
```bash
curl -O https://www.influxdata.com/d/install_influxdb3.sh \
&& sh install_influxdb3.sh
```
Y se mostrará entonces un menú de instalación donde se podrá escoger si instalar en un contenedor Docker o sí se instala en el sistema operativo.

## Instalar Docker
Para poder instalar InfluxDB dockerizado hace falta evidentemente tener instalado Docker. 

:::tip[Descargas de Docker]
- <a href="https://docs.docker.com/engine/install/">Docker Engine</a>
- <a href="https://docs.docker.com/desktop/">Docker Desktop</a>
:::

Docker Engine es el propio motor de Docker, la capacidad de crear y gestionar contenedores, es capaz de llevar a cabo la mayoría de funciones y se ha de ejecutar desde la línea de comandos.

Por su parte Docker Desktop, incluye el Docker Engine, pero además posee herramientas adicionales como plugins, interfaz gráfica, etc... Es gratuito para cierto tipo de usos y para otros posee una versión de pago.


### Acceso instalación de InfluxDB3
#### Con script descargado
```
docker run -it -p 8181:8181 -v ./plugins:/plugins influxdb3-core influxdb3 serve --object-store memory --node-id node0 --plugin-dir /plugins
```
#### Otras opciones de ejecución con el script
```bash
# Opcion A, una imagen 
docker run -d \
  --name influxdb3 \
  -p 8086:8086 \
  -v influxdb3_data:/var/lib/influxdb3 \
  influxdb:3-core

# Opción B, otra imagen
docker run -d \
  --name influxdb3 \
  -p 8086:8086 \
  -v influxdb3_data:/var/lib/influxdb3 \
  influxdb3-core:latest
```

#### Sin script
```bash
docker pull influxdb:3-core

# Para arquitectura de PC de 64 bits
docker pull \
--platform linux/amd64 \
influxdb:3-core

```
### Con docker-compose
```bash
version: '3.8'
services:
  influxdb3:
    image: influxdb:3-core
    platform: linux/amd64
    ports:
      - "8086:8086"
    volumes:
      - influxdb3_data:/var/lib/influxdb3
    environment:
      - INFLUXD_SQLITE_DIR=/var/lib/influxdb3

volumes:
  influxdb3_data:

```

```bash
docker-compose up -d
```
:::tip[Puertos]
- **Puerto 8086**: *puerto tradicional para InfluxDB y su API HTTP para la comunicación con clientes como Telegraf.*

- **Puerto 8181**: *Es el puerto para desarrollo incorporado en InfluxDB (**backend IOx**)*
:::

## Modo producción
```bash
docker run -d \
  --name influxdb3 \
  -p 8086:8086 \
  -v influxdb3_data:/var/lib/influxdb3 \
  influxdb:3-core
```
## Modo desarrollo
```bash
  mkdir -p plugins && \
docker run -it \
  -p 8181:8181 \
  -v $(pwd)/plugins:/plugins \
  influxdb3-core \
  influxdb3 serve --object-store memory --node-id node0 --plugin-dir /plugins
```
### Docker Engine
#### Añadiendo la clave GPG de Docker
```bash
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
```
#### Añadiendo el repositorio a la lista de fuentes
```bash
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```
#### Realizando la instalación
```bash
# Realizando la instalación
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```
#### Comprobando la instalación
Para ver que todo ha salido perfectamente hay una comprobación con un contenedor de prueba llamado "Hello World"
```bash
sudo docker run hello-world
```
Si sale bien se verá un mensaje de texto asociado al contenido de esa imagen de docker ejecutada. También se puede consultar la lista de contenedores ejecutados para ver como se había ejecutado el contenedor hello-world.

```bash
sudo docker container ps -a
sudo docker image ls
```

