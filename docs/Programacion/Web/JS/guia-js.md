---
title: Guía JS
---
# JS
En esta guía de JS se van a realizar un repaso básico de los conceptos a tener en cuenta, habrá enlaces a otra documentación, pero se pretende tener una guía mínima completa funcional en esta entrada de la documentación.
## BOM
El BOM es el modelo de objetos del navegador, los cuales se verán a continuación.

### Objeto Window 
<details>
<summary>
Del Objeto Window dependen los siguientes Objetos que forman parte del <b>BOM</b>
</summary>

- **document**: *representa el DOM*
- **location**: *información sobre la URL*
- **navigator**: *información sobre el navegador*
- **screen**: *información sobre la pantalla del user*
- **history**: *contenido del historial e interacción con el mismo*

</details>

#### Principales propiedades del Objeto Window
<details>
<summary>
Relación de las principales propiedades del Objeto <b>Window</b>
</summary>

- **innerWidth/innerHeight**: *ancho y altura interior de la ventana*
- **outerWidth/outerHeight**:
- **scrollX, scrollY**: *número de pixeles que el documento ha sido desplazado*
- **opener**: *hace referencia a la ventana que abrió otra ventana a través del método open()*
:::warning[Reverse tabnabbing]
En los enlaces de apertura de ventanas usar los siguientes tags
```html
target="_blank" rel="noopener" 
```
:::
- **storage**: *es un objeto que permite almacenar valores, existen dos implementaciones diferentes, **localStorage** y **sessionStoraga***
- **console^**: permite mostrar datos por consola, dispone de uno interesantes métodos como son, log(), dir(), error().

</details>


#### Principales métodos del Objeto Window
<details>
<summary>
Relación de los principales métodos del Objeto <b>Window</b>
</summary>


- **window.alert()**
- **window.prompt()**
- **window.confirm()**
- **window.open(url, name, características)**

:::tip[Características]
Dentro de las características, que van todas en un solo bloque entrecomillado, destacan algunas como son: width, height, left, top, scrollbars, resizable, toolbar, menubar, status, location
:::

- **window.close()**
- **window.scroll(x,y): desplaza a esas coordenadas**
- **window.scrollTo(x, y)**
- **window.scrollBy(x, y)**
- **setInterval()**
- **clearInterval()**
- **setTimeout()**
- **clearTimeOut()**
- **print()**

</details>

### Objeto Document
Del objeto Document cuelgan las tags y elementos HTML que se manipulan en las páginas web para la muestra de contenido o la interacción con el usuario, de ahí que surja el modelo **DOM**.

:::tip[DOM]
El **DOM** *(Document Object Model) es el modelo de objetos del documento
:::

#### Principales propiedades del Objeto Document
<details>
<summary>
Relación de las principales propiedades del Objeto <b>Window</b>
</summary>

- **title**: *título del documento, el título de la página*
- **body**: *elemento HTML del body de la página*
- **head**: *elemento HTML del head de la página*
- **URL**: *devuelve la URL*
- **domain**: *devuelve el dominio*
- **cookie**: *permite la lectura de cookies*
- **readyState**: *nivel de carga del documento*

</details>

#### Principales métodos del Objeto Document
<details>
<summary>
Relación de los principales métodos del Objeto <b>Window</b>
</summary>

- **getElementById**
- **getElementsByClassName**
- **getElementsByTagName**
- **querySelector**
- **querySelectorAll**
- **createElement**
- **createTextNode**
- **appenchild**
- **removeChild**
- **replaceChild**
- **write**
- **open/close:** *abre / cierra el flujo de escritura*
- **addEventListener**

</details>

### Objeto Location
#### Principales propiedades del Objeto Location
<details>
<summary>
Relación de las principales propiedades del Objeto Location
</summary>

