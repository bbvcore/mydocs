---
sidebar_position: 1
title: Firewall Windows Defender
---
# :dart: Firewall Windows Defender

## Básico
### :unlock: Desactivar Firewall
```batch
netsh advfirewall set allprofiles state off
```
### :lock: Activar Firewall
```batch
netsh advfirewall set allprofiles state on
```
### :recycle: Resetear Firewall
```batch
netsh advfirewall reset
```
## Reglas
### Bloquear tráfico entrante a servidor local
```batch
netsh advfirewall firewall add rule name="Bloquear HTTP de entrada" dir=in action=block protocol=TCP localport=80
netsh advfirewall firewall add rule name="Bloquear HTTPS de entrada" dir=in action=block protocol=TCP localport=443
```

### Bloquear tráfico entrante del navegador
```batch
netsh advfirewall firewall add rule name="Bloquear HTTP de entrada" dir=in action=block protocol=TCP remoteport=80
netsh advfirewall firewall add rule name="Bloquear HTTPS de entrada" dir=in action=block protocol=TCP remoteport=443
```

### Bloquear tráfico saliente a servidor local
```batch
netsh advfirewall firewall add rule name="Bloquear HTTP de salida" dir=out action=block protocol=TCP localport=80
netsh advfirewall firewall add rule name="Bloquear HTTPS de salida" dir=out action=block protocol=TCP localport=443
```

### Bloquear tráfico de entrada al servidor local
```batch
netsh advfirewall firewall add rule name="Bloquear HTTP de entrada" dir=in action=block protocol=TCP remoteport=80
netsh advfirewall firewall add rule name="Bloquear HTTPS de entrada" dir=in action=block protocol=TCP remoteport=443
```



### Verificar las reglas
```batch
netsh advfirewall firewall show rule name="Bloquear HTTP de entrada"
```
<details>
<summary>
Ejemplo del resultado de la consulta sobre la regla "Bloquear HTTP de entrada"
</summary>

```batch

Nombre de regla:                      Bloquear HTTP de entrada
----------------------------------------------------------------------
Habilitada:                           Sí
Dirección:                            Fuera
Perfiles:                             Dominio,Privada,Pública
Agrupamiento:
LocalIP:                              Cualquiera
RemoteIP:                             Cualquiera
Protocolo:                            TCP
LocalPort:                            Cualquiera
RemotePort:                           80
Cruce seguro del perímetro:          No
Acción:                               Bloquear

Nombre de regla:                      Bloquear HTTP de entrada
----------------------------------------------------------------------
Habilitada:                           Sí
Dirección:                            Dentro
Perfiles:                             Dominio,Privada,Pública
Agrupamiento:
LocalIP:                              Cualquiera
RemoteIP:                             Cualquiera
Protocolo:                            TCP
LocalPort:                            Cualquiera
RemotePort:                           80
Cruce seguro del perímetro:          No
Acción:                               Bloquear

Nombre de regla:                      Bloquear HTTP de entrada
----------------------------------------------------------------------
Habilitada:                           Sí
Dirección:                            Dentro
Perfiles:                             Dominio,Privada,Pública
Agrupamiento:
LocalIP:                              Cualquiera
RemoteIP:                             Cualquiera
Protocolo:                            TCP
LocalPort:                            80
RemotePort:                           Cualquiera
Cruce seguro del perímetro:          No
Acción:                               Bloquear
Aceptar
```

</details>

### Borrar las reglas, perfiles o propiedades
```batch
netsh advfirewall firewall delete rule name="<nombre regla>"
```

<details>
<summary>
Ejemplo de borrado de reglas
</summary>

```batch
netsh advfirewall firewall delete rule name="Bloquear HTTP de entrada"

Se eliminaron 3 reglas.
Aceptar
```
</details>

:::tip[Puertos principales]
- 22 (SSH)
- 21 (FTP)
- 23 (Telnet)
- 25 (SMTP) - 587 
- 53 (DNS)
- 25 (SMTP)
- 80 (HTTP) - 443
- 110 (POP3) - 995
- 143 (IMAP) - 993
:::

