---
title: Websocket Server 
---

# WebSocket Server 

```javascript
const WebSocket = require('ws');

// Crear un servidor WebSocket en el puerto 8080
const wss = new WebSocket.Server({ port: 8080 });

wss.on('connection', (ws) => {
    console.log('Cliente conectado');

    // Enviar un mensaje al cliente cuando se conecte
    ws.send('¡Bienvenido al servidor WebSocket!');

    // Recibir mensajes del cliente
    ws.on('message', (message) => {
        console.log('Mensaje recibido del cliente: ' + message);
        
        // Responder al cliente con un mensaje
        ws.send(`Servidor: Recibí tu mensaje - ${message}`);
    });

    // Manejar el cierre de la conexión
    ws.on('close', () => {
        console.log('Conexión cerrada');
    });
});

console.log('Servidor WebSocket escuchando en ws://localhost:8080');
```
