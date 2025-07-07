---
sidebar_position: 1
title: scada BR
---

# ScadaBR
## Descarga e instalación
### Clonar repositorio
```bash
sudo git clone https://github.com/thiagoralves/ScadaBR_Installer.git
```

### Acceder directorio
```bash
cd ScadaBR_Installer
```

### Script
```bash
sudo bash install_scadabr.sh
```

### Configuración de Tomcat
```bash
/opt/tomcat6/apache-tomcat-6.0.53/bin/bash catalina.sh start
```

### Creación de rol
```bash
/opt/tomcat6/apache-tomcat-6.0.53/conf/tomcat-users.xml
```

## Interfaz gráfica
Dispone de una serie de iconos en su interfaz gráfica donde los más destacadas son los siguientes.

### Icono de base de datos
Sirve para cargar los datos, normalmente de un PLC o del protocolo ModBus.

### Icono ojo
Es necesario para añadir puntos (variables).

### Icono papel
Se corresponde con la vista gráfica, carga CSS.

### Icono aplicación
Aquí se permite realizar operaciones como uploads (fondo), graphics (iconos) y manipular los resources (css).
