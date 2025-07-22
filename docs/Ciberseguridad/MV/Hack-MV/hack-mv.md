---
title: Hack MV
---

# Hack MV
Procedo a la creación de una **máquina virtual** para ejercicios de **ciberseguridad**, la cual será un **OS GNU/Linux** del ecosistema **RHEL** para salir de mi área de confort **Debian**, más concretamente AlmaLinux 8.10.

## Usuarios del OS
Para los usuarios he usado 2 referencias de Marvel, en este caso serán Iron Man y el Dr Doom.

:::info
- **dr-doom** / **Dr_????**
- **iron-man** / **t??-?????**
:::

Ambos usuarios son usuarios con privilegios reducidos, pero el acceso a la máquina por ssh se logrará con el usuario **iron-man**, una vez dentro de la máquina, el **atacante** podrá escalar privilegios encontrando al usuario **dr-doom**, el cual prodrá llevar a cabo *ciertas acciones* de **permisos elevados** desde una **jaula**.

Para ello es necesario llevar 2 acciones clave, primero otorgar al user **dr-doom** un directorio donde poder ejecutar ciertos comandos, para ello es necesario modificar el fichero **/etc/sudoers** y luego generar en ese directorio una **jaula**.

### Sudoers
Para gestionar la escala de privilegios del usuario **dr-doom** se modifica el fichero **/etc/sudoers** *(previamente se realiza un backup del mismo)* de la siguiente forma.
```bash
dr-doom ALL=(ALL)  NOPASSWD: /opt/limited/*
```
De esta forma desde ese directorio el usuario dr-doom podrá llevar a cabo las acciones permitidas por la jaula.

:::info
- dr-doom: user
- ALL [hosts] = (ALL) [users]
- NOPASSWD: sin login
- /opt/limited: zona de acción donde puede operar con sudo el usuario
:::

### Jaula
Realmente no es una jaula completa, no se usa **chroot**, pero si un entorno similar que permite ejecutar dentro de un directorio una consola bash a un determinado usuario.

```bash
cd /opt
mkdir limited
cd limited
mkdir bin
mkdir lib
mkdir lib64
```

