
# Servidores Web con SSL

## Requisitos previos
### Certificado autofirmado
Se ha de haber creado un certificado autofirmado y una clave privada, que ambos se almacenarán en sus correspondientes directorios en el sistema operativo.

```bash
/etc/ssl/certs
/etc/ssl/private
```
## Configuracion Apache
Para utilizar SSL con Apache se ha de crear un virtual host o modificar uno existente y añadir el soporte SSL al puerto 443.
### Host virtual
Su ubicación varia en función del OS, en este caso hablo desde GNU/Linux, donde su ubicación es la siguiente:
```bash
/etc/apache2/sites-avaliable
```
En este directorio se crea un fichero para configurar el virtual host en el puerto 443
```
sudo dominio-local-ssl.conf
```
<details>
<summary>
Contenido del servidor virtual
</summary>

```
<VirtualHost *:443>
    ServerName ssl.local
    ServerAlias www.ssl.local
    
    DocumentRoot /var/www/html
    
    SSLEngine on
    SSLCertificateFile <path>
    SSLCertificateKeyFile <path>
    
    <Directory /var/www/html>
        Options Indexes FollowSymLinks # Permite mostrar ficheros en directorio sin index y seguir enlaces simbolicos
        AllowOverride All # Permite .htaccess para sobrescribir configuraciones
        Require all granted # Sustituto del Allow from all
    </Directory>

    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined

</VirtualHost>
```

</details>

Una vez creado el fichero se procede a activarlo
```
sudo a2ensite ssl-local.conf
```
### Redireccionamiento de http a https
Buscar el virtualhost que escucha el puerto 80 y proceder a realizar un redireccionamiento permanente
```bash
    ServerName tu_dominio.com
    Redirect permanent / https://tu_dominio.com/
```


#### Comandos básicos

- **a2enmod**:
- **a2ensite**:
- **a2dismod**:
- **a2dissite**:
- **a2enconf**:
- **a2disconf**:


Los ficheros de conf se suelen solo activar o desactivar, no editar, son extras para configurar y complementar **apache2.conf**.

Los comandos para los módulos se usan solo en GNU/Linux, en Windows se activan comentando o descomentando los módulos porque se usan líneas LoadModule.


:::warning[Virtual Hosts]
Los **virtual host** en windows se suelen configurar en el fichero principal, que está ubicado en **\conf\httpd.conf**, o también en el fichero **\conf\extra\httpd-vhosts.conf**
:::


## Configuración Nginx

### Certificados
En los directorios comentados anteriormente para Apache, ya que los certificados son comunes a todos los servicios desplegados dentro del OS.

### Configuración de servidor Https
Se ha de editar el fichero de configuración
```
/etc/nginx/sites-avaliable/nameDominio
```
Y dentro de se especifican las características del servicio que se desplegara en Nginx. 
```
# Servidor en el puerto 80
server{
    listen 80;
    server_name: nginx.local, www.nginx.local;
    return 301 https://$host$request_uri; # Redireccionamiento
}

# Servidor en el puerto 443
server{
    listen 443 ssl;
    server_name: nginx.local www.nginx.local;
    
    ssl_certificate <path>
    ssl_certificate_key <path>
    
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;
    
    root /var/www/<dominio_dir>;
    index index.html index.htm;
    
    location / {
        try_files $uri $uri/=404; # $uri busca file o dir, sino 404
    }
}
```

Habilitar el servicio
```
sudo ln -s /etc/nginx/sites-available/tu_dominio /etc/nginx/sites-enabled/
sudo nginx -t # Valida el fichero de configuración sin reiniciar nginx
```



























