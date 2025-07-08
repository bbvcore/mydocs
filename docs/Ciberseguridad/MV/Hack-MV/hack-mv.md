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

```
CREATE DATABASE labdb;
USE labdb;

CREATE TABLE users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  username VARCHAR(50),
  password VARCHAR(50)
);

INSERT INTO users (username, password) VALUES
('admin', 'admin123'),
('user1', 'pass1'),
('user2', 'pass2');



<?php
$conn = new mysqli('localhost', 'root', 'tu_password', 'labdb');

if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

if (isset($_POST['username']) && isset($_POST['password'])) {
    $user = $_POST['username'];
    $pass = $_POST['password'];

    // ¡Vulnerable a SQL Injection!
    $sql = "SELECT * FROM users WHERE username='$user' AND password='$pass'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        echo "Bienvenido, " . htmlspecialchars($user);
    } else {
        echo "Credenciales incorrectas";
    }
}
?>

<form method="post" action="">
    Usuario: <input type="text" name="username" /><br />
    Contraseña: <input type="password" name="password" /><br />
    <input type="submit" value="Entrar" />
</form>

```


``` 
use labdb

db.users.insertMany([
  { username: "admin", password: "admin123" },
  { username: "user1", password: "pass1" },
  { username: "user2", password: "pass2" }
])


const http = require('http');
const url = require('url');
const { MongoClient } = require('mongodb');

const client = new MongoClient('mongodb://localhost:27017');
let db;

async function startServer() {
  await client.connect();
  db = client.db('labdb');

  http.createServer(async (req, res) => {
    const query = url.parse(req.url, true).query;

    if (req.url.startsWith('/login') && query.username && query.password) {
      const { username, password } = query;

      // Vulnerable: No sanitización ni validación
      const user = await db.collection('users').findOne({ username: username, password: password });

      if (user) {
        res.writeHead(200, {'Content-Type': 'text/plain'});
        res.end(`Bienvenido, ${username}`);
      } else {
        res.writeHead(401, {'Content-Type': 'text/plain'});
        res.end('Credenciales incorrectas');
      }
    } else {
      res.writeHead(200, {'Content-Type': 'text/html'});
      res.end(`
        <form method="GET" action="/login">
          Usuario: <input name="username" /><br />
          Contraseña: <input name="password" /><br />
          <input type="submit" value="Entrar" />
        </form>
      `);
    }
  }).listen(3000, () => console.log('Servidor Node.js escuchando en puerto 3000'));
}

startServer().catch(console.error);
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