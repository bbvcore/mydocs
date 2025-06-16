---
sidebar_position: 1
title: Firewall Windows Defender
---
# :dart: Firewall Windows Defender
Se trata del cortafuegos de Windows para el control del tráfico entrante y saliente en Windows, forma parte de Windows Defender Security Center.

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

:::warning
Las reglas para la gestión del cortafuegos de Windows se están llevando a cabo con **netsh** para que sea más compatible con Windows al poder ejecutarse desde cualquier versión de Windows al ser ejecutables desde **CMD** y no hacer falta la **Power Shell**
:::

#### Anexo: Power Shell
El cortafuegos puede gestionarse desde la **Power Shell** con comandos básicos como los siguientes.
```powershell
New-NetFirewallRule -DisplayName "Nombre regla" -Direction "" -Protocol "" -LocalPort -Action
Remove-NetFirewallRule -DisplayName "Nombre regla"
Set-NetFirewallProfile -Profile Domain,Public,Private -Enabled True
Set-NetFirewallProfile -Profile Domain,Public,Private -Enabled False
```
:::tip[Resetear reglas en PowerShell]
Curiosamente para resetear las reglas, es necesario usar **netsh**, no existe un CMD-LET para tal fin
:::


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

