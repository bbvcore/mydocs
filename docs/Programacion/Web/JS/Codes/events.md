---
title: Events
---

# Events
<details>
<summary>
Código fuente de ejemplo de uso de eventos en **JS**
</summary>

```javascript
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>JS: Events</title>
</head>
<body>
    <script type="text/javascript">
        const btn = document.createElement('btn')
        btn.textContent = 'Ejecutando el método Alert'
        document.body.appendChild(btn)
        btn.addEventListener('click',(e)=>{
            alert('El botón ha sido pulsado')
            // Métodos del objeto event
            console.log(e.type)
            console.log(e.target)
            console.log(e.currentTarget)
            //preventDefault() // Evita comportamiento por defecto
            //stopPropagation() // Evita propagación a otros elementos
            console.log(e.key) // tecla presionada
            console.log(e.code) // código asociado a la tecla presionada
            // clientX y clientY: coordenadas del mouse en la ventana.
            // screenX y screenY: posición respecto al monitor (pantalla completa)
            // pageX y pageY: posición con respecto a la página (incluye el scroll), dentro del Document.
            // offsetX y offsetY: posición relativa al elemento que recibió el evento, es decir, donde se hace click

        })
        </script>

<input type="text" id="capturar" placeholder="Escribir aquí">
<script type="text/javascript">
    const character = document.getElementById("capturar")
    character.addEventListener('keydown', (e) => {
      console.log(`Key: ${e.key} (KeyCode: ${e.code})`);
      if (event.key === 'Enter') {
        alert('Tecla enter');
        event.preventDefault(); // Evitar acción por defecto
      }
    });   
</script>
</body>
</html>
```

</details>