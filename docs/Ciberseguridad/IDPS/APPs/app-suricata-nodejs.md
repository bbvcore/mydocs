---
title: App para Suricata
---
# App para Suricata
Aplicación desarrollada mediante **NodeJS** para poder consultar rápidamente valores y datos interesantes proporcionados por **Suricata**.

## Code
<details>
<summary>
Código de la aplicación web realizada con NodeJS
</summary>

```javascript
//-------------------------------------------------------------------------
// 			MÓDULOS
//-------------------------------------------------------------------------
const fs = require('fs')
const path = require('path')
const express = require('express')

//-------------------------------------------------------------------------
// 			CONSTANTES
//-------------------------------------------------------------------------
const EVE = '/var/log/suricata/eve.json'
// console.log(EVE)
const PORT = process.env.PORT || 3000;

//-------------------------------------------------------------------------
// 			APP
//-------------------------------------------------------------------------
const app = express();

// Parseo de datos en solicitudes y formularios
app.use(express.json())
app.use(express.urlencoded({extended: true}))

//-------------------------------------------------------------------------
// 			FUNCIONES
//-------------------------------------------------------------------------
const readEve = (limit = 100) => {
try{
    const data = fs.readFileSync(EVE, 'utf8'); // Lee el fichero eve.json
    const lines = data // A continuación se encadenan una serie de métodos, lineas almacenará cada línea extraida de data
      .split('\n') /* Divide el fichero con cada salto de linea, ya que en eve.json se almacenan como: {dupla}\n, en este caso el separador que se usa como argumento es el salto de línea  */
      .filter(Boolean) /* Elimina lineas vacias */
      .slice(-limit) /* Solo usa las últimas líneas, slice usa dos argumentos inicio y final, pero si solo se pone uno va desde ese inicio al final, y si se pone negativo, empieza en el final y va hasta ese valor */
      .map(line => { /* Mapeo, line sirve de currentValue para la iteración y transformación con el método map  */
        try {
          return JSON.parse(line); // Parsea cada línea a un objeto JSON
        } catch {
          return null;
        }
      })
      .filter(Boolean); // Borr las líneas que no se pudieron parsear

    return lines; // El retorno de la función
  } catch (error) {
    console.error('Se ha producido un error leyendo el fichero eve.json:', error.message);
    return []; // Al haber un error se retorna vacio
  }
}

//-------------------------------------------------------------------------
// 			ENPOINTS
//-------------------------------------------------------------------------
//  Consultar los últimos 100 eventos
//-------------------------------------------------------------------------
app.get('/events', (req, res) => {
  const limit = parseInt(req.query.limit) || 100; // Línea innecesaria de momento, pero está para permitir peticiones GET con postman o el navegador web cuando se escale
  const events = readEve(limit); // Leer los datos
  res.json(events); // Mostrar los datos
});

//-------------------------------------------------------------------------
// Filtrar /events/filter?protocol=UDP
//-------------------------------------------------------------------------
app.get('/',()) => {

}

app.get('/events/filter', (req, res) => {
  const limit = parseInt(req.query.limit) || 100;
  const protocol = req.query.protocol;

  if (!protocol) {
    return res.status(400).json(
    	{ 
    		error: 'Ha de proporcionar un protocolo en el parámetro "protocol".' 
    	});
  }

// Obtención de todos los eventos		
  const events = readEve(limit); // LLamada a la función de lectura de eve.json

// Depuración
console.log("Protocolo buscado: ", protocol)
const protocolos = events.map(e => e.proto).filter(Boolean)
console.log("Protocolos encontrados: ", [...new Set(protocolos)])

// http://localhost:3000/events/filter?protocol=tcp&limit=1 ejemplo de uso con protocolo y modificación del valor limit
// Filtraje por protocolo
  const filtered = events.filter(event => event.proto && event.proto.toLowerCase() === protocol.toLowerCase());
  res.json(filtered); // Retorno de los eventos filtrados
});


// Inicio del servidor
app.listen(PORT, () => {
  console.log(`La API de consulta de Suricata está disponible desde http://localhost:${PORT}`);
});

```


</details>

## Casos de uso
```bash
http://localhost:3000/events/
http://localhost:3000/events?limit=<value Integer>
```

```bash
http://localhost:3000/events/filter?protocol=udp
http://localhost:3000/events/filter?protocol=tcp&limit=1
```

