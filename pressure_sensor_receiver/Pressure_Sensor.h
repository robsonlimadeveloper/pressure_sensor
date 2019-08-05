/*
  Sensor_Pressure.h - Library for use with Arduino Nano and HC-05 bluetooth module
*/
 
#ifndef Pressure_Sensor_h
#define Pressure_Sensor_h
 
#include "Arduino.h"
#include "SoftwareSerial.h"
 
class Pressure_Sensor
{
    public:
        Pressure_Sensor(Stream *device);
        float getPressure();
        float getTemperature();
        float getAltitude();
          
    private:
        Stream *mySerial;
        float pressureValue;
        float temperatureValue;
        float altitudeValue;
        String message;
        void getMessage();   
};
#endif