- **href**: *URL completa, para leer o redireccionar.*
- **origin**: *muestra el Protocolo, el Host y el Puerto.*
- **protocolo**: *muestra el protocolo de la URL*
- **host**: *muestra el Hostname y el Puerto*
- **hostname**: *muestra solo el dominio*
- **port**: *muestra solo el puerto*
- **pathname**: *muestra la URL después del Hostname (/pathname)*
- **search**: *las queries (?)*
- **hash**: *las anclas (#)*

</details>

#### Principales métodos del Objeto Location
<details>
<summary>
Relación de los principales métodos del Objeto <b>Location</b>
</summary>

- **assing**: *permite la cargade una nueva URL (forma parte del historial)*
- **replace:** *carga una nueva URL (no se puede volver atrás, no forma parte del historial)*
- **reload**: *recarga la URL*
- **toString**: *devuelve una URL como una cadena*
- **valueOf**: *devuelve el objeto*

</details>


### Objeto Navigator
#### Principales propiedades del Objeto Navigator
<details>
<summary>
Listado de las principales propiedades del objeto <b>Navigator</b>
</summary>

- **userAgent**: *identifica el el navegador y el OS*
- **appName**: *nombre del navegador*
- **appVersion**: *versión del navegador*
- **platform**: *plataforma y OS*
- **languaje**: *idioma*
- **languajes**: *array de los idiomas*
- **onLine**: *valor booleano para comprobar la conectividad a internet*
- **cookieEnabled**: *si las cookies están habilitadas*
- **connection**: *información de la conexión*
</details>

#### Principales métodos del Objeto Navigator
<details>
<summary>
Listado de los principales métodos del objeto <b>Navigator</b>
</summary>

- javaEnabled(): si hay soporte para Java
- permissions.query(): permite consultar permisos del navegador
</details>

:::tip[Ayuda rápida]
- En el navegador web, en la consola (F12) se pueden realizar consultas sobre las propiedades y métodos de los objetos del BOM, usando console.log o console.dir. También se puede afinar la consulta de la siguiente manera.
```javascript
console.log(Object.getOwnPropertyNames(location))
```
<details>
<summary>
Obtención del array con las propiedades y métodos del objeto <b>Navigator</b>
</summary>

```javascript

Array(14) [ "href", "origin", "protocol", "host", "hostname", "port", "pathname", "search", "hash", "assign", … ]​
0: "href"
1: "origin"
2: "protocol"
3: "host"
4: "hostname"
5: "port"
6: "pathname"
7: "search"
8: "hash"
9: "assign"
10: "replace"
11: "reload"
12: "toString"
13: "valueOf"
​
length: 14
```

</details>
:::


### Objeto History
#### Principales propiedades del Objeto History
<details>
<summary>
Listado de las principales propiedades del objeto <b>History</b>
</summary>

- **length**: *contenido de registros en el historial*
- **scrollRestoration**: *control del scroll en páginas SPA, mediante auto intentará volver a la página anterior, pero con manual se puede especificar el scroll y donde ir, algo muy útil en SPA dado el estilo de programación de este estilo que simula en un solo documento la carga de páginas*

</details>

#### Principales métodos del Objeto History
<details>
<summary>
Listado de los principales métodos del objeto <b>History</b>
</summary>

- **back**: *retrocede en el historial*
- **forward**: *avanzar en el historial*
- **go**: *va a una determinada posición en el historial
- **pushState(state, title, url)**: añade una entrada al historial sin refresco de página. Especialmente útil para páginas SPA.*
- **replaceState(state, title, url)**: *reemplaza la entrada del historial*
- **state**: *el estado actual si se ha usado pushState para agregar una entrada al historial.*

</details>


### Objeto Screen
#### Principales propiedades del Objeto Screen
<details>
<summary>
Listado de los principales propiedades del objeto <b>Screen</b>
</summary>

- **width**: *ancho de pantalla*
- **height**: *altura de la pantalla*
- **availWidth**: *ancho de pantalla disponible*
- **availHeight**: *altura de pantalla disponible*
- **colorDepth**: *número bits profundidad color*
- **pixelDepth**: *profundidad de color (suele ser como colorDepth)*
- **orientation**: *orientación de la pantalla*

</details>

#### Principales métodos del Objeto Screen
<details>
<summary>
Listado de los principales métodos del objeto <b>Screen</b>
</summary>

- **orientation.lock**: *bloquear la pantalla*
- **orientation.unlock**: *desbloquear la pantalla*

</details>

## Asíncronia
La ejecución habitual de un código de JS es sincrona, pero hay veces que la funcionalidad implementada requiere realizar acciones que consumen un determinado tiempo, como pueden ser la consulta a una base de datos o a una API, en estos casos se utiliza la asíncronia.

### Herramientas asíncronas
#### Callbacks
Los callbacks son funciones que se pasan como argumento de otra función para su posterior ejecución.
```javascript
// Se define una función llamada welcome que utiliza 2 parámetros, los argumentos de estos parámetros son el valor del name y la funcionalidad de la función callback
const welcome = (name, callback) => {
    alert("Bienvenido ", name)
    callback()
}

// Se realiza la ejecución de la función previamente declarada y se le pasan los argumentos adecuados a los parámetros definidos, es decir el valor de name y el código de la función, en este caso se usa una función anomina con notación arrow
welcome("Borja", ()=>{
    console.log("Código a ejecutar desde la función callback pasada como argumento")
})
```
## Promesas
```javascript
const p = new Promise((resolve, reject)=>{
    let status_ok = true
    if (status_ok){
        resolve()  
    }else{
        reject()
    }
})
p
.then(r=> console.log(r))
.catch(e=> console.log(e))
```

## Async/Await
```javascript
const waiting = (ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

const start = async () => {
  console.log("Iniciar");
  await waiting(5000);
  console.log("Temporizador de 5 segundos");
}

ejecutar();

```

## Event Loop
El sistema de gestión de asincronía en **JS** se llama **Event Loop**, el cual va ejecutando el código sincrono mientras gestiona la pila de código asíncrono, para gestionar las tareas asíncronas cuando las sincronas finalicen.
```javascript
const getUsers => async() {
  try {
    const answer = await fetch("https://jsonplaceholder.typicode.com/users");

        if (!answer.ok) {
            throw new Error("Error al obtener los datos");
        }

        const data = await answer.json();
        console.log("Usuarios:", data);
  } catch (error) {
        console.error("Error:", error.message);
  }
}

getUsers();
```



