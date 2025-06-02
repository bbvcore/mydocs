#Docusaurus
## Descarga e instalación
### Requisitos previos
Es necesario contar con nodejs y npm
```
sudo apt update && sudo apt install nodejs npm -y
```
Comprobar las versiones instaladas
```
node -v
npm -v
```

## Descarga de docusaurus
Crear una instalación de docusaurus en su última versión, en el directorio docusaurus-bbv y con el template classic
```
npx create-docusaurus@latest docusarusus-bbv classic
```
Una vez creado e instalado se ha de navegar al directorio del docusaurus y ejecutar el comando
```
npm install
```
Una vez instalados los módulos de las dependencias se procede a lanzar el propio docusarus con el comando
```
npm run start
```
Pd: En función de la configuración del fichero **package.json** se puede omitir el **run**.

## Compilación para producción
```
npm run build
```
Y mostrar el contenido desplegado con el comando
```
npm run serve
```

## Personalizar estética
En la siguiente ruta se puede modificar el estilo **CSS**
```
src/css/custom.css
docusaurus.config.js
node_modules/@docusaurus/theme-classic/src/theme/
```

Aplicar cambios de nuevo
```
npm start
``
