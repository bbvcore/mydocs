
// Contenedores
podman por docker o a la inversa 

// Contenedor node-red
 $sudo podman run -d   -p 1880:1880   -v /var/tmp/docker-containers/node-red/data:/data   --name nodered   docker.io/nodered/node-red
Trying to pull docker.io/nodered/node-red:la



// Comprobar contenedores
└──╼ $podman ps
CONTAINER ID  IMAGE                              COMMAND     CREATED        STATUS            PORTS                   NAMES
6768253abc0a  docker.io/nodered/node-red:latest              2 minutes ago  Up 2 minutes ago  0.0.0.0:1880->1880/tcp  nodered

Otro más detallado: sudo podman container list --all

// Comprobar logs
podman logs nodered

// Eliminar 
podman rm name
podman rm id
podman container prune // borra todos

// Crear imagen propia*******************************************************
// DockerFile ejecución
Dockerfile : nombre siempre fichero
podman build -t nodered-custom .
└──╼ $sudo podman image ls
REPOSITORY                  TAG         IMAGE ID      CREATED        SIZE
localhost/nodered           latest      2f98b8b7765d  4 minutes ago  620 MB

// Ahora lanzar la imagen creada
sudo podman run -d -p 1880:1880 -v /var/tmp/docker-containers/node-red/data:/data --name nodered localhost/nodered:latest

// Crear un despliegue docker-compose******************************************
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
      - nodered-network

networks:
  nodered-network:
    driver: bridge


En este caso podman-compose: 
sudo pip3 install podman-compose / apt install podman-compose
podman-compose --version


sudo podman-compose up -d
sudo podman-compose down


└──╼ $sudo podman-compose  up -d
podman-compose version: 1.0.6
['podman', '--version', '']
using podman version: 4.3.1
** excluding:  set()
['podman', 'ps', '--filter', 'label=io.podman.compose.project=node-red', '-a', '--format', '{{ index .Labels "io.podman.compose.config-hash"}}']
['podman', 'network', 'exists', 'node-red_nodered-network']
['podman', 'network', 'create', '--label', 'io.podman.compose.project=node-red', '--label', 'com.docker.compose.project=node-red', '--driver', 'bridge', 'node-red_nodered-network']
['podman', 'network', 'exists', 'node-red_nodered-network']
podman run --name=nodered -d --label io.podman.compose.config-hash=defe979e60f1595801c1776b50a7b46c2f05ed7bb2a93d4f61b105091d490a07 --label io.podman.compose.project=node-red --label io.podman.compose.version=1.0.6 --label PODMAN_SYSTEMD_UNIT=podman-compose@node-red.service --label com.docker.compose.project=node-red --label com.docker.compose.project.working_dir=/var/tmp/docker-containers/node-red --label com.docker.compose.project.config_files=podman-compose.yaml --label com.docker.compose.container-number=1 --label com.docker.compose.service=nodered -v /var/tmp/docker-containers/node-red/data:/data --net node-red_nodered-network --network-alias nodered -p 1880:1880 --restart always localhost/nodered:latest
7e61a7d6ef7c0ec5b7b5522195724c116c5881fe537adb20eafb84fe09e62606
exit code: 0




// Soporte extra en YAML para Grafana e InfluxDB
  influxdb:
    image: influxdb:latest
    container_name: influxdb
    ports:
      - "8086:8086"
    volumes:
      - /var/tmp/influxdb:/var/lib/influxdb
    restart: always
    networks:
      - nodered-network

  grafana:
    image: grafana/grafana:latest
    container_name: grafana
    ports:
      - "3000:3000"
    restart: always
    networks:
      - nodered-network
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=admin  # Cambia la contraseña por defecto si es necesario

networks:
  nodered-network:
    driver: bridge




