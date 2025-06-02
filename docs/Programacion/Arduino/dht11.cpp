
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> // Librería para MQTT
#include <Adafruit_Sensor.h> // Librería para trabajar con ciertos sensores
#include <DHT.h> // Librería propia para sensores DHT (como el 11 o el 22)

//*******************************************
// CONFIGURACIÓN DE RED Y BROKER
//*******************************************
const char *ssid = ""; 
const char *password = "";
const char *mqtt_server = ""; // IP del Broker

//*******************************************
// CONFIGURACIÓN DEL SENSOR DHT
//*******************************************
#define PIN 15 // Pin de conexión de la patilla de datos del sensor
#define SENSOR_TYPE DHT11 // Tipo de Sensor

//*******************************************
// OBJETOS: WIFI, CLIENT y DHT
//*******************************************
WiFiClient espClientDHT;
PubSubClient client(espClientDHT);
DHT dht(PIN, SENSOR_TYPE);

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
    Serial.println("Establecida la conexión WiFi");
}

//*******************************************
// FUNCIÓN CONEXIÓN MQTT
//*******************************************
void conectBroker() {
    while (!client.connected()) {
        Serial.print("Conectando al BROKER MQTT...");
        if (client.connect("ESP32ClientDHT")) {
            Serial.println("WORKS! Establecida conexión con el BROKER");
            client.subscribe("sensores/dht11"); // Subscribirse al SUBTOPIC '/dht11'
        } else {
            Serial.print("ERROR!, Código de retorno => RC = ");
            /*
                RC = 0 => Conexión correcta
                RC = 1 => ERROR versión protocolo
                RC = 2 => ClientID NO válido - Suele ser el más habitual
                RC = 3 => Broker NO disponible
                RC = 4 => Error en las credenciales para el Broker 
                RC = 5 => No autorizada la conexión
             */
            Serial.print(client.state());
            Serial.println("Reintentando reconectar pasado 1 segundo...");
            delay(1000);
        }
    }
}

//********************************************
// FUNCIÓN PARA LEER LA TEMPERATURA Y HUMEDAD
//********************************************
void readAndPublishDHT() {
    // Variables para almacenar las lecturas de las mediciones
    float temp = dht.readTemperature(); // Leer la temperatura
    float hum = dht.readHumidity();    // Leer la humedad

    // Debuguear
    if (isnan(temp) || isnan(hum)) {
        Serial.println("ERROR!, problemas con la lectura de datos del sensor DHT11");
        return;
    }

    // Construcción del objeto para la publicación de los datos del sensor DHT
    String payload = "{\"temperature\": " + String(temp) + ", \"humidity\": " + String(hum) + "}"; // Casting a String
    Serial.println("Publicando mediciones : " + payload); // Mostrar por la consola aprovechando el puerto serie las mediciones

    // Publicar en el subtopic "sensores/dht11"
    client.publish("sensores/dht11", payload.c_str()); // Conversión a 'const char *', que es como los requiere la librería
}

//*******************************************
// FUNCIÓN SETUP EN ARDUINO
//*******************************************
void setup() {
    Serial.begin(115200);
    initWifi(); // Lanzar la función de conexión a WiFi
    client.setServer(mqtt_server, 1883); // Método para establecer la IP y el puerto del Broker
    dht.begin(); // Inicializar el sensor DHT11
}

//*******************************************
// FUNCIÓN LOOP EN ARDUINO
//*******************************************
void loop() {
    if (!client.connected()) { // Si NO se estableció la conexión
       conectBroker(); // Conexión al BROKER, llamada a función
    }
    client.loop(); // Conexión en BUCLE
     readAndPublishDHT(); // Función de lectura/publicación de los datos del sensor DHT11
    delay(30000); // Retardo hasta la siguiente lectura
}