Ahora queda copiar las librerías con cp (se puede añadir -a por si hay enlaces simbolicos) del binario bash, para conseguir las librerias necesarias se usa el comando ldd.
``` bash 
ldd /bin/bash
```
Y entonces se muestran las librerías necesarias, esas serán las que se copien a la estructura creada en el directorio **/opt/limited/**.

## Servidor vsFTPD
```bash
sudo dnf install vsftpd -y
```
Editar el fichero de configuración del servidor **FTP** en la ruta siguiente
```bash
sudo nano /etc/vsftpd/vsftpd.conf
```
Descomentar la línea del fichero de configuración que permite habilitar al usuario anonimo
```bash
Anonymous_enable=YES
```
Una vez descomentada la línea ya se puede hacer login con el **user** *Anonymous* y la **password** en *blanco*, una vez permitido el acceso, se pueden subir ficheros a la siguiente ruta
```bash
/var/ftp/
```


## Servidor SSH
```bash
sudo dnf install openshh-server
```

## Servidores web
Los servicios web vulnerables que ofrecen las pistas para completar el reto serán 4: 1 nativo (80) y 3 virtuales cada uno con un dominio.

### Instalación de Apache
```bash
sudo dnf install -y httpd
sudo systemctl enable --now httpd
sudo systemctl status httpd
```

#### Subdirectorios
A continuación se crean los subdirectorios para los servidores virtuales.

```bash
sudo mkdir /var/www/servicio1.local/
```

#### Permisos
Si se requisiera hacer ajustes en los permisos, en este caso no es necesario porque estoy realizando todo como **root** y los usuarios atacantes deben de interaccionar con el navegador.

```bash
sudo chown -R user:grupo /var/www/servicioX.local/public_html
```

#### Ficheros index
Para cada dominio virtual se añade un fichero index.html


#### Contenido de los servicios
Requiere la creación de ficheros de configuración, uno por servicio.

```bash
sudo nano /etc/httpd/conf.d/primero.local.conf 
```

:::tip
En AlmaLinux los ficheros de configuración se colocan en httpd/conf.d y se les asigna la extensión .conf y todos en el mismo directorio. No dispone del sistema de comandos a2* de Apache/Debian para habilitar y deshabilitar.
```bash
/etc/httpd/conf/httpd.conf # Configuración principal
/etc/httpd/conf.d/*.conf # Virtual hosts
```
:::


Requiere la creación de ficheros virtuales, aquí se puede optar por usar el 80 para todos o asignar otro puerto. Esto ya veré como lo haré.

```bash
<VirtualHost *:80>
    ServerName servicioX.local
    DocumentRoot /var/www/servicioX.local
    <Directory /var/www/servicioX.local/>
        AllowOverride All
        Require all granted
    </Directory>
</VirtualHost>
```

:::tip[Jerarquía servidores]
/var/www/html/            #  Server Web (nativo)
/var/www/servicio1.local/ # virtual host 1
/var/www/servicio2.local/ # virtual host 2
/var/www/servicio3.local/ # virtual host 3
:::

#### Modificar fichero /etc/hosts
Añadir al fichero de configuración de los hosts los nombres de dominio de los servidores virtuales asociados a la máquina virtual.
```bash
127.0.0.1   servicioX.local
```

## PHP y MariaDB
### Instalación de PHP
```bash
sudo dnf install php php-mysqlnd php-json php-mbstring php-common php-xml php-cli php-gd php-opcache php-pdo -y
```
#### Verificación de la instalación
```bash
php --version
```
### Instalación de PhpMyAdmin
:::warning
Esto se puede convertir en una odisea en sistemas operativos RHEL por SElinux y la gestión que
usan estas distros de dependencias comparado a distros Debian.
:::

#### Repositorio EPEL
```bash
sudo dnf install epel-release -y
```
#### Actualizar metadatos
```bash
sudo dnf clean all && sudo dnf makecache
```
Sigue sin encontrar phpmyadmin entonces se va a descargar directamente
```bash
curl -L -o phpMyAdmin.tar.gz https://www.phpmyadmin.net/downloads/phpMyAdmin-latest-all-languages.tar.gz
sudo mkdir /usr/share/phpMyAdmin
sudo tar xzf phpMyAdmin.tar.gz -C /usr/share/phpMyAdmin --strip-components=1
ls /usr/share/phpMyAdmin # Comprobar que están todos los ficheros
```
#### Fichero de configuración de Apache
Crear un fichero en **/etc/httpd/conf.d/phpMyAdmin**
```bash
Alias /phpmyadmin /usr/share/phpMyAdmin

<Directory /usr/share/phpMyAdmin/>
    Require all granted
</Directory>
```
#### Fichero de configuración de phpMyAdmin
Requiere generar uno propio usando de referencia el proporcionado como ejemplo
```bash
cp /usr/share/phpMyAdmin/config.sample.inc.php /usr/share/phpMyAdmin/config.inc.php
```
Ajustar estas lineas
```bash
$cfg['blowfish_secret'] = ''; // Contraseña para encriptar cookies y demás
$cfg['Servers'][1]['host'] = '10.255.255.77';  // IP del servidor MariaDB
$cfg['Servers'][1]['auth_type'] = 'cookie';    // Para pedir usuario y contraseña
$cfg['Servers'][1]['AllowNoPassword'] = false; // No permitir conexión sin contraseña

```
#### Crear usuario para phpmyadmin
```sql
CREATE USER IF NOT EXISTS 'phpmyadmin'@'%' IDENTIFIED BY ''; -- Creación user
GRANT ALL PRIVILEGES ON *.* TO 'phpmyadmin'@'%' WITH GRANT OPTION; -- Permisos *.* (db.table)
FLUSH PRIVILEGES; -- Recarga permisos
```
Comprobar que funciona correctamente
```bash
mysql -u phpmyadmin -h <IP> -p
```


#### Configurar firewall
```bash
sudo firewall-cmd --permanent --add-port=3306/tcp
sudo firewall-cmd --permanent --add-service=http
sudo firewall-cmd --reload
```
#### Ajustar SELinux
```bash
sudo sestatus
sudo setsebool -P httpd_can_network_connect_db 1 # Permanente
sudo setenforce 0 # Temporal
```


### Instalación de MariaDB
```bash
sudo dnf install mariadb-server
```
#### Comprobación de la instalación
```bash
mysql --version
```
#### Activación y comprobación del servicio
```bash
systemctl enable mariadb
systemctl start mariadb
systemctl status mariadb
```
## Aplicación PHP - MariaDB
### MariaDB
```sql
CREATE DATABASE hack;
USE hack;

create table users( id INT ZEROFILL AUTO_INCREMENT PRIMARY KEY, user varchar (64), password varchar (64) ) ENGINE = INNODB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_spanish2_ci; 

INSERT INTO users (user, password) VALUES
('admin', '<password>')
```

