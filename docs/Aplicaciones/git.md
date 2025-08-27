---
sidebar_position: 2
title: Git
---

# &#9881; Git 
Git es un software open source que realiza las funciones de controlador de versiones.


## &#x1F3B2; Comandos básicos 

### &#x2699; Configurar cuenta 

:::warning
Si no se especifica un nivel se configura por defecto como local.
:::
```bash
git config --global user.name
git config --global user.email
```
:::info[]
- **git.local** afecta solo al directorio del proyecto en el equipo
- **git.global** afecta a todos los repositorios en el equipo
- **git.system** afecta a todos los usuarios y a todos los repositorios en el equipo
:::
Para eliminar una configuración se utiliza el parámetro **unset**.
```bash
git config --global --unset user.email
```
### &#x27BF; Mergear 

```bash
git checkout <nameBranch> # cambia de rama
git pull origin <nameBranch> # actualiza la rama
git merge <nameBranch> # hace merge
git push origin <nameBranch> # sube al repositorio
```
Cuando se hace merge pueden haber cambios que merge no notifica como conflicto de versiones, y suele pasar cuando los cambios se producen en el mismo fichero, es decir existe el mismo fichero pero tiene cambios que git entiende menores, aunque igual no son tan menores.

En sintesis merge actua por defecto de la siguiente forma:
- Si son distintos los ficheros mergea sin preguntar
- Si son iguales y tienen el mismo contenido también mergea sin problemas
- Si son iguales y tienen distinto contenido se establece un conflicto y toca comprobar las diferencias

#### :warning: Soluciones a merges problemáticos
```bash
git status # indica conflictos
git status -s 
git show # info de objetos
```
:::tip
- untracked (work directory): fichero creado
- modified (add): staged
- commited (commit)
- Simbolos:
1. ?: no tracked
2. A: add
3. AM: add y modified
- Colores:
1. Rojo: modificado
2. Verde: sin modificar
:::


### &#x1F333; Ramas 

### &#x1F4DA; Cambiar de ramas 

```bash
git branch
git checkout -b
git switch -c
```

#### &#x270F; Borrar ramas 

```bash
git branch -d <nameBranch>
git push origin --delete <nameBranch>
```

#### &#x2696; Comparar 

```bash
git diff # compara cambios
git diff rama1..rama2
git diff rama1..rama2 --fichero
```
:::tip
Si un fichero NO existe en una rama, git sabe que NO existe, pero NO sabe si es que no existió o que fue borrado
:::

#### &#x1F4CB; Listar ficheros de la rama 

```bash
git ls-tre --name-only "<branch>"
```
### &#x1F4C1; &#x1F4C1; Clonar repositorio 


```bash
git clone <PathRepository>
```

## &#x1F916; Rebase 

El método rebase en git sirve para posicionar 2 ramas en una sola posicionando una sobre otra, de ahí el concepto rebasar, es como poner 2 ramas en una misma línea partiendo la segunda rama desde un determinado commit de la primera rama. El método rebase del comando git permite abrir una shell interactiva con el parámetro -i para poder editar el commit escogido.

Con esta fusión de ramas se obtiene un historial limpio, esta forma es ideal para trabajar en solitario pero en proyectos es más recomendado usar merge ya que conserva todos los commits tal cual. El historial de commits con rebase de la rama 2 sobre la 1 se inicializa desde el punto que hace de Head en la rama 1, entonces los commits de la rama 2 se reescriben con nuevos hashes al haber cambiado el commit número 1 de la rama2 al ser actualmente el commit número 1 el punto de la rama 1 donde se ubico el Head antes del rebase.

## &#x1F449; Detached HEAD 

Es cuando un HEADapunta directamente a un commit y no a una rama, esta acción pasa cuando se hace el uso de git checkout con un hash.

Si se hace un cambio en esta caso, el commit no pertenece a  ninguna rama, por ello se suele almacenar estos cambios en una nueva rama con git checkout -b, aunque se puede volver a la rama existente y si no hay conflicto en los cambios ni se hace commit no debería de haber problemas, por ello si se hacen cambios, esos commit quedan en un limbo y lo mejor es crear una rama nueva para guardar los cambios.

Para evitar estos problemas, si se necesita editar un commit lo mejor es usar rebase -i.

## &#x2328; Git stash 

Permite editar y guardar los cambios no modificados en una pila especial donde nunca se perderán salvo que se borren y además se pueden aplicar en una rama si interesa mediante git apply, además se puede consultar la pila con git stash list. Con git stash pop se puede aplicar el stash y borrarlo del stack, al contrario que apply que lo aplica pero sigue en el stack.
Si se quiere borrar un elemento de la pila de stash determinado se puede hacer uso de git stash drop stash@{n}. Los procesos de git stash quedan en el directorio de trabajo, una vez aplicados hace falta un commit también. Para aplicar un determinado cambio de la pila, se busca en la lista y luego se usa git stash apply stash@{indice númerico}


## &#128189; Creación de un repositorio local de un repositorio remoto
```bash
git init
git branch -m main
git add .
git commit -m "Primer commit"
# Haciendo uso de HTTPS
git remote add origin <URL_DEL_REPO>
# Haciendo uso de SSH
git remote add origin git@github.com:<repo_name>.git
# Comprobar el repositorio remoto
git remote -v
## Subir los ficheros 
git push -u origin main # A veces es necesario usar --force
```

## &#127760; Métodos de subida (Push)
### Uso de Key SSH
Desde hace unos años muchos repositorios requieren el uso de una **clave SSH**, en esta sección se muestra como se configura.
#### &#128193; Acceso al directorio SSH del OS
```bash
ls ~/.ssh
```
#### &#128273; Generación de una clave SSH
```bash
ssh-keygen -t ed25519 -C "email@dominio.com"
```
:::tip[Dos ficheros]
- id_ed25519 (clave privada)
- id_ed25519.pub (clave pública)
:::

#### &#128273; Copiar la clave pública SSH
```bash
cd ~/.ssh
cat id_ed25519.pub
```
El resultado del comando cat se copia al portapapeles para agregar en la cuenta de GitHub.

#### &#128196; Agregar la clave pública al repositorio Git
En la sección Settings de GitHub se añade la clave en la sección SSH and GPG keys escogiendo la opción New SSH key, añadiendo un nombre y pegando la clave.

```bash
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5BBVBBIK4+VxM2sWYhGQd2dQDV+lL0/BT1AXbVTqe896xPFVO4 bbvcore@github.io
```
#### &#128190; Comprobar repositorio local

Adecuar repositorio para usar SSH, primero comprobar si está configurado para HTTPS.

```bash
git remote -v
```
Si muestra origen para el fetch y el push con HTTPS hace falta realizar el cambio a SSH

```bash
git remote set-url origin git@github.com:usuario/repositorio.git
```
Una vez realizado el cambio ya se puede subir con **git push** los ficheros requeridos, pidiendo previamente persimo para añadiendo el host al repo.