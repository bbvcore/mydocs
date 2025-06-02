---
sidebar_position: 1
title: Despliegue Defir
---

# Despliegue Defir
## ElasticSearch
### Actualización del sistema
```
sudo apt update && sudo apt upgrade -y
```
### Instalación de Java
```
sudo apt install openjdk-17-jdk -y
```
### Agregar repositorio
#### Descarga de la clave GPG
```
wget -qO - https://artifacts.elastic.co/GPG-KEY-elasticsearch | sudo gpg --dearmor -o /usr/share/keyrings/elasticsearch-keyring.gpg
```
#### Añadir repositorio firmado a sources.list.d
```
echo "deb [signed-by=/usr/share/keyrings/elasticsearch-keyring.gpg] https://artifacts.elastic.co/packages/8.x/apt stable main" | sudo tee /etc/apt/sources.list.d/elastic-8.x.list
```
### Instalar elasticsearch
```
sudo apt update
sudo apt install elasticsearch -y
```
### Habilitar servicio e inicalización
```
sudo systemctl daemon-reexec
sudo systemctl enable elasticsearch
sudo systemctl start elasticsearch
```

### Comprobar el estado del servicio
```
sleep 10
sudo apt install curl
curl -k https://localhost:9200 || echo "Puede estar todavía inicializando el servicio elasticsearch."
```

### Obtención del token para la instalación de Kibana
La vigencia de este token es de 30 minutos
```
sudo /usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana
```

## Instalación de Kibana
### Actualización e instalación 
```
sudo apt update && sudo apt install kibana -y
```
### Habilitar Kibana
```
sudo systemctl enable kibana
```
### Introducir el Token
```
sudo /usr/share/kibana/bin/kibana-setup --enrollment-token "<pegar el token>"
```
### Inicializar Kibana
```
sudo systemctl start kibana
```

## Elastic Agent
Accediendo a la sección **Fleet** yendo a **Add Fleet Server**. 
:::tip[Opciones al añadir el Fleet Server]
- Establecer un nombre.
- Añadir un host, normalmente: https://localhost:8220
- Confirmar el nombre y el host.
- Descargar e instalar el **Fleet Server** en el host Server
donde está instalado ElasticSearch y Kibana. Revisar el código proporcionado y cambiar la IP por localhost de ser necesario.
:::


### Descarga del agente para Linux
```
curl -L -O https://artifacts.elastic.co/downloads/beats/elastic-agent/elastic-agent-8.13.4-linux-x86_64.tar.gz
```
#### Descomprimir el agente
```
tar -xzf elastic-agent-8.13.4-linux-x86_64.tar.gz
```
#### Instalación del agente
:::warning
- La opción --insecure se usa para poder operar sin tener habilitados certificados TLS/SSL y aplicar solo el uso del Token para el enrollment.
:::

```
sudo ./elastic-agent install \
  --url="URL con protocolo del Fleet Server: Puerto" \
  --enrollment-token="Token del enrollment" \
  --insecure
```

## Añadir integración Windows a Fleet
Para poder monitorizar Windows mediante la instalación en ese sistema operativo de Sysmon se debe de agregar la integración de "Windows".

:::tip[Pasos en la interfaz gráfica]
- Add integration
- Buscar "Windows"
- Ir a **Settings** e **Install Windows** donde añade 18 assets
- Add Windows
- Save & continue
:::


### Anexo: Preparación de Windows
#### Sysmon
Desde la Web de Microsoft Learn se realiza la descarga de Sysmon, además también se descarga SwiftOnSecurity para obtener el fichero XML de configuración.
```
.\Sysmon -i --accepteua
.\Sysmon -c <fichero-configuracion.xml>
```


#### Instalación del Agente
Instalarlo como Administrador usando la Power Shell
```
.\elastic-agent.exe install --url=Url Server: Puerto --enrollment-token=Enrollment Token --insecure"
```

