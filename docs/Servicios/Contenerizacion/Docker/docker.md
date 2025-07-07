---
sidebar_position: 1
title: Docker
---

# Docker
Es un software que permite la creación de contenedores para el despliegue de microservicios interconectados entre ellos a través de una red local. Esta implementación permite tener los servicios aislados y que los mantenimientos, errores o actualizaciones se mantengan focalizadas en espacios independientes que eviten daños colaterales.

## Pasos previos
1. Actualizar el sistema
```bash
sudo apt update
sudo apt upgrade -y
```
2. Paquetes
```bash
sudo apt install apt-transport-https ca-certificates curl software-properties-common -y
```
:::info[Paquetes]
- apt-transport-https: añade soporte para HTTPS a la gestión de paquetes que hace ATP.
- ca-certificates: incluye una colección de certificados de las autoridades reconocidos globalmente.
- curl: parquete para obtener la herramienta de transferencia de ficheros que soporta HTTP, HTTPS, FTP, FTSP, SCP, SFTP... Permite descargar ficheros, peticiones HTTP/HTTPS e incluir cabeceras personalizadas en las cabeceras.
- software-properties-common: permite gestionar los repositorios permitiendo utilizar  los PPA mediante la herramienta add-apt-repository.
:::


3. Añadir GPG

**GPG** es una herramienta de firma y cifrado basada en OpenGPG para verificar los datos como seguros.

:::note[Parámetros Curl]
- f: fallo silencioso, no muestra la respuesta del error.
- s: modo silencioso, no muestra información descarga.
- S: muestra errores si suceden en el proceso y esta activado el modo silencioso.
- L: sigue redireciones de ficheros.
:::

Se descarga la clave de docker.gpg y se almacena en un directorio temporal.
```bash
curl -fsSL https://download.docker.com/linux/ubuntu/gpg > /tmp/docker.gpg 
```

:::note[apt-key]
apt-key sirve para añadir, eliminar, explortar, listar y otras operaciones sobre claves.
:::
```bash
sudo apt-key add /tmp/docker.gpg
```


4. Añadir repositorio

