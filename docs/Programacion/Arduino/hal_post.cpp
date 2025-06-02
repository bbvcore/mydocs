//******************************************************
//      PARA SOLICITUD POST CON NODE-RED 
//******************************************************

// LIBRERÍAS
#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <HTTPClient.h>  // Librería para enviar solicitudes HTTP
#include <esp32-hal.h>   // Para leer la temperatura

//*******************************************
// CONFIGURACIÓN DE RED Y DEL ENDPOINT
//*******************************************
// Wifi
const char *ssid = "MiFibra-65F2";
const char *password = "";  
// Endpoint
const String url = "http://192.168.1.55:1880/temperature";  

//*******************************************
// FUNCIÓN CONEXIÓN WIFI
//*******************************************
void initWifi() {
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Intentando establecer la conexión WiFi...");
    }
    Serial.println("Conexión WiFi establecida");
}

//*******************************************
// FUNCIÓN TEMPERATURA Y POST
//*******************************************
void temperatureToServer() {
    // Leer la temperatura
    float temp = temperatureRead();  
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println("º C");

    // Cliente HTTP
    HTTPClient http;
    // Inicializar y pasar la URL
    http.begin(url);  
    // Cabeceras
    http.addHeader("Content-Type", "application/json");  

    // Payload estilo JSON
    String payload = "{\"temperature\": " + String(temp) + "}";

    // Enviar POST
    int httpResponseCode = http.POST(payload);  

    if (httpResponseCode > 0) {
        Serial.print("Código si se produce la respuesta HTTP: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("ERROR!, problemas con la solicitud HTTP: ");
        Serial.println(httpResponseCode);
    }

    // Finalizar la solicitud POST
    http.end();  
}

//***********************************************************************************************
//*******************************************
//       FUNCIÓN SETUP EN ARDUINO
//*******************************************
void setup() {
    Serial.begin(115200);  // Iniciar la comunicación serial
    initWifi;  // Conectar a la red WiFi
}

//*******************************************
//       FUNCIÓN LOOP EN ARDUINO
//*******************************************
void loop() {
    temperatureToServer();  // Enviar la temperatura al servidor en bucle
    delay(30000);  // Esperar 30 segundos antes de enviar la siguiente lectura
}
