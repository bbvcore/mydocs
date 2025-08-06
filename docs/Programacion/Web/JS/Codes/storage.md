---
title: Storage
---
# Storage

<details>
<summary>
Código JS de uso del objeto Storage
</summary>

```html
<!DOCTYPE html>
<html lang="es">
    <meta charset="utf-8">
    <meta name="viewport" content="device=width-device;initial-scale=1">
    <style type="text/css">
    </style>
<body>
<h2>Objeto Storage</h2>
<input type="text" id="data-key" placeholder="Introduce una clave">
<input type="text" id="data-value" placeholder="Introduce un valor">
<button onclick="save()"> Guardar </button>
<button onclick="see()"> Mostrar </button>
<button onclick="del()"> Borrar </button>

<div id="rs"></div>

<script type="text/javascript">
// Almacenar el dato
    const save = ()=>{
        const key = document.getElementById('data-key').value
        const value = document.getElementById('data-value').value
        localStorage.setItem(key, value)
        alert("Valor guardado")
    }

// Mostrar el dato
    const see = () => {
     const list = document.getElementById('rs')
     list.innerHTML = "" // Limpiar list

    for (let i = 0; i < localStorage.length; i ++){
        let key = localStorage.key(i)
        let value = localStorage.getItem(key)
        
        let item = document.createElement('li');
        item.textContent = `Key: ${key} | Value: ${value}`;
        list.appendChild(item);
        }
    }

// Eliminar todos los datos
    const del = () => {
        //localStorage.removeItem(key)
        localStorage.clear()
        document.getElementById('rs').textContent = 'Se ha borrado el listado' 
    }

// Iterar el objeto Storage
for (let i = 0; i < localStorage.length; i ++){
    let key = localStorage.key(i)
    let value = localStorage.getItem(key)
    console.log('Key: ' + key + 'Value: ' + Value)
}
</script>
</body>
</html>
```

</details>