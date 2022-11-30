

#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

// Credenciales wifi
/* 1. Define the WiFi credentials */
#define ssid "Galaxy A512922"
#define password "zsdt5796"

/* 2. Define the API Key */
#define API_KEY "AIzaSyCv_l8RY1lVafGqV2QnLEQ1_OGedmp9BX0"

//* 3. Credenciales Proyecto Firebase */
const char *FIREBASE_HOST="https://proyecto-iot-3af79-default-rtdb.firebaseio.com/"; 
const char *FIREBASE_AUTH="udszphwuGFxndgF59slGMqqHxOcApGCxgKm1FqcR";

// Firebase Data object in the global scope
FirebaseData firebaseData;

bool iterar = true;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
    Serial.print("hi");
  }
  Serial.print("\nConectado al Wi-Fi");
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  String nodo = "Proyecto-iot";

  while (iterar)
  {
    // set Float  value
  Firebase.setFloat(firebaseData,"number", 42.0);

    // escribir datos
   Firebase.setInt(firebaseData, "Sensor", 800);
   Firebase.setInt(firebaseData, "Temperatura", 11);
   Firebase.setString(firebaseData, "Led", "off");
   Serial.println("Los datos se escribieron con éxito");

    Firebase.setString(firebaseData, nodo + "/sensor", "DHT11");
    Firebase.setInt(firebaseData, nodo + "/temperatura", 45);
    Firebase.setBool(firebaseData, nodo + "/alarmas", true);

    // leer datos
     Firebase.getString(firebaseData, nodo + "/sensor");
     Serial.print("El sensor es: ");Serial.println(firebaseData.stringData());
     Firebase.getInt(firebaseData, nodo + "/temperatura");
     Serial.print("La última temperatura fue: ");Serial.println(firebaseData.intData());
     delay(250);
     
     

    // push de datos
    Firebase.setString(firebaseData, "Led1", "Hola Mundo!");
    
    Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/temperatura", 31);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/temperatura", 30);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/Humedad", 67);

    iterar = false;
    Firebase.end(firebaseData);
  }
} // End Loop