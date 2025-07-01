---
title: ESP32 + HAL adaptado a Node-red
---

# &#128736;  ESP32 + HAL adaptado a Node-red

<details>
<summary>
Código fuente para implementar en el ESP32
</summary>

```c++
//*******************************************
//      MODIFICADO PARA NODE-RED
//*******************************************
// LIBRERIAS
//*******************************************
/*#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <PubSubClient.h> // Esta libreria hay que añadirla desde Librerias de PIO
#include <esp32-hal.h> // Para leer la temperatura

//*******************************************
// CONFIGURACIÓN DE RED Y BROKER
//*******************************************
const char *ssid = "MiFibra-65F2";
const char *password = "";
// Red teléfono móvil
//const char *ssid = "****"
//const char *password = "*****"
const char *mqtt_server = "192.168.1.55"; // IP DEL HOST LOCAL DONDE SE EJECUTA EL BROKER (NO USAR NUNCA LOCALHOST, PORQUE EL ESP32 LA INTERPRETA COMO LA PROPIA DEL ESP32)

//*******************************************
//  OBJETOS: WIFI Y CLIENT
//*******************************************
WiFiClient espClient;
PubSubClient client(espClient);

//*******************************************
// FUNCIÓN CONEXIÓN WIFI
//*******************************************
void init_wifi(){
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Intentando establecer la conexión WiFi...");
    }
    Serial.println("Establecida la conexión WiFi");
}

//*******************************************
// FUNCIÓN CONEXIÓN MQTT
//*******************************************
void conect_broker(){
    while (!client.connected()){
        Serial.print("Conectando al BROKER MQTT...");
        if (client.connect("ESP32Client")){
            Serial.println("WORKS! Establecida conexión con el BROKER");
            client.subscribe("temperature"); // Subcribirse al TOPIC
        }
        else{
            Serial.print("ERROR!, rc= ");
            Serial.print(client.state());
            Serial.println("Reintentanto establecer la conexión tras 1 segundo...");
            delay(1000);
        }
    }
}

//*******************************************
// FUNCIÓN LEER TEMPERATURA
//*******************************************
void setTemperature(){
    float temp = temperatureRead();
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println("º C");
    client.publish("temperature", String(temp).c_str()); // Como un String
}

//***********************************************************************************************
//*******************************************
//       FUNCIÓN SETUP EN ARDUINO
//*******************************************
void setup(){
        Serial.begin(115200);
        init_wifi(); // Llamada a función 
        client.setServer(mqtt_server, 1883); 
}

//*******************************************
//       FUNCIÓN LOOP EN ARDUINO
//*******************************************
void loop(){
        if (!client.connected()){ // Si NO se estableció la conexión
            conect_broker(); // Conexión al BROKER, llamada a función
        }
        client.loop(); // Conexión en BUCLE
        setTemperature();
        delay(30000);
    }*/
```

</details>