---
title: Scrolling
---
# Scrolling

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Scrolling</title>
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
        #layer{
            width:100px;
            height:100px;
            overflow:auto;
            border:2px solid black;
        }
    </style>
</head>
<body>
    <div id="layer">
        Lorem ipsum dolor sit amet consectetur adipisicing elit. In veniam, nisi eligendi cupiditate, tempora tenetur illum, necessitatibus itaque animi eum officia repudiandae velit non sapiente placeat impedit repellat voluptates? Repudiandae!
        Lorem ipsum, dolor sit amet consectetur adipisicing elit. Eligendi quidem nisi inventore ea magnam aliquam rerum modi consequuntur doloremque, sunt vero iste quibusdam, enim totam? Magnam velit sit obcaecati tempore.
    </div>
<script type="text/javascript">
    // Scroll para Window y HTMLElement
    console.log('ScrollX y ScrollY es el scroll producido en el objeto Window (ventana): X:' + window.scrollX + ', Y: ' + window.scrollY);
    const capa = document.getElementById("layer");
    console.log("ScrollLeft y ScrollTop producido en un HTML elemento, Lef: " + capa.scrollLeft + ", Top: " + capa.scrollTop);
    console.log('Scroll Height Total(visible + no visible): ' + document.documentElement.scrollHeight); 
    console.log('Scroll Width Total (visible + no visible): ' + document.documentElement.scrollWidth); 
    console.log("Scroll(x,y) permite desplazar a una determinadas coordenadas la ventana");
    console.log("ScrollTo(x,y) desplaza la ventana hacía una posición exacta");
    console.log("ScrollBy(x,y) desplaza la ventana desde donde esta X,Y pixeles");
    
    // Tamaño de Window y HTML Element
    console.log(window.innerWidth + " ,tamaño de la ventana visible viewport - solo Window");
    console.log(window.outerrHeight + " ,tamaño de la ventana total (con barras, etc...) - solo Window");
    console.log(capa.clientHeight + " ,tamaño del viewport desde - HTMLELement - sin barras de scroll + padding - border");
    console.log(capa.clientWidth + " ,tamaño del viewport desde - HTMLElement -  sin barras de scroll + padding - border");
    console.log(capa.offsetWidth + ", incluye tamaño + lo demás (padding + border)");
    // GetBoundingClientRect
    const box = document.getElementById("box");
    const get = box.getBoundingClientRect();

    // Propiedades del objeto capturado con getBoundingClientRect
    console.log(get.top);
    console.log(get.bottom);
    console.log(get.width);
    console.log(get.height);
    console.log(get.left);
    console.log(get.right);

</script>
</body>
</html>

```