---
sidebar_position: 3
title: Node-red
---

# Node-red

## Instalación
### Actualización del sistema
```bash
sudo apt install update
sudo apt install upgrade
```
## Instalación de NodeJS
```bash
sudo apt install nodejs -y
```

## Instalación de Node-red (sin Admin)
```bash
npm install -g --unsafe-perm node-red 
```

## Instalación de Node-red (Admin)
```bash
npm install -g --unsafe-perm node-red-admin
```

### Generar hash
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

```bash
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

## Lanzamiento de node-red
```bash
node-red
```
