#include <PinChangeInt.h>
#include <LowPower.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SERIAL_RX_PIN 0
#define SERIAL_TX_PIN 1
#define SERIAL_BAUDRATE 115200
#define SERIAL_SLEEP_TIMEOUT 10000

Adafruit_BMP280 bmp; // I2C
long last_time = 0;
long timeNow = 0;
String command = "";

void  WakeHandler ()
{
 // Nothing to do; just wakes the device. 
}

//Show errors on serial
void error(String msg){
  while(true){
    Serial.println(msg);
  }
}

//Iniciate BMP280 Sensor Module
void initSensor(){
  if (!bmp.begin()) {  
    error("Could not find a valid BMP280 sensor, check wiring!");
  }
}

//Configure
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(SERIAL_RX_PIN, INPUT_PULLUP);
  initSensor();
}

//Return pressure on bar format
float getPressureBar(){
  float pressureMilliBar = (float)bmp.readPressure()/100;

  return pressureMilliBar/1000;
}

//Return temperature on celsius format
long getTemperature(){
  long temperature = bmp.readTemperature();
  return temperature;
}

//Return altitude on M format
long getAltitude(){
  long altitude = bmp.readAltitude(1013.25);
  return altitude;
}

//Low power, on non serial activities
void sleep(){
  //Serial.println("Sleeping");
  Serial.flush();
  pinMode(SERIAL_RX_PIN, INPUT_PULLUP);
  PCintPort::attachInterrupt(SERIAL_RX_PIN, &WakeHandler, LOW);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  PCintPort::detachInterrupt(SERIAL_RX_PIN);
  Serial.begin(SERIAL_BAUDRATE);
  
  last_time = millis(); //Activate limit time for read serial device port
   
}
void loop() {

   timeNow = millis();

  //limit 
  if((timeNow - last_time) < SERIAL_SLEEP_TIMEOUT){
     //Serial.println("in time");
     while(Serial.available()) {
        char character = Serial.read();
        
        //Serial.println(command);

        if (character == '\n')
        {
          //Serial.print(command);
          
          if(command.toInt() == 1){
            
            Serial.print(String(getPressureBar())+"-"+String(getTemperature())+"-"+String(getAltitude())); //Send pressure value to serial port (bluetooth)
          }
          
          last_time = timeNow;
          
          command = "";
        }else{
          command.concat(character);
        }
        
      }
      
  }else{
    sleep();
  }
  //delay(500);
}
