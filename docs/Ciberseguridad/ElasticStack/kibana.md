---
sidebar_id: 3
title: kibana
---


# Kibana
## Token para instalar Kibana
Es necesario generar un token *justo antes** de *instalar* *Kibana*, dado que el token tiene un *tiempo de vida* de **30 minutos**.
```
sudo /usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana
```
Si se produce un error tipo **"exit 69"** o **"problemas de cluster"** hay que comprobar que **elasticsearch** está correctamente habilitado y activo.
```
sudo systemctl status elasticsearch
sudo systemctl enable elasticsearch
sudo systemctl start elasticsearch
```

### Instalar Kibana
#### Setup de Kibana
 Previamente se **actualiza** también el *OS*.
```
sudo apt update && sudo apt install kibana
```
#### KEYstore
```
Kibana KeyStore en /etc/kibana/kibana.keystore
```

#### Configuración con el token
```
sudo /usr/share/kibana/bin/kibana-setup --enrollment-token "pegar token"
```

#### Finalización del proceso
```
Kibana configured successfully
    To start Kibana run:
    bin/kibana
```

:::tip[Ubicación Kibana]
 - /usr/share/kibana 
:::
 
#### Acceso via web
```
    localhost:5601
```
#### Credenciales
```
    User: elastic
    Password: Generada en la instalación
```

## Posibles problemas durante el procedimiento
En todo proceso pueden suceder algunos problemas, los más destacados relacionados con este software son los siguientes.

### Kibana
1.  Si falla el acceso a kibana comprobar que está activo
```
sudo systemctl enable kibana
sudo systemctln start kibana
```

2.  Si falla reiniciar Kibana y revisar logs
```
sudo sistemctl restart kibana
sudo journalctl -u kibana -f
```