### Php
#### Fichero index.php
```php
<?php
// Creación de la sesión
session_start();

// Se comprueba si existe el usuario
if (isset($_SESSION["user"])) {
    // Si se está logueado se va al dashboard.php	
    header("Location: dashboard.php");
    exit();
}

// Si no se está logueado 
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["user"])) {
    $con = new mysqli('localhost', 'root', '', 'hack');
    if ($con->connect_error) {
        die("Error en la conexión a base de datos");
    }

    // Guardar los datos del user 	
    $user = $_POST["user"];     
    $pass = $_POST["password"]; 

    // Consulta SQL muy Vulnerable
    $query = "SELECT * FROM users WHERE user = '$user' AND password = '$pass'";
    $result = $con->query($query);

    if ($result->num_rows > 0) {
        $_SESSION["user"] = $user; 
        header("Location: dashboard.php");
        exit();
    } else {
        echo "Datos de acceso incorrectos";
    }
}
?>
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Hack me: Index </title>
  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }

    html, body {
      height: 100%;
      font-family: sans-serif;
      background: #f5f5f5;
    }

    body {
      display: grid;
      grid-template-rows: auto 1fr;
      grid-template-columns: 1fr;
      grid-template-areas: 
        "header"
        "content";
    }

    header {
      grid-area: header;
      background-color: #333;
      color: #fff;
      padding: 1rem;
      display: flex;
      align-items: center;
      justify-content: space-between;
      position: fixed;
      top: 0;
      left: 0;
      width: 100%;
      z-index: 10;
    }
    
    /* Icono menú hamburguesa */
    .hamburger {
      font-size: 1.8rem;
      cursor: pointer;
      user-select: none;
    }

    /* Modal - PopUp */
    .content {
      grid-area: content;
      display: flex;
      justify-content: center;
      align-items: start;
      padding: 6rem 2rem 2rem; 
    }

    .content-inner {
      background: #fff;
      width: 68rem;
      max-width: 100%;
      min-height: 14rem;
      box-shadow: 0 0 10px rgba(0,0,0,0.1);
      padding: 2rem;
      border-radius: 8px;
      margin-top:10rem;
    }

    .content-inner a {
      color: #007BFF;
      text-decoration: underline;
      cursor: pointer;
    }

    /* Menú oculto debajo del header */
    .menu {
      position: fixed;
      top: 4rem; 
      left: 0;
      width: 100%;
      height: calc(100% - 4rem); 
      background: #444;
      color: #fff;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      gap: 2rem;
      transform: translateX(-100%); /* Se oculta el menú de LTR */
      transition: transform 0.4s ease;
      z-index: 9;
    }

    .menu.active { 
      transform: translateX(0); /* Se muestra el menú de LTR */
    }

    .menu a {
      color: #fff;
      text-decoration: none;
      font-size: 1.5rem;
      transition: color 0.2s;
    }

    .menu a:hover {
      color: #ddd;
    }

  </style>
</head>
<body>
<!-- Barra Superior -->
  <header>
    <!-- div class="hamburger" onclick="toggleMenu()">☰</div-->
    <h1>Hack me!</h1>
  </header>

<!-- Menú Lateral, oculto/visible con toggle -->
  <nav class="menu" id="menu">
    <a href="#">Log In</a>
    <a href="#">Log Out</a>
  </nav>

<!-- Contenido centrado -->
  <div class="content">
<div class="content-inner" style="width: 320px; padding: 1rem;">
  <h2 style="text-align: center;padding:.5rem 0 1.5rem 0;">Hack Me App</h2>
  <form method="POST" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" style="display: flex; flex-direction: column; gap: 0.8rem;">
      <input type="text" name="user" required style="width: 100%; padding: 0.5rem; border: 1px solid #ccc; border-radius: 4px;">
      <input type="password" name="password" required style="width: 100%; padding: 0.5rem; border: 1px solid #ccc; border-radius: 4px;">
      <input type="submit" value="Acceder" style="width: 100%; padding: 0.5rem; background: #333; color: #fff; border: none; border-radius: 4px; cursor: pointer;margin-bottom:1rem;">
  </form>
</div>
  </div>
  <script>
    function toggleMenu() {
       /* Capturar elemento menú y jugar con su visibilidad */
      document.getElementById('menu').classList.toggle('active');
    }
  </script>
</body>
</html>
```

