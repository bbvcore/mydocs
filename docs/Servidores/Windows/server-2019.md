--- 
sidebar_position: 2
title: Windows Server
---

# Windows Server 
En este caso me centro en la versión 2022, la ISO de evaluación que permite Microsoft descargar para probar.

## Instalación
Inicialmente sale un script donde se dan una serie de opciones de configuración, en principio es todo lo lógico al estándar con lo cual si no se requiere hacer cambios y se pretende acceder ya al Windows Server se ha de escoger la opción 13.

:::tip[Comprobar versión Windows]
Desde la powershell con el comando.
```PS
Get-WindowsEdition -Online
```
En este caso al ser una versión de evaluación, al reiniciar vuelve al script (sconfig) y entonces la opción que se ha de escoger es la 15, que nos permite salir a la Power Shell y allí se presentan varios escenarios posibles:
### Está instalado Windows Server
```PS
explorer
```
### No está instalado Windows Server
```PS
start powershell
Install-WindowsFeature Server-Gui-Mgmt-Infra, Server-Gui-Shell -Restart
```
Si no permite instalar la interfaz gráfica, como es el caso se va a realizar el procedimiento por consola PowerSehell

```ps
// Renombrar máquina
Rename-Computer -NewName server-bas -Restart 
// Añadir IP
New-NetIPAddress -InterfaceAlias "Ethernet" -IPAddress 192.168.1.200 -PrefixLength 24 -DefaultGateway 192.168.1.1
// Dirección DNS cliente
Set-DnsClientServerAddress -InterfaceAlias "Ethernet" -ServerAddresses 192.168.1.200
// Instalar AD
Install-WindowsFeature AD-Domain-Services -IncludeManagementTools
// Promocionar a DC
Import-Module ADDSDeployment

// Instar el bosque del DC
Install-ADDSForest `
  -DomainName "bbv.local" `
  -DomainNetbiosName "BBV" `
  -SafeModeAdministratorPassword (ConvertTo-SecureString "4dm1n_2025" -AsPlainText -Force) `
  -Force:$true

// Comprobar instalación
Get-ADDomain
Get-ADForest

// Zona inversa
Add-DnsServerPrimaryZone -NetworkId "192.168.1.0" -ReplicationScope "Domain"

// Comprobación
Get-DnsServerZone
// Ver los recursos en la zona inversa

Get-DnsServerResourceRecord -ZoneName "1.168.192.in-addr.arpa"


```

:::tip[Comando clásicos desde CMD]
```batch
- dcpromo.exe, para promocionar a controlador de dominio (desde 2003)
- ocsetup.exe
- servermanagercmd.exe
```