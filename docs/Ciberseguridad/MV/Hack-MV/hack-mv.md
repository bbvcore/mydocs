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


## Servidor SSH


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
('admin', 'admin1234'),
('admin', '12345678'),
('admin', '00000000');
```

### Php
```php

<?php
// Creación de la sesión
session_start();

// Se comprueba si existe el usuario
if (isset($_SESSION["user"])) {
    // Si se está logueado se va al access.php	
    header("Location: access.php");
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
        header("Location: access.php");
        exit();
    } else {
        echo "Datos de acceso incorrectos";
    }
}
?>


<form method="POST" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">
    User: <input type="text" name="user" required><br>
    Password: <input type="password" name="password" required><br>
    <input type="submit" value="Acceder">

</form>

```


inyección
```sql
' OR '1'='1' -- 
SELECT * FROM users WHERE user = '' OR '1'='1' -- ' AND password = '123'
```

```
### Access.php
```php
<?php
session_start();
if(!isset($_SESSION["user"])){
	header("Location: index.php");
	exit();
}
echo "Bienvenido: ". $_SESSION["user"];

?>
```




## Aplicación NodeJS + MongoDB

```javascript
```

### Problemas acceso
````bash
sudo firewall-cmd --list-all
sudo firewall-cmd --permanent --add-service=http
sudo firewall-cmd --reload
sudo ss -tlnp | grep httpd
getenforce #SElinux
sudo setenforce 0
```