#### Fichero dashboard.php
```bash
<?php
session_start();
if(!isset($_SESSION["user"])){
	header("Location: index.php");
	exit();
}
?>
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Hack me: Dashboard </title>
  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }

    html, body {
      height: 100%;
      font-family: sans-serif;
      background: #f5f5f5;
    }

    body {
      display: grid;
      grid-template-rows: auto 1fr;
      grid-template-columns: 1fr;
      grid-template-areas: 
        "header"
        "content";
    }

    header {
      grid-area: header;
      background-color: #333;
      color: #fff;
      padding: 1rem;
      display: flex;
      align-items: center;
      justify-content: space-between;
      position: fixed;
      top: 0;
      left: 0;
      width: 100%;
      z-index: 10;
    }
    
    /* Icono menú hamburguesa */
    .hamburger {
      font-size: 1.8rem;
      cursor: pointer;
      user-select: none;
    }

    /* Modal - PopUp */
    .content {
      grid-area: content;
      display: flex;
      justify-content: center;
      align-items: start;
      padding: 6rem 2rem 2rem; 
    }

    .content-inner {
      background: #fff;
      width: 68rem;
      max-width: 100%;
      min-height: 40rem;
      box-shadow: 0 0 10px rgba(0,0,0,0.1);
      padding: 2rem;
      border-radius: 8px;
    }

    .content-inner a {
      color: #007BFF;
      text-decoration: underline;
      cursor: pointer;
    }

    /* Menú oculto debajo del header */
    .menu {
      position: fixed;
      top: 4rem; 
      left: 0;
      width: 100%;
      height: calc(100% - 4rem); 
      background: #444;
      color: #fff;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      gap: 2rem;
      transform: translateX(-100%); /* Se oculta el menú de LTR */
      transition: transform 0.4s ease;
      z-index: 9;
    }

    .menu.active { 
      transform: translateX(0); /* Se muestra el menú de LTR */
    }

    .menu a {
      color: #fff;
      text-decoration: none;
      font-size: 1.5rem;
      transition: color 0.2s;
    }

    .menu a:hover {
      color: #ddd;
    }

  </style>
</head>
<body>
<!-- Barra Superior -->
  <header>
    <div class="hamburger" onclick="toggleMenu()">☰</div>
    <h1>Hack me!</h1>
  </header>

<!-- Menú Lateral, oculto/visible con toggle -->
  <nav class="menu" id="menu">
    <a href="index.php">Log In</a>
    <a href="logout.php">Log Out</a>
  </nav>

<!-- Contenido centrado -->
  <div class="content">
    <div class="content-inner">
      <h2>Hack Me: Dashboard</h2>
      <p style="padding:1rem 0 1.5rem 0;"><?php echo "Bienvenido Sr./Sra. ".$_SESSION["user"]; ?></p>
      <p></p>
      <table style="border-collapse: collapse; width: 100%; text-align: center;">
  <tr style="background-color: #555;color:white;">
    <td style="padding: 8px; border: 1px solid #222;">User</td>
    <td style="padding: 8px; border: 1px solid #222;">Password</td>
    <td style="padding: 8px; border: 1px solid #222;">Description</td>

  </tr>
  <tr style="background-color: #f3f3f3;">
    <td style="padding: 8px; border: 1px solid #222;">Spiderman</td>
    <td style="padding: 8px; border: 1px solid #222;">********</td>
    <td style="padding: 8px; border: 1px solid #222">The Amazing Spiderman</td>
  </tr>
  </tr>
    <tr style="background-color: #c3c3c3;">
    <td style="padding: 8px; border: 1px solid #222;">Gata Negra</td>
    <td style="padding: 8px; border: 1px solid #222;">********</td>
    <td style="padding: 8px; border: 1px solid #222;">Felicia Hardy</td>
  </tr>
  <tr style="background-color: #f3f3f3;">
    <td style="padding: 8px; border: 1px solid #222;">Dr Doom</td>
    <td style="padding: 8px; border: 1px solid #222;">********</td>
    <td style="padding: 8px; border: 1px solid #222;">Victor Von Doom</td>
  </tr>
    <tr style="background-color: #c3c3c3;">
    <td style="padding: 8px; border: 1px solid #222;">Jean Grey</td>
    <td style="padding: 8px; border: 1px solid #222;">********</td>
    <td style="padding: 8px; border: 1px solid #222;">Jean Elaine Grey Summers</td>
  </tr>
  </tr>
    <tr style="background-color: #f3f3f3;">
    <td style="padding: 8px; border: 1px solid #222;">Lobezno</td>
    <td style="padding: 8px; border: 1px solid #222;">********</td>
    <td style="padding: 8px; border: 1px solid #222;">James Howlet</td>
  </tr>
  </tr>
    <tr style="background-color: #c3c3c3;">
    <td style="padding: 8px; border: 1px solid #222;">Viuda Negra</td>
    <td style="padding: 8px; border: 1px solid #222;">********</td>
    <td style="padding: 8px; border: 1px solid #222;">Natasha Romanova</td>
  </tr>
</table>
    </div>
  </div>


  <script>
    function toggleMenu() {
       /* Capturar elemento menú y jugar con su visibilidad */
      document.getElementById('menu').classList.toggle('active');
    }
  </script>
</body>
</html>


```

