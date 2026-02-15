---
title: Conexión WiFi
---
# Conexión WiFi
```C++
//**********************************
// Librerías
//**********************************
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

//**********************************
// Wifi
//**********************************
const char *ssid = "POCO";
const char *password = "12345678";
// Objetos WiFi y cliente Mqtt
WiFiClient clientMqttHistorian;
PubSubClient client(clientMqttHistorian); // Cliente MQTT con argumento conexión WiFi

//**********************************
// Configuración del Broker
//**********************************
const char *broker = "IP"; // IP del servidor Broker - Revisar siempre

//**********************************
// Función conexión WiFi
//**********************************
void initWifi(){
  delay(10);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Intentado establecer conexión wifi");
  }
  Serial.println("Establecida la conexión WiFi");
}

//**********************************
// Función de conexión para MQTT
//**********************************
void conectBroker(){
  while(!client.connected()){
   Serial.println("Conexión establecida con el Broker MQTT");
   // Identificador único del ESP en el broker
    String IdEsp32= "ESp32"+ WiFi.macAddress();
    if(client.connect(IdEsp32.c_str())){ // c_str es un puntero al primer elemento de const char*
      Serial.println("Works!, establecida conexión.");
      client.subscribe("topics/historian/data-grafana");
    } else {
     Serial.println("Error, código de retorno RC => ");
            /*
                RC = 0 => Conexión correcta
                RC = 1 => ERROR versión protocolo
                RC = 2 => ClientID NO válido - Suele ser el más habitual
                RC = 3 => Broker NO disponible
                RC = 4 => Error en las credenciales para el Broker 
                RC = 5 => No autorizada la conexión
             */
      Serial.println(client.state());
      Serial.println("Reintentando la conexión...");
      delay(1000);
    }
  }
}


//**********************************
// Librería 
//**********************************
void setup() {
  Serial.begin(115200);
  initWifi(); // Función para conexión a WiFi
 // client.setServer(broker, 1883);
}

void loop() {
 // if (!client.connected()){ // Comprueba la conexión al broker
    //conectBroker();
   // client.loop(); // Bucle del broker para mantener la conexión
 // }
}

```