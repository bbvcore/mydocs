---
title: Laravel CRUD
sidebar_id: 1
---
# Laravel Crud
## Previo
### Servidor web
```bash
sudo apt install apache2
```
### Composer
```bash
sudo apt install composer
```
### Librería PHP y XML
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

Si da error en laravel con sqlite hay que crear la migración con los siguientes comandos

```bash
php artisan session:table
php artisan migrate
```

## Crud
