---
sidebar_position: 2
title: Git
---

# Git 
Git es un software open source que realiza las funciones de controlador de versiones.


## Creación de un repositorio local de un repositorio remoto
```bash
git init
git branch -m main
git add .
git commit -m "Primer commit"
# Haciendo uso de HTTPS
git remote add origin <URL_DEL_REPO>
# Haciendo uso de SSH
git remote add origin git@github.com:bbvcore/mydocs.git
# Comprobar el repositorio remoto
git remote -v
## Subir los ficheros 
git push -u origin main # A veces es necesario usar --force
```


## Métodos de subida (Push)
### Uso de Key SSH
Desde hace unos años muchos repositorios requieren el uso de una clave SSH, en esta sección se muestra como se configura.
#### Acceso al directorio SSH del OS
```bash
ls ~/.ssh
```
#### Generación de una clave SSH
```bash
ssh-keygen -t ed25519 -C "email@dominio.com"
```
:::tip[Dos ficheros]
- id_ed25519 (clave privada)
- id_ed25519.pub (clave pública)
:::

#### Copiar la clave pública SSH
```bash
cd ~/.ssh
cat id_ed25519.pub
```
El resultado del comando cat se copia al portapapeles para agregar en la cuenta de GitHub.

#### Agregar la clave pública al repositorio Git
En la sección Settings de GitHub se añade la clave en la sección SSH and GPG keys escogiendo la opción New SSH key, añadiendo un nombre y pegando la clave.

```bash
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5BBVBBIK4+VxM2sWYhGQd2dQDV+lL0/BT1AXbVTqe896xPFVO4 bbvcore@github.io
```
#### Comprobar repositorio local

Adecuar repositorio para usar SSH, primero comprobar si está configurado para HTTPS.

```bash
git remote -v
```
Si muestra origen para el fetch y el push con HTTPS hace falta realizar el cambio a SSH

```bash
git remote set-url origin git@github.com:usuario/repositorio.git
```
Una vez realizado el cambio ya se puede subir con **git push** los ficheros requeridos, pidiendo previamente persimo para añadiendo el host al repo.