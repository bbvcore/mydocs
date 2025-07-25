---
title: Profiles
---

# Profiles
En sistemas operativos Windows los perfiles dependen del fichero **NTUSER.DAT**, dando lugar ello a varios perfiles con características diferentes como son los siguientes.

## Perfil Local
Se crea en el disco duro local cuando un usuario accede por primera vez al sistema operativo.
- **Path**: \Users\usuarioName
- **Características**: permite un acceso rápido a los datos pero NO permite sincronización entre diferentes equipos.

## Perfil Móvil
Se almacena en un servidor remoto y el usuario al realizar login en cualquier equipo del dominio accede al perfil.
- **Path**: \\servidor\perfiles\usuarioName
- **Características**: disponer del mismo entorno en todos los equipos, es más lento el acceso y puede generar conflictos cuando se realiza el acceso desde diferentes sitios.

## Perfil Obligatorio
Es un perfil móvil que no almacena los datos del usuario, estos cambios son borrados al cerrar sesión.

:::tip[Activar perfil obligatorio]
Para poder utilizar este tipo de perfiles es necesario renombrar el fichero **NTUSER.MAN** por **NTUSER.DAT**.
:::

## Perfil Temporal
Este perfil se crea cuando por algún motivo el OS no es capaz de cargar un determinado perfil de usuario. Al usuario se le notifica dicha situación.
- **Path**: \User\TEMP

:::warning
Dicha situación se produce cuando el perfil es corrupto o se encuentra alterado debido a problemas de permisos o de red.
:::

## Fichero NTUSER.DAT
El fichero **NTUSER.DAT** se encuentra en el directorio del perfil de cada usuario.

```batch
c:\Users\userName\NTUSER.DAT
```
Contiene las preferencias del usuario, las cuales están almacenadas en el registro de Windows las cuales se cargan en las entradas siguientes del mismo

```batch
HKEY_USERS\<SID>
HKEY_CURRENT_USER
```

Para la edición del fichero usar **REGEDIT**, ya que este fichero está configurado como un **fichero hive** *(grupo de claves, subclaves y valores del Registro de Windows)*.

### Manipulación del fichero NTUSER.DAT
Primero hacer una copia de respaldo del fichero, a continuación acceder al registro de Windows.
```batch
regedit
```
Se va a HKEY_USERS,  se escoge **cargar subarbol** y se selecciona el fichero *(ha de ser un usuario distinto al de la sesión actual)*. 
Una vez cargada se ha de generar un nombre temporal para la clave generada, y se procede a editar el perfil, una vez finalizado, se va a archivo y se selecciona "Descargar subárbol".

:::tip[Obtener el SID]
```batch
wmic useraccount get name,sid
```
**Wmic** es un meta comando, entonces hay ayuda para wmic, wmic useraccount, wmic useraccount get...