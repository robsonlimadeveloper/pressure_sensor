/*
  Sensor_Pressure.cpp - For use with Arduino Nano and HC-05 bluetooth module
*/

#include "Pressure_Sensor.h"
#include "SoftwareSerial.h"
 
Pressure_Sensor::Pressure_Sensor(Stream *device)
{
    mySerial = device;
    pressureValue = 0;
    temperatureValue = 0;
    altitudeValue = 0;
    message = "";
}
//Split string and remove separate values
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
//get serial message
void Pressure_Sensor::getMessage()
{   
    if (mySerial->available()>0) {
        message = mySerial->readString();
        pressureValue = getValue(message,'-',0).toFloat();
        temperatureValue = getValue(message,'-',1).toFloat();
        altitudeValue = getValue(message,'-',2).toFloat();
    }else{
      mySerial->println("1");
    }    
}
float Pressure_Sensor::getPressure(){
  getMessage();
  return pressureValue;
}
float Pressure_Sensor::getTemperature(){
  getMessage();
  return temperatureValue;
}
float Pressure_Sensor::getAltitude(){
  getMessage();
  return altitudeValue;
}
