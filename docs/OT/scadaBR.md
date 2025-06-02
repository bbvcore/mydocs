---
sidebar_position: 1
title: scada BR
---

# ScadaBR
## Descarga e instalación
### Clonar repositorio
```
sudo git clone https://github.com/thiagoralves/ScadaBR_Installer.git
```

### Acceder directorio
```
cd ScadaBR_Installer
```

### Script
```
sudo bash install_scadabr.sh
```

### Configuración de Tomcat
```
/opt/tomcat6/apache-tomcat-6.0.53/bin/bash catalina.sh start
```

### Creación de rol
```
/opt/tomcat6/apache-tomcat-6.0.53/conf/tomcat-users.xml
```

## Interfaz gráfica
### Icono de base de datos
Sirve para cargar los datos, normalmente de un PLC o del protocolo ModBus.

### Icono ojo
Es necesario para añadir puntos (variables).

### Icono papel
Se corresponde con la vista gráfica, carga CSS.

### Icono aplicación
Aquí se permite realizar operaciones como uploads (fondo), graphics (iconos) y manipular los resources (css).
