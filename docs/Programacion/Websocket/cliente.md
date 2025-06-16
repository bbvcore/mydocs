---
title: Websocket Cliente
---

# Websocket

```bash
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ejemplo WebSocket</title>
</head>
<body>
    <h2>Conexión WebSocket</h2>
    <div id="messages"></div>
    <input type="text" id="messageInput" placeholder="Escribe un mensaje...">
    <button id="sendButton">Enviar</button>

    <script>
        // Crear una nueva conexión WebSocket
        const socket = new WebSocket('ws://localhost:8080');

        // Abierto: cuando se establece la conexión
        socket.onopen = function(event) {
            console.log('Conexión establecida');
            document.getElementById('messages').innerHTML += '<p>Conexión establecida con el servidor.</p>';
        };

        // Mensaje recibido del servidor
        socket.onmessage = function(event) {
            console.log('Mensaje del servidor: ' + event.data);
            document.getElementById('messages').innerHTML += `<p>Servidor: ${event.data}</p>`;
        };

        // Error en la conexión
        socket.onerror = function(error) {
            console.log('Error de WebSocket:', error);
        };

        // Cerrar la conexión
        socket.onclose = function(event) {
            console.log('Conexión cerrada');
            document.getElementById('messages').innerHTML += '<p>Conexión cerrada.</p>';
        };

        // Enviar mensaje al servidor cuando el botón es presionado
        document.getElementById('sendButton').onclick = function() {
            const message = document.getElementById('messageInput').value;
            if (message) {
                socket.send(message);
                document.getElementById('messages').innerHTML += `<p>Tú: ${message}</p>`;
                document.getElementById('messageInput').value = ''; // Limpiar campo de texto
            }
        };
    </script>
</body>
</html>
```
