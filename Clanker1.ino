#include <Servo.h>
#include <QTRSensors.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
QTRSensors qtr;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

void setup() {

  myservo.attach(9);
  myservo1.attach(10);
  qtr.setTypeAnalog();

  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount);

  
  Serial.begin(9600);

}



void loop() {
 Claw();

}

void Claw(){

  myservo.write(180); 
  myservo1.write(0);
 
  Serial.println(myservo.read());
  Serial.println(myservo1.read());
  
  delay(500);
  
  myservo.write(95);
  myservo1.write(88);

  Serial.println(myservo.read());
  Serial.println(myservo1.read());
  
  
  delay(500);

}

void Line(){

 qtr.read(sensorValues);
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)

  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);

}
