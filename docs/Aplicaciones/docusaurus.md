---
sidebar_position: 1
title: Docusaurus 
---

# &#129429; Docusaurus 
Docusaurus es una aplicación para la creación de sitios web estáticos para la generación de documentación usando markdown y también es compatible con HTML. Creado por Facebook y basado en React.



## Pasos previos
Es necesario contar con **nodejs** y con su gestor de dependencias **npm**
```bash 
sudo apt update && sudo apt install nodejs npm -y
```
Comprobación de las versiones instaladas
```bash
node -v
npm -v
```

## &#128190; Instalación
```bash
npx create-docusaurus@latest <nombre> <classic>
cd nombre
npm install
npm run start
```

## &#128194; Estructura y ficheros de interés
La estructura de un proyecto base es la siguiente:

- **docs**: aloja la documentación en markdown.
- **src**: código de React y componentes.
- **blog**: sección para elaborar entradas para un blog
- **static**: ficheros estáticos como imáges u otros recursos
- **docusaurus.config.js**: fichero de configuración de docusaurus
- **sidebar.js**: estructura de la barra lateral de navegación
- **package.json**: configuración de las dependencias e inserción de scripts
- **README.md**: información del proyecto


## Personalización CSS de docusaurus
En la siguiente ruta se puede modificar el estilo **CSS**.

```javascript
src/css/custom.css
docusaurus.config.js
node_modules/@docusaurus/theme-classic/src/theme/
```

## &#128421; Despliegue en producción
Para el despliegue hace falta empaquetar la aplicación con la construcción de un **build**.

### &#128423; Servidor github pages
En este caso se va a realizar como ejemplo el despligue de un proyecto realizado con **Docusaurus** en el servicio de **github pages**.

:::tip
Fichero de configuración del proyecto: **docusaurus.config.js**
:::

### &#9881; Configuración para la generación de los ficheros estáticos del despliegue.
```javascript
module.exports = {
  // Añadir la URL del repositorio de github
  url: 'https://bbvcore.github.io',
  // Indicar
  baseUrl: '/me/docs/', 

  // ...
  organizationName: 'bbvcore', // User github
  projectName: 'me', // repositorio

  trailingSlash: false, // Elimina el slash final de la ruta
};
```
#### Creación de los ficheros del despliegue
```javascript
npm run build
```