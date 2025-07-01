---
sidebar_position: 3
title: Node-red
---

# &#128225; Node-red
Se trata de un **software** *basado* en **flujos**, mediante **componentes JSON**, para trabajar con diferentes tecnologías como **APIs**, **hardware** o *servicios* basado en **NodeJS** y ampliamente popular en **IoT**.

##  &#128189; Instalación
### &#10003; Actualización del sistema
```bash
sudo apt install update
sudo apt install upgrade
```
## &#10003; Instalación de NodeJS
```bash
sudo apt install nodejs -y
```

## &#10003; Instalación de Node-red (sin Admin)
```bash
npm install -g --unsafe-perm node-red 
```

## &#10003; Instalación de Node-red (Admin)
```bash
npm install -g --unsafe-perm node-red-admin
```

### &#10003; Generar hash
```bash
node-red admin hash-pw 
```
Guardar el hash para el fichero de configuración generado tras introducir un password para lograr su generación.

Una vez guardado se accede al fichero settings, en mi caso este fichero está en la siguiente ruta.

```bash
/usr/lib/node_modules/node-red/settings.js # global
~/.node-red/settings.js # local, es donde se ha de editar el pass
```

Una vez abierto hay que buscar la sección de **adminAuth** y en la propiedad **password** del objeto pegar el hash previamente generado.

```javascript
   adminAuth: {
        type: "credentials",
        users: [{
            username: "admin", # Se puede personalizar
            password: "<pegar Hash>",
            permissions: "*"
        }]
    },
```

También, justo encima de este objeto, se puede descomentar la propiedad **credentialSettings** y añadir una password para añadir seguridad en un entorno de producción, ya que cifra las contraseñas almacenadas en nodos como MySQL, Mqtt...

## &#9989; Lanzamiento de node-red
```bash
node-red
```

## &#129489; Soluciones a problemas
### &#128276; Problema con ESP32 y platform del serial
Es necesario añadir nuestro usuario al grupo **dialout**.
```bash
sudo usermod -a -G dialout $USER
```

### &#10060; Otros problemas y soluciones
Los usuarios de sistemas GNU/Linux para usar este tipo de placas, como las usadas a través de **platform.io**, se ven obligados a instalar el espacio de usuario de dispositivos (udev), el cual es un administrador de nodos del dispositivo y también un manejador de los eventos que suceden al agregar o eliminar dispositivos de HW del OS.

:::warning
Para este tipo de problemáticas consultar el siguiente enlace:
https://docs.platformio.org/en/latest/core/installation/udev-rules.html
:::