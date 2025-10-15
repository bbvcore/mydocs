---
title: powershell
---
# Powershell

## Creación / modificación / eliminación de dir / files
- **get-location**: como **pwd**
- **set-location**: acceder a un directorio, como **cd**
- **get-childitem**: listar los ficheros y directorios
- **new-item**: creación de ficheros o directorios
```ps
New-item -ItemType File  file.txt
New-item -ItemType Directory  dirName
```
- **copy-item**: copiar ficheros
```ps
copy-item file1.txt file1-copiado.txt
```
- **move-item**: mover ficheros
```ps
move-item file1.txt /tmp/
```
- **remove-item**: eliminar ficheros o directorios
- **get-content**: ver contenido de un fichero
- **clear-host**: limpiar la pantalla

## Información del sistema
- **get-computerinfo**: información del sistema
- **get-localuser**: lista de usuarios locales
- **get-localgroup**: lista de grupos locales
- **get-process**: listar los procesos del sistema
- **get-services**: listar los servicios del sistema
- **get-netIPAddress**: ver la dirección de red

## Ayuda
- **get-command**: lista de comandos
- **get-help (name command)**: ayuda sobre un comando

## Permisos de ejecución de ficheros .ps1
Para evitar restricciones de seguridad y poder probar scripts se puede usar
```ps
Set-ExecutionPolicy Unrestricted
```

## Texto y pipelines
```ps
write-verbose "ejecutando script" # Solo si se ejecuta con verbose -verbose
write-host "soy el puto amo" # escribir en el host
write-output "saliendo" # stdout (pipeline)
```