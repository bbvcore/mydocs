---
title: Laravel CRUD
sidebar_id: 1
---
# Laravel Crud
## Previo
En este documento se traza como instalar y configurar el marco de trabajo de laravel para llevar a cabo un sistema CRUD para establecer un servicio de login en una aplicación.

Se parte de 0 en la configuración del entorno de trabajo, es decir servidor web, php, composer, etc.

### Servidor web
```bash
sudo apt install apache2
```
### Composer
```bash
sudo apt install composer
```
### Librería PHP y XML
Instalar esta librería para soporte XML y acceso al DOM por parte del framework, en Linux debido al procedimiento de ser modular y minimalista no viene por defecto instalada tras instalar Php.
```bash
sudo apt update
sudo apt install php8.3-xml
```
### Crear proyecto Laravel
```bash
mkdir projectNamecomp
composer create-project laravel/laravel
```
### Activar e instalar SQLite
```bash
sudo apt install php-sqlite3
```

Editar el fichero php.ini y descomentar la siguiente línea

```php
;extension=sqlite3
``` 

## Levantar servidor
```bash
php artisan serve
```

### Error con SQLite
Si da error en laravel con sqlite hay que crear la migración con los siguientes comandos

```bash
touch database/database.sqlite
php artisan session:table
php artisan migrate
```
### Error AppKey
Se genera una Key con el siguiente comando
```bash
php artisan key:generate
```
Y se comprueba que todo sea correcto con el comando siguiente para ver el contenido del fichero oculto .env
```bash
cat .env
APP_KEY=base64:giukhkG+DuWOOc26aOXBxbz89c4...=
```
## Login



## Crud

