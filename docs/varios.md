---
title: varios
---
# Básico pentesting
## Linux
### Acceso remoto
#### SSH
```bash
ssh -L port:host-local:port user@IP/domain
```
#### Netcat

### Captura tráfico
#### TCPdump
```bash 
tcpdump -i "<interface>" "<port>" "<fichero>"
```
### Bases de datos
#### SQLmap
```
sqlmap -r sqli-accept-cat.req -p catName --level=5 --tables --dump --risk=3 ---dbms=sqlite
--threads=10
```
### Fuzzing
#### Gospider
```bash
gospider -s
```
#### Dirsearch
```bash
dirsearch -u
```
#### Feroxbuster
```bash 
feroxbuster -u "<host>" -w "<wordlist>"
```
#### Ffuc
```bash
ffuc -c -u "<host>" -H "host:FUZZ.<target-url>"
```
### XSS
Cross Site Scripting para llevar a cabo inyección JS de código malicioso en páginas web.
#### XSS Reflejado
El payload viaja en la petición **HTTP** donse se *"refleja"* el código en el HTML si no hay sanitización, de esta forma de esta forma el servidor lo incrusta en el HTML que devuelve y de ahí el problema potencial. Este código iría en un input de HTML o podría ir en la URL.
```javascript
<script>alert("Codigo XSS reflejado")</script>
```
Este payload iría **dentro** del <u>código HTML</u> **que devuelve el servidor** <u>sin haberlo sanitizado</u> y se intepretaría como JS, dando lugar a la posibilidad de ejecución de código JS malicioso.

#### XSS Almacenado
Este caso es más grave que el **XSS** reflejado porque ahora el código se almacena en una base de datos y puede ser ejecutado multiples veces.
Además de en una base de datos podría ser almacenado en otros lugares, como ficheros de configuración, logs del sistema o en la memoria caché.
```javascript
<script>while(true){};</script>
```
En este caso sería la ejecución de un **loop infinito** que podría provocar la imposibilidad del uso de un sistema online por parte de los usuarios al generarse un bloqueo del navegador del cliente mientras se consultaba algún valor de la aplicación web.
```php
<?php
$id = $_GET['id'];
$conn = new mysqli("localhost", "root", "", "xss_attack");
$res = $conn->query("SELECT * FROM productos WHERE id=$id");
$row = $res->fetch_assoc();
echo "<h1>".$row['nombre']."</h1>";
echo "<p>".$row['descripcion']."</p>"; 
?>
```
Al realizar esta consulta y al acceder a los datos introducidos sin sanitización tiene lugar el ataque de XSS.

#### XSS DOM
La vulnerabilidad está en el cliente, es decir en el navegador web del usuario, donde el script puede leer datos del navegador de los objetos del **DOM**, puede afectar al **BOM**, pero normalmente las acciones acaban realizándose en el **DOM**, por ello para simplificar se le denomina DOM.
```html
<div id="div-donde-incrustrar"></div>
```
```javascript
document.getElementById("div-donde-incrustrar").innerHTML = location.hash.substring(1);
```
De esta forma se consigue el código que viaja después del hash, y con el método substring con el argumento 1, indica que empieza la cadena a almacenar desde la posición 1, que es donde empieza el código del script, de esta forma se omite coger la almohadilla (#)
```html
http://localhost/pagina-atacada.html#<script>while(true){}</script>
```
Mediante una url se pasa el script a insertar en la página HTML. Por ello para poder ejecutar o explotar esta vulnerabilidad la página web debería de leer datos de la URL como de location.hash o location.search e incluso location.pathname, y luego insertarlos dentro del HTML con algún método potencialmente inseguro como innerHTML.

## Windows
### Crackmapexec
Herramientas netexec
### BloodHound
Herramienta para inspeccionar objetos de Directorio Activo, requiere del sistema gestor de base de datos neo4j y de una interfaz gráfica para visualizar los datos del AD obtenidos como objetos JSON.
#### Bloodhound-python
Recolector de datos del directorio activo para bloodhound
#### Bloodhound-AD
Permite cambiar passwords de usuarios a raíz de una credenciales válidas en el sistema
#### Evil-WinRM
Permite explotar WinRM para poder acceder de forma remota a equipos windows mediante sesión de consola power shell.