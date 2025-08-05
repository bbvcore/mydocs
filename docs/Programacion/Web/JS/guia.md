---
title: Guía JS
---
# JS
En esta guía de JS se van a realizar un repaso básico de los conceptos a tener en cuenta, habrá enlaces a otra documentación, pero se pretende tener una guía mínima completa funcional en esta entrada de la documentación.
## BOM
El BOM es el modelo de objetos del navegador, los cuales se verán a continuación.

### Objeto Window 
Del Objeto Window dependen los siguientes Objetos
- document: representa el DOM
- location: información sobre la URL
- navigator: información sobre el navegador
- screen: información sobre la pantalla del user
- history: contenido del historial e interacción con el mismo

#### Principales propiedades del Objeto Window
- innerWidth/innerHeight: ancho y altura interior de la ventana
- outerWidth/outerHeight:
- scrollX, scrollY: número de pixeles que el documento ha sido desplazado
- opener: hace referencia a la ventana que abrió otra ventana a través del método open()
:::warning[Reverse tabnabbing]
En los enlaces de apertura de ventanas usar los siguientes tags
```html
target="_blank" rel="noopener" 
```
:::
- localStorage
- sessionStorage
- console

#### Principales métodos del Objeto 
- window.alert()
- window.prompt()
- window.confirm()
- window.open(<url>, <name>, <características>)
:::tip[Características]
Dentro de las características, que van todas en un solo bloque entrecomillado, destacan algunas como son: width, height, left, top, scrollbars, resizable, toolbar, menubar, status, location
:::
- window.close()
- window.scroll(x,y): desplaza a esas coordenadas
- window.scrollTo(x, y)
- window.scrollBy(x, y)
- setInterval()
- clearInterval()
- setTimeout()
- clearTimeOut()
- print()

### Objeto Navigator
#### Principales propiedades
- userAgent: identifica el el navegador y el OS
- appName: nombre del navegador
- appVersion: versión del navegador
- platform: plataforma y OS
- languaje: idioma
- languajes: array de los idiomas
- onLine: valor booleano para comprobar la conectividad a internet
- cookieEnabled: si las cookies están habilitadas
- connection: información de la conexión

#### Principales métodos
- javaEnabled(): si hay soporte para Java
- permisision.query(): permite consultar permisos del navegador
