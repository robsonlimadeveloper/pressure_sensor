/*
  Example receive data from the "pressure_sensor_remote.ino" using: Arduino Nano, BMP280 and HC06 bluetooth module(Slave). 
*/

#include "Pressure_Sensor.h"

SoftwareSerial mySoftSerial(2, 3);
Pressure_Sensor sensor(&mySoftSerial);

void setup() {
  Serial.begin(115200);
  mySoftSerial.begin(115200);
}

void loop() {
  Serial.println("_____________________________________________________");
  Serial.println("Pressão: " + String(sensor.getPressure()));
  Serial.println("Temperatura: " + String(sensor.getTemperature())+"Cº");
  Serial.println("Altitude: " + String(sensor.getAltitude())+"m");
  delay(500);
}