Con el comando **add-apt-repository** se añade el repositorio como un fichero del directorio **/etc/apt/sources.list.d/**. De esta forma no se toca, como antaño, el fichero **sources.list**, sino que se genera uno específico por cada aplicación con el formato *"aplicacion.list"* y se almacena en el directorio **sources.list.d.**

```bash
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
```
:::tip[Linux Standard Base]
- El comando lsb_release muestra información específica sobre la versión de la distribución GNU/Linux en la que se está.
```bash
lsb_release --help
```
:::

5. Actualizar
```bash
sudo apt update
```

## Instalación 
1. Instalar docker
```bash
sudo apt install docker-ce -y
```
2. Comprobar el estado
```bash
sudo systemctl status docker
```
3. Habilitarlo
```bash
sudo systemctl enable docker
```

### Comandos básicos de Docker
#### Comprobar contenedores
```bash
docker ps 
```
#### Detener microservicios ejecutado en un contenedor
```bash
docker stop apache-container mysql-container phpmyadmin-container
```
#### Borrar contenedores, volumenes, imágenes y redes
```bash
docker rm <name-container>
docker network rm <name-network>
docker volume rm <name-volume>
docker image rm <name-image> o docker rmi <name-image>
```

## Implementaciones
### Desde la terminal

#### Creación de una Red
La red es necesaria para la interconexión de los diferentes microservicios asignados a cada contenedor creado.
```bash
docker network create ot
```
#### Contenedor para Apache
```bash
docker run -d \
  - -name apache-docker \
  - -network ot \
  -p 80:80 \
  -v $(pwd)/html:/usr/local/apache2/htdocs/ \
  httpd:latest
```

#### Contenedor para MySQL
```bash
docker run -d \
  --name mysql-docker \
  --network ot \
  -e MYSQL_ROOT_PASSWORD=root \
  -e MYSQL_DATABASE=mydb \
  -e MYSQL_USER=user \
  -e MYSQL_PASSWORD=123456 \
  -v mysql-data:/var/lib/mysql \
  mysql:5.7
```

#### Contenedor para PHPmyadmin
```bash
docker run -d \
  --name phpmyadmin-docker \
  --network ot  \
  -p 8080:80 \
  -e PMA_HOST=mysql-docker \
  -e PMA_USER=user \
  -e PMA_PASSWORD=123456 \
  phpmyadmin/phpmyadmin
```

### Desde compose
#### Instalación de compose
#### Descarga desde GitHub de Compose
```bash
sudo curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
```
#### Asignar permisos de ejecución
```bash
sudo chmod +x /usr/local/bin/docker-compose
```
#### Comprobar la versión
```bash
docker-compose --version
```


## Caso práctico con Compose
<details>
<summary>
Contenido del fichero YAML para el caso práctico
</summary>

```bash
version: '3.7'

services:
  apache:
    image: httpd:latest
    container_name: apache-docker
    ports:
      - "80:80"
    networks:
      - ot
    volumes:
      - ./html:/usr/local/apache2/htdocs/
  
  mysql:
    image: mysql:5.7
    container_name: mysql-docker
    environment:
      MYSQL_ROOT_PASSWORD: 123456
      MYSQL_DATABASE: mydb
      MYSQL_USER: user
      MYSQL_PASSWORD: 123456
    networks:
      - ot
    volumes:
      - mysql-data:/var/lib/mysql

  phpmyadmin:
    image: phpmyadmin/phpmyadmin
    container_name: phpmyadmin-container
    environment:
      PMA_HOST: mysql
      PMA_USER: user
      PMA_PASSWORD: 123456
    ports:
      - "8080:80"
    networks:
      - ot

volumes:
  mysql-data:

networks:
	ot
	driver:bridge
```

</details>

#### Lanzar y detener docker-compose
```bash
sudo docker-compose up -d 
sudo docker-compose down 
```

## Caso práctico desde la terminal

### Crear red
```bash
sudo docker network create ot
```
### Comprobación de redes
```bash
sudo docker network ls
NETWORK ID     NAME      DRIVER    SCOPE
d8dc1d547cca   bridge    bridge    local
0b1d5a9a0ba1   host      host      local
80383a5ddfe7   none      null      local
ef70cdc539c6   ot        bridge    local
```
### Creación y ejecución del contenedor de Apache
```bash
sudo docker run -d --name apache-docker --network ot -p 80:80 -v $(pwd)/html:/usr/local/apache2/htdocs/ httpd:latest
Unable to find image 'httpd:latest' locally
latest: Pulling from library/httpd
8a628cdd7ccc: Pull complete 
60ba3d18ad64: Pull complete 
4f4fb700ef54: Pull complete 
03e322382f93: Pull complete 
4ad6b63c403f: Pull complete 
c613327bbca6: Pull complete 
Digest: sha256:4564ca7604957765bd2598e14134a1c6812067f0daddd7dc5a484431dd03832b
Status: Downloaded newer image for httpd:latest
e23a662730b32189601456c3b5ad25cf5402073f5ff4c96db995f1e4c88b6694
```
### Creación y ejecución del contenedor de MySQL
```bash
sudo docker run -d --name mysql-docker --network ot -e MYSQL_ROOT_PASSWORD=root -e MYSQL_DATABASE=mydb -e MYSQL_USER=user -e MYSQL_PASSWORD=123456 -v mysql-data:/var/lib/mysql mysql:5.7
Unable to find image 'mysql:5.7' locally
5.7: Pulling from library/mysql
20e4dcae4c69: Pull complete 
1c56c3d4ce74: Pull complete 
e9f03a1c24ce: Pull complete 
68c3898c2015: Pull complete 
6b95a940e7b6: Pull complete 
90986bb8de6e: Pull complete 
ae71319cb779: Pull complete 
ffc89e9dfd88: Pull complete 
43d05e938198: Pull complete 
064b2d298fba: Pull complete 
df9a4d85569b: Pull complete 
Digest: sha256:4bc6bc963e6d8443453676cae56536f4b8156d78bae03c0145cbe47c2aad73bb
Status: Downloaded newer image for mysql:5.7
323fe08f159c714f9074726b8b2428a2be7c5b1b400868bf59e645b8a4d4e013
```
### Creación y ejecución del contenedor de phpmyadmin
```bash
sudo docker run -d --name phpmyadmin-docker --network ot -p 8080:80 -e PMA_HOST=mysql-docker -e PMA_USER=user -e PMA_PASSWORD=123456 phpmyadmin/phpmyadmin // Aquí hubo un error PMA_HOST, ya solucionado
Unable to find image 'phpmyadmin/phpmyadmin:latest' locally
latest: Pulling from phpmyadmin/phpmyadmin
af302e5c37e9: Pull complete 
71a74ed03dab: Pull complete 
3ef8d0774deb: Pull complete 
11d17388a3b8: Pull complete 
0814cbbf72a2: Pull complete 
3a28acedadf8: Pull complete 
2ab7ef40feaf: Pull complete 
88324ccb20a1: Pull complete 
ad5f2fca9132: Pull complete 
9df2a6231627: Pull complete 
b3207e60ff9a: Pull complete 
d18c9f420b35: Pull complete 
673faad72ba8: Pull complete 
4f4fb700ef54: Pull complete 
a5c74661bb9e: Pull complete 
1cf5cbfd971f: Pull complete 
e92d8472eb26: Pull complete 
7755344c0dda: Pull complete 
b0f9dd503cef: Pull complete 
2ee0fe041682: Pull complete 
Digest: sha256:95e01f723b5e55fabf16d0473f1df2354c4c6352b35902b51d6a6245e074aee4
Status: Downloaded newer image for phpmyadmin/phpmyadmin:latest
906a873cdf0d01128049bae11e422d566d85cea32c2318ca901135a25a333d59
```

### Listado de contenedores
```bash
sudo docker ps 
CONTAINER ID   IMAGE                   COMMAND                  CREATED          STATUS          PORTS                                     NAMES
906a873cdf0d   phpmyadmin/phpmyadmin   "/docker-entrypoint.…"   4 minutes ago    Up 4 minutes    0.0.0.0:8080->80/tcp, [::]:8080->80/tcp   phpmyadmin-docker
323fe08f159c   mysql:5.7               "docker-entrypoint.s…"   34 minutes ago   Up 34 minutes   3306/tcp, 33060/tcp                       mysql-docker
e23a662730b3   httpd:latest            "httpd-foreground"       58 minutes ago   Up 58 minutes   0.0.0.0:80->80/tcp, [::]:80->80/tcp       apache-docker
```

