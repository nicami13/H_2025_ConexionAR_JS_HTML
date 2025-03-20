#include <Arduino.h>  
#include <WiFi.h>  
#include <AsyncTCP.h>  
#include <ESPAsyncWebServer.h>  
#include "SPIFFS.h"  

int LDR = 33;  
const char* ssid = "USTA_Estudiantes";  
const char* password = "#soytomasino";  

AsyncWebServer server(80);  

void setup() {  
    pinMode(LDR, INPUT);  
    Serial.begin(115200);  
    initWiFi();  
    initSPIFFS();  

    // Servir el archivo HTML principal  
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){  
      request->send(SPIFFS, "/index.html", "text/html");  
    });  

    // Ruta para obtener el valor de la luz  
    server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){  
      int valor = analogRead(LDR); // Leer el LDR  
      String jsonResponse = "{\"light\": " + String(valor) + "}"; // Crear respuesta JSON  
      request->send(200, "application/json", jsonResponse); // Enviar respuesta  
    });  

    server.begin();  
}   

void initWiFi() {  
    WiFi.mode(WIFI_STA);  
    WiFi.begin(ssid, password);  
    Serial.println("");  
    Serial.print("Connecting to WiFi...");  
    while (WiFi.status() != WL_CONNECTED) {  
        Serial.print(".");  
        delay(1000);  
    }  
    Serial.println("");  
    Serial.println(WiFi.localIP());  
}   

void initSPIFFS() {  
    if (!SPIFFS.begin()) {  
        Serial.println("An error has occurred while mounting SPIFFS");  
    }  
    Serial.println("SPIFFS mounted successfully");  
}  

void loop() {  
    // No se necesita hacer nada en el bucle principal  
}  
