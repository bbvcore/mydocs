---
title: Flujo Aedes - Hal
---

# &#128736; Flujo Node-Red Aedes
Flujo de node-red para poder trabajar con un ESP32 
y transmitir su temperatura a través de un broker Aedes.

<details>
<summary>
Obtener el <b>JSON</b> del flujo para usar en <b>Node-red</b>
</summary>

```json
[
    {
        "id": "d2d7d69d8ec676de",
        "type": "tab",
        "label": "Aedes + Esp32 temperatura",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "b49f517879342d2d",
        "type": "mongodb3",
        "uri": "mongodb://localhost:27017/ESP32",
        "name": "",
        "options": "",
        "parallelism": "-1"
    },
    {
        "id": "ebd5c64a.61c8d",
        "type": "mqtt-broker",
        "name": "Broker Aedes",
        "broker": "192.168.1.55",
        "port": "1883",
        "clientid": "node-red-client",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": 4,
        "keepalive": "60",
        "cleansession": true,
        "autoUnsubscribe": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willRetain": false,
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    },
    {
        "id": "871eb7bf686042da",
        "type": "mqtt-broker",
        "name": "brokerEsp32",
        "broker": "192.168.1.55",
        "port": "1883",
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": "4",
        "keepalive": "60",
        "cleansession": true,
        "autoUnsubscribe": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthRetain": "false",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closeQos": "0",
        "closeRetain": "false",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willRetain": "false",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    },
    {
        "id": "f2f358f62e8eee1f",
        "type": "mqtt in",
        "z": "d2d7d69d8ec676de",
        "name": "",
        "topic": "temperature",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "871eb7bf686042da",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 150,
        "y": 160,
        "wires": [
            [
                "3e1bae80ea115f99",
                "7eb173b27aab6a46"
            ]
        ]
    },
    {
        "id": "e2af2fbf2d2b60dd",
        "type": "aedes broker",
        "z": "d2d7d69d8ec676de",
        "name": "brokerEsp32",
        "mqtt_port": "1883",
        "mqtt_ws_bind": "port",
        "mqtt_ws_port": "",
        "mqtt_ws_path": "",
        "cert": "",
        "key": "",
        "certname": "",
        "keyname": "",
        "persistence_bind": "memory",
        "dburl": "",
        "usetls": false,
        "x": 150,
        "y": 240,
        "wires": [
            [],
            []
        ]
    },
    {
        "id": "3e1bae80ea115f99",
        "type": "debug",
        "z": "d2d7d69d8ec676de",
        "name": "debug 1",
        "active": true,
        "tosidebar": true,
        "console": true,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 410,
        "y": 160,
        "wires": []
    },
    {
        "id": "0ce86af7afc7e71e",
        "type": "comment",
        "z": "d2d7d69d8ec676de",
        "name": "ESP32 conectado al Broker enviando la temperatura del microprocesador",
        "info": "",
        "x": 320,
        "y": 80,
        "wires": []
    },
    {
        "id": "7eb173b27aab6a46",
        "type": "function",
        "z": "d2d7d69d8ec676de",
        "name": "obj JSON",
        "func": "\nlet value = msg.payload\nlet obj = {\n    temp : value\n}\nmsg.payload = obj\nreturn msg\n\n",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 360,
        "y": 260,
        "wires": [
            [
                "292e901892823db6"
            ]
        ]
    },
    {
        "id": "292e901892823db6",
        "type": "debug",
        "z": "d2d7d69d8ec676de",
        "name": "debug 2",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 560,
        "y": 260,
        "wires": []
    },
    {
        "id": "f1e34b39.3c9c5",
        "type": "http in",
        "z": "d2d7d69d8ec676de",
        "name": "temperature",
        "url": "temperature",
        "method": "post",
        "upload": false,
        "swaggerDoc": "",
        "x": 130,
        "y": 340,
        "wires": [
            [
                "f8a3f69a.9e8fa8"
            ]
        ]
    },
    {
        "id": "f8a3f69a.9e8fa8",
        "type": "json",
        "z": "d2d7d69d8ec676de",
        "name": "Parse JSON",
        "property": "payload",
        "action": "obj",
        "pretty": false,
        "x": 380,
        "y": 340,
        "wires": [
            [
                "ebf49a0b.3fe71",
                "d7a4f69a.6d7f7"
            ]
        ]
    },
    {
        "id": "ebf49a0b.3fe71",
        "type": "debug",
        "z": "d2d7d69d8ec676de",
        "name": "Ver objeto temperatura",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 640,
        "y": 340,
        "wires": []
    },
    {
        "id": "d7a4f69a.6d7f7",
        "type": "http response",
        "z": "d2d7d69d8ec676de",
        "name": "Send Response",
        "statusCode": "200",
        "headers": {},
        "x": 620,
        "y": 440,
        "wires": []
    }
]
```
</details>