#### Fichero logout.php
```bash
<?php
session_start();
session_unset();
session_destroy();
header("Location: index.php");
?>
```

## Inyección SQL clásica
```sql
' OR '1'='1' -- # Importante, dejar un espacio después del comentario
SELECT * FROM users WHERE user = '' OR '1'='1' -- ' AND password = 'abc'
```


## Aplicación NodeJS + MongoDB
### Instalación de MongoDB
#### Versión Debian/Ubuntu

```bash
wget -qO - https://pgp.mongodb.com/server-7.0.asc | sudo tee /etc/apt/trusted.gpg.d/mongodb-server-7.0.gpg > /dev/null && echo "deb [ arch=amd64 ] https://repo.mongodb.org/apt/debian bookworm/mongodb-org/7.0 main" | sudo tee /etc/apt/sources.list.d/mongodb-org-7.0.list

sudo apt update
sudo apt install -y mongodb-org && sudo systemctl enable --now mongod

mongosh
```


#### Versión RHEL (incluye AlmaLinux)
```bash
sudo nano /etc/yum.repos.d/mongodb.repo

[mongodb-org-6.0]
name=MongoDB Repository
baseurl=https://repo.mongodb.org/yum/redhat/$releasever/mongodb-org/6.0/x86_64/
gpgcheck=1
enabled=1
gpgkey=https://www.mongodb.org/static/pgp/server-6.0.asc

sudo dnf install -y mongodb-org
sudo systemctl enable --now mongod

sudo ufw allow 27017/tcp    # Debian (ufw)
sudo firewall-cmd --permanent --add-port=27017/tcp
sudo firewall-cmd --reload  # AlmaLinux (firewalld)
```
:::warning[Conexiones externas]
Editar el fichero **/etc/mongod.conf**
```bash
/etc/mongod.conf
```
Y usar la **wildcard** **0.0.0.0** en **bindIp**.
:::

#### Versión Docker
```bash
sudo dnf update -y # actualizar dnf
sudo dnf install -y yum-utils # herramientas necesarias
sudo dnf config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo # añadir repo
sudo dnf install -y docker-ce docker-ce-cli containerd.io # instalar docker
sudo systemctl enable --now docker # activar el servicio
sudo usermod -aG docker $USER # añadir user al grupo
newgrp docker # recargar permisos del grupo
```

## App NodeJS
La aplicación desarrollada en NodeJS, es una aplicación sencilla que permite inyección No-SQL, para ello se ha usado MongoDB y dado que da problemas las ultimas versiones por instrucciones ilegales en lo sistemas de virtualización de virtual box y las versiones más viejas por determinadas librerías, tomo la decición de usar docker y crear un contenedor para el servicio docker.

El contenedor requería de un volumen para la persistencia de datos, por ello se generará un directorio para ello.
```bash
mkdir /opt/mongodb/
```
Una vez creado el volumen se crea el contendor con la imagen de mongodb, mapeando el puerto del host 27017 al 27017 del contenedor, de esta forma no habrá problemas para poder usar el servidor de nodejs del host con MongoDB, eso sí, también hay que usar una imagen vieja. Anterior a la 5.0 que usa instrucciones AVX.
```bash
docker run -d \
  --name mongodb \
  -p 27017:27017 \
  -v /opt/mongodb:/data/db \
  mongo:4.4
```
:::tip[Repaso comandos docker]
Los comandos **docker** pueden liar porque ha evolcionado la sintaxis y a veces se pueden mezclar sintaxis antigua y moderna.
| Comando antiguo   | Comando actual        |
| ----------------- | --------------------- |
| `docker rm`       | `docker container rm` |
| `docker rmi`      | `docker image rm`     |
| `No existía`      | `docker volume rm`    |
| `No existía`      | `docker network rm`   |

