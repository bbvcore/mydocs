---
sidebar_position: 1
title: Git
---

# Git 
Git es un software open source que realiza las funciones de controlador de versiones.

## Métodos de subida (Push)
### Uso de Key SSH
Desde hace unos años muchos repositorios requieren el uso de una clave SSH, en esta sección se muestra como se configura.
#### Acceso al directorio SSH del OS
```
ls ~/.ssh
```
#### Generación de una clave SSH
```
ssh-keygen -t ed25519 -C "email@dominio.com"
```
:::tip[Dos ficheros]
- id_ed25519 (clave privada)
- id_ed25519.pub (clave pública)
:::

#### Copiar la clave pública SSH
```
cd ~/.ssh
cat id_ed25519.pub
```
El resultado del comando cat se copia al portapapeles para agregar en la cuenta de GitHub.

#### Agregar la clave pública al repositorio Git
En la sección Settings de GitHub se añade la clave en la sección SSH and GPG keys escogiendo la opción New SSH key, añadiendo un nombre y pegando la clave.
```
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIK4+VxM2sWYhGQd2dQDV+lL0/BT1AXbVTqe896xPFVO4 bascore_@hotmail.com
```
#### Comprobar repositorio local

Adecuar repositorio para usar SSH, primero comprobar si está configurado para HTTPS.

```
git remote -v
```
Si muestra origen para el fetch y el push con HTTPS hace falta realizar el cambio a SSH
```
git remote set-url origin git@github.com:usuario/repositorio.git
```
Una vez realizado el cambio ya se puede subir con **git push** los ficheros requeridos, pidiendo previamente persimo para añadiendo el host al repo.