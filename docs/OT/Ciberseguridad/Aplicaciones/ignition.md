---
sidebar_position: 1
title: scada BR
---

# Ignition
## Instalación y descarga
### Actualización
```
sudo apt update
```

### Instalar Java
```
sudo apt install openjdk-11-jdk -y
```

### Acceso a la URL de Inductive
```
https://inductiveautomation.com/downloads/ignition/
```

### Ejecutar instalador de ignition
```
sudo bash ignition-8.1.48-linux-64-installer.run 
```
Añadir un user del sistema operativo válido para la instalación.

### Acceder a la URL local
Ir a la web localhost:8088

### Escoger opción deseada
En este caso corresponde escoge: "Maker Edition" y es necesario entonces gestionar una licencia de usuario, para ello registrarse https://inductiveautomation.com/.

Desde esa cuenta, se crear la licencia y se usa el token generado desde la cuenta en **inductive** para su suo en localhost. También es necesario configurar una **Gateway** para poder lanzar la aplicación.