---
sidebar_position: 1
title: Docusaurus
---

# Docusaurus


## Instalación
## Estructura y ficheros de interés


## Despliegue en producción
Para el despliegue hace falta empaquetar la aplicación con la construcción de un **build**.

### Servidor github pages
En este caso se va a realizar el despligue en github pages.

:::tip
Edición del fichero de configuración: docusaurus.config.js
:::

```
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

```
npm run build
```