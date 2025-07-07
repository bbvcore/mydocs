---
sidebar_position: 1
title: Podman
---


# Podman
Se trata de un gestor de contenedores open source similar a Docker, de hecho aprovecha los mismos comandos y la misma estructura para generar imagenes, volumenes y contenedores 

## Casos de uso
## Desde la terminal de comandos
#### Creación de un contenedor desde la terminal
Se procede a crear un contenedor para node-red, mapeando el puerto 1880, descargando la imagen de docker.io y generando persistencia en el directorio /var/tmp/docker-containers.
 
```bash
$sudo podman run -d   -p 1880:1880   -v /var/tmp/docker-containers/node-red/data:/data   --name nodered   docker.io/nodered/node-red
Trying to pull docker.io/nodered/node-red:la
```

### Comprobación de los contenedores en ejecución
```bash
└──╼ $podman ps
CONTAINER ID  IMAGE                              COMMAND     CREATED        STATUS            PORTS                   NAMES
6768253abc0a  docker.io/nodered/node-red:latest              2 minutes ago  Up 2 minutes ago  0.0.0.0:1880->1880/tcp  nodered
```
:::tip[Más detalles]
Para obtener más detalles de los contenedores se puede usar el siguiente comando.
```bash
sudo podman container list --all
```
:::

#### Otros comandos interesantes
**Comprobar logs**
```bash
podman logs nodered
```

**Eliminar**
El comando por defecto para eliminar es **rm**, para imágenes también se puede usar **rmi** y para eliminar todos los contenedores y no uno a uno se puede usar **prune**.
```bash
podman rm name
podman rm id
podman container prune 
```

## A partir de una imagen personalizada
### Crear imagen con Dockerfile
Para crear una imagen propia se hace uso del fichero **Dockerfile**, el cual especificará las características de la nueva imagen.

<details>
<summary>
Contenido del Dockerfile
</summary>

```bash
# Construir imagen usando de base la oficial
FROM nodered/node-red:latest

# Instalar nodos extras
#RUN npm install \
#    node-red-contrib-mqtt \
#    node-red-node-mongodb \
#    node-red-contrib-mysql \
#    node-red-contrib-influxdb

# Exposición del puerto 1880 
EXPOSE 1880

# Comando inicial al lanzar el contenedor CMD ["exec", "param1", "param2", "param n"]
# De base se lanza node
# De parámetro se lanza red.js que se encarga de cargar los módulos
# procesar settings.js, arrancar componentes, cargar web server y escuchar el 1880
CMD ["node", "/usr/src/node-red/red.js"]
```
</details>


:::note[Características del Dockefile]
- **Nombre del fichero**: el fichero siempre se ha de llamar **Dockerfile**.
- **Creación de la imagen**:
```bash
podman build -t tag-imagen .
```
:::

### Comprobación de la imagen creada
```bash
└──╼ $sudo podman image ls
REPOSITORY                  TAG         IMAGE ID      CREATED        SIZE
localhost/nodered           latest      2f98b8b7765d  4 minutes ago  620 MB
```
#### Desplegando desde la terminal la imagen creada
Una vez se ha creado la imagen se procede a desplegar el contenedor.
```bash
sudo podman run -d -p 1880:1880 -v /var/tmp/docker-containers/node-red/data:/data --name nodered localhost/nodered:latest
```

#### Desplegando con podman-compose
Se crea un fichero **Yaml** con las características necesarias para el despligue del contenedor de la imagen creada.

```bash
version: '3.8'

services:
  nodered:
    image: localhost/nodered:latest
    container_name: nodered
    ports:
      - "1880:1880"
    volumes:
      - /var/tmp/docker-containers/node-red/data:/data
    restart: always
    networks:
      - basix-network

networks:
  basix-network:
    driver: bridge
```

En docker se usaba el fichero docker-compose, en podman el fichero se renombra a podman-compose pero se despliega de la misma forma que en docker.

<b>Instalación de podman-compose</b>

Se puede instalar de varias formas, a través de APT o de PIP.

```bash
sudo pip3 install podman-compose
sudo apt install podman-compose
```
Se comprueba la versión descargada y así también se certifica que la instalación se realizó correctamente.
```bash
podman-compose --version
```

<b>Despligue y cancelación</b>

Con **up** se despliega el contenedor con la imagen creada y con **down** se finaliza el mismo.

```bash
sudo podman-compose up -d
sudo podman-compose down
```
<b>Ejemplo del despliegue</b>

```bash
└──╼ $sudo podman-compose  up -d
podman-compose version: 1.0.6
['podman', '--version', '']
using podman version: 4.3.1
** excluding:  set()
['podman', 'ps', '--filter', 'label=io.podman.compose.project=node-red', '-a', '--format', '{{ index .Labels "io.podman.compose.config-hash"}}']

...

7e61a7d6ef7c0ec5b7b5522195724c116c5881fe537adb20eafb84fe09e62606
exit code: 0
```


## Extras para el fichero YAML
Añadir contenedores con las imágenes de repositorio al fichero YAML para desplegar también Grafana e InfluxDB.

```bash
  influxdb:
    image: influxdb:latest
    container_name: influxdb
    ports:
      - "8086:8086"
    volumes:
      - /var/tmp/influxdb:/var/lib/influxdb
    restart: always
    networks:
      - basix-network

  grafana:
    image: grafana/grafana:latest
    container_name: grafana
    ports:
      - "3000:3000"
    restart: always
    networks:
      - basix-network
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=admin  # Cambia la contraseña por defecto si es necesario

networks:
  basix-network:
    driver: bridge

```


