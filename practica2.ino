

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

//sensor
const int trigPin = 14;
const int echoPin = 12;
const int  LEDR = 4;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;


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
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LEDR, OUTPUT);
  digitalWrite(LEDR, LOW);
}

void loop()
{ // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  String nodo = "Proyecto-iot-3";

  int prendido = 0;
  bool presencia;

  if (distanceCm < 20){
     digitalWrite (LEDR , HIGH);
     presencia = false; 
  } else {
    digitalWrite (LEDR, LOW);
    presencia = true;
    prendido = prendido + 1;
  }

  int entradas = 0;

  while (iterar && entradas < 5);

  {
    // set Float  value
  Firebase.setFloat(firebaseData, nodo +"Distancia",distanceCm);
  Firebase.setInt(firebaseData, nodo + "Tiempo",prendido);
  Firebase.setBool(firebaseData, nodo + "Led", presencia);
  Serial.println("Los datos se escribieron con éxito");

    
    Firebase.pushInt(firebaseData, nodo + "/distancia", distanceCm);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/distancia", distanceCm);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/distancia", distanceCm);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/distancia", distanceCm);

    entradas += 1;
  }

  iterar = false;
 Firebase.end(firebaseData);
} // End Loop