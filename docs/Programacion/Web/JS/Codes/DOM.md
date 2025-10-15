---
title: DOM
---
# DOM
<details>
<summary>
Ejemplo de manipulación del DOM en JS, donde se crea de forma dinámica un contenedor, un titulo y un texto, se monta todo y se añade al flujo del DOM en la sección del body.
</summary>

```html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="author" content="Borja Bas Ventín">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>DOM</title>
</head>
<body>
    <script>
        const seccion = document.createElement('div')
        seccion.className = "seccion"

        const titulo = document.createElement('h3')
        titulo.textContent = "Titulo de la sección"

        const parrafo = document.createElement('p')
        const text = document.createTextNode("Este es el contenido de un parrafo")
        parrafo.appendChild(text)

        seccion.appendChild(titulo)
        seccion.appendChild(parrafo)

        document.body.appendChild(seccion)
        // Otros métodos interesantes: removeChild(old method), remove(new method), setAttribute, getAttribute
    </script>
</body>
</html>

```

</details>