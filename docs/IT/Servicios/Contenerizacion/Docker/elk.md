---
sidebar_position: 2
title: ELK
---
# ELK
Despliegue básico para pruebas de la pila de elastic **ELK**. Uno de los principales problemas de realizar un despliegue con docker-compose en este caso es que **elasticsearch** y **kibana** requieren de la combinación de un proceso interactivo y en un orden de ejecución determinado, ni completamente secuencial ni paralelo, si se pretende añadir seguridad por ello este despliegue es sin seguridad. Con contenedores resulta más sencillo un despliegue con seguridad, aunque en este caso particular creo que sería mejor un despliegue con scripting.

## Despliegue con docker-compose
Utilización de la herramienta **docker-compose** que requiere de un fichero **yml/yaml** para realizar el despliegue.

<details>
<summary>
Fichero Yaml para el despliegue
</summary>

```
version: "3.8"

services:
  elasticsearch:
    image: docker.elastic.co/elasticsearch/elasticsearch:8.8.2
    container_name: elasticsearch
    environment:
      - discovery.type=single-node
      - xpack.security.enabled=false
    ports:
      - "9200:9200"
    networks:
      - elk-basic

  kibana:
    image: docker.elastic.co/kibana/kibana:8.8.2
    container_name: kibana
    environment:
      - ELASTICSEARCH_HOSTS=http://elasticsearch:9200
      - XPACK_SECURITY_ENABLED=false
      - KIBANA_SYSTEM_PASSWORD=
    ports:
      - "5601:5601"
    depends_on:
      - elasticsearch
    networks:
      - elk-basic

networks:
  elk-basic:
    driver: bridge
```
</details>

## Opciones
### Comprobación de logs
```
docker-compose logs -f kibana
```
### Acceso contenedores
```
sudo docker exec -it <name-container> /bin/bash
```

## Script para automatizar el proceso.
<details>
<summary>
Script despliegue.sh
</summary>

```
#!/bin/bash
# Uso de despliege.sh:
# <namefile.yaml o yml> [up|down|restart]
# Tag para el nombre de project name que usa docker-compose en el despliegue
# Si no se indica un tag coge el nombre del directorio, por ello se personalizaCOMPOSE_FILE="$1"

#===========================================================================
# VARIABLES
#===========================================================================

COMMAND="$2"
PROJECT_NAME="despliegue_elk"

#===========================================================================
# FUNCIONES
#===========================================================================
# Despliegue
function up(){
    echo "Desplegando los contenedores..."
    docker-compose -p "$PROJECT_NAME" -f "$COMPOSE_FILE" up -d
}

# Anular el Despliegue
function down(){
    echo "Deteniendo los contenedores..."
    docker-compose -p "$PROJECT_NAME" -f "$COMPOSE_FILE" down
}

# Reiniciar el Despliegue
function restart(){
    echo "Reiniciando el despliegue..."
    echo "Primero tumbando los microservicios"
    down 2>/dev/null || echo "No se ha podido levantar el sistema"
    sleep 3
    echo "Segundo levantando los microservicios"
    up 2>/dev/null || echo "No se ha podilo levantar el sistema"
}

#===========================================================================
# SWITCH
#===========================================================================
case "$COMMAND" in
    up) up ;;
    down) down ;;
    restart) restart ;;
    *)
    echo
    echo "***********************************************************"
    echo "*							  *"
    echo "*	    Despliegue con DOCKER-COMPOSE		  *"
    echo "*							  *"
    echo "***********************************************************"
     echo "*							  *"
    echo "*	Instrucciones para ejecutar el despliegue	  *"
    echo "*							  *"
    echo "***********************************************************"
    echo "* Para ejecutar el despliegue siga el siguiente patrón:   *"
    echo "*							  *"
    echo "* $0 <nombre fichero YAML> [up|down|restart] *"
    echo "*							  *"
    echo "***********************************************************"
    echo
    exit 1
    ;;
esac
```
</details>