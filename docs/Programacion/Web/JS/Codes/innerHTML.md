---
title: InnerHTML
---

# InnerHTML
<details>
<summary>
Ejemplo de <b>InnerHTML</b> en <b>JS</b>
</summary>

```javascript
<!DOCTYPE html>
<html lang="es">
    <meta charset="utf-8">
    <meta name="viewport" content="device=width-device;initial-scale=1">
<body>
<input type="text" name="captureText" id="captureText" placeholder="Introducir texto">
<input type="text" name="seeText" id="seeText" placeholder="Ver texto">
<button id="change">Change</button>
<div id="result"></div>
<div id="live"></div>
<script type="text/javascript">
    const capture = document.getElementById('captureText')
    const see = document.getElementById('seeText')
    const result = document.getElementById('result')
    const live = document.getElementById('live')
    const change = document.getElementById('change')
    
    change.addEventListener('click',()=>{
        see.value = capture.value // Copia 
        // Input NUNCA innerHTML
        result.innerHTML = capture.value;
    })

    capture.addEventListener('input',()=>{
            live.innerHTML = capture.value    
    })

</script>
</body>
</html>
```

</details>
