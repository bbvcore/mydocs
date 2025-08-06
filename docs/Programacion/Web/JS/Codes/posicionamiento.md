---
title: Posicionamiento
---
# Posicionamiento

<details>
<summary>
Código <b>JS</b> para calculo de posicionamiento de elementos en el documento.
</summary>

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        *{
            margin:0;
            padding:0;
            box-sizing: border-box;
        }
        body{
            font-size:100%;
            font:sans-serif;
        }
        #padre{
            width:14rem;
            height: 4rem;
            margin:0 auto;
            border:2px solid black;
        }
        #hijo{
            width:100%;
            height:2.5rem;
            margin:0 auto;
            border: 2px solid black;
            margin-top:10rem;
 
        }
    </style>
</head>
<body>

<div id="padre"></div>
<div id="hijo">
    <btn id="btn">Acción</btn>
</div>

<script type="text/javascript">
// Seleccionar los elementos
    const padre = document.getElementById('padre');
    const hijo = document.getElementById('hijo');

// Obtener las propiedades de sus dimensiones
    const posPadre = padre.getBoundingClientRect();
    const posHijo = hijo.getBoundingClientRect();
    console.log(posPadre)
    console.log(posHijo)

// Realizar los calculos para averigurar las distancias
    const distH = Math.abs(posPadre.left - posHijo.left);
    const distV = Math.abs(posPadre.top - posHijo.top);

    console.log(`Dist. Horizontal: ${distH}px`);
    console.log(`Dist. Vertical: ${distV}px`);

// Posicionamiento objetos
const btn = document.getElementById('btn')
btn.addEventListener('click', (e) => {
  console.log('screenX / screenY:', e.screenX, e.screenY);
  console.log('clientX / clientY:', e.clientX, e.clientY);
  console.log('pageX / pageY:', e.pageX, e.pageY);
  console.log('offsetX / offsetY:', e.offsetX, e.offsetY);
});
</script>
    
</body>
</html>
```

</details>