Además es importante asegurarse de que mongodb sea propietarios del directorio, tanto el user como el group, por ello en vez de usar **mongodb** se usara el **id** de user y group.
```bash
chown 999:999 /opt/mongodb/
```
:::

### Instalación de NodeJS
```bash
curl -fsSL https://rpm.nodesource.com/setup_20.x | sudo bash -
dnf install -y nodejs
```

### Creación del proyecto
```bash
mkdir /opt/app-node/
npm init -y
```

```javascript


```

### Ejecución
#### MongoDB en funcionamiento
Lanzar el contenedor de mongodb
```bash
docker run -d \
  --restart=always \ 
  --name mongodb \
  -p 27017:27017 \
  -v /opt/mongodb:/data/db \
  mongo:4.4.18
```
Se puede configurar para que siempre se reinicie el contenedor automáticamente con el proceso de **docker**, debería de funcionar siempre, pero me gusta más tener un script incorporado en el  **systemd** y activarlo como servicio, de todas formas la opción del comando es la siguiente.
```bash
docker update --restart=always mongodb
```
#### NodeJS en funcionamiento
```bash
node server.js #/opt/app-node
```

#### Introducir datos en database
```bash
use testdb

db.users.insertOne({
  email: "victima@example.com",
  password: "123456"
})
```

#### Inyección en NodeJS
Inyección para acceder al servidor
```bash
{"$ne": null }
```


#### Crear un servicio para NodeJS
Creo un servicio para el inicio a systemd del servidor de NodeJS.
sudo nano /etc/systemd/system/nodeapp.service

```bash
[Unit] # Unidad, descripción y relación con otras
Description=Servidor web App con NodeJS
After=network.target docker.service
Requires=docker.service

[Service] # Configuración del servicio
ExecStart=/usr/bin/node /opt/app-node/server.js
WorkingDirectory=/opt/app-node
Restart=always
User=nobody
Environment=NODE_ENV=production

[Install] # Conexión con el sistema de arranque, nivel de target
WantedBy=multi-user.target

```
Reiniciar systemd, activar servicio y lanzar
#### Activar Docker como servicio
```bash
sudo systemctl enable --now docker
```
#### Crear servicio para MongoDB
```bash
/etc/systemd/system/mongodb-container.service
```
```bash
[Unit]
Description=Contenedor MongoDB
Requires=docker.service
After=docker.service

[Service]
Restart=always
ExecStart=/usr/bin/docker start -a mongodb
ExecStop=/usr/bin/docker stop mongodb

[Install]
WantedBy=multi-user.target
```
```bash
sudo systemctl d-reexec
sudo systemctl enable mongodb-container
sudo systemctl start mongodb-container

```
#### Permisos a mongo
```bash
sudo chown -R 999:999 /opt/mongodb
sudo chmod -R 755 /opt/mongodb
```

:::warning[Tips]
Comando **systemd-analyze** para verificar el servicio creado en SystemD
```bash
systemd-analyze verify file.service
```
Comprobar imágen correcta
```bash
docker inspect -f '{{ .Config.Image }}' mongodb
```
Inspeccionar imágenes de MongoDB
```bash
docker inspect mongodb | grep Image
```
Siempre reiniciar un contenedor con cada inicio
```bash
docker update --restart=always mongodb
````
:::


#### Comprobar política reinicio
docker inspect -f '{{ .HostConfig.RestartPolicy.Name }}' mongodb


## Nginx
```bash
sudo dnf install nginx -y
sudo systemctl start nginx
sudo systemctl enable nginx
sudo firewall-cmd --permanent --add-service=http
sudo firewall-cmd --permanent --add-service=https
sudo firewall-cmd --reload
```
### Configuración
```bash
/etc/nginx/nginx.conf
/etc/nginx/conf.d/
nginx -t # validar la configuración
```
#### Problemas acceso en AlmaLinux
```bash
sudo dnf install policycoreutils-python-utils -y
sudo semanage port -a -t http_port_t -p tcp 8080
sudo semanage port -a -t http_port_t -p tcp 6969
sudo cat /var/log/nginx/error.log
```

## Problemas acceso 
````bash
sudo firewall-cmd --list-all
sudo firewall-cmd --permanent --add-service=http
sudo firewall-cmd --reload
sudo ss -tlnp | grep httpd
sudo sestatus # Estado de SElinux
getenforce # Modo de ejecución de SElinux
sudo setenforce 0 #Disable
```