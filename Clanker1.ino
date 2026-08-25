#include <Servo.h>
#include <QTRSensors.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
QTRSensors qtrA;

const int echoPin = (12);
const int trigPin = (11);
int duration, distance;
unsigned long c_time;// = millis();
unsigned long p_time;
unsigned long t_time;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

void setup() {

  
  myservo.attach(9);
  myservo1.attach(10);
  qtrA.setTypeRC();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  qtrA.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount);

  Serial.begin(9600);

}

void loop() { 
 Claw();
 Line();
 Clench();
}

void Claw(){

  if(millis() - p_time > 250){
  p_time = millis();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  //Serial.println(distance);
  }
}

void Line(){

if (millis() - t_time > 250){
  t_time = millis();
  qtrA.read(sensorValues);
}
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    //Serial.print(sensorValues[i]);
    //Serial.print('\t');
  }
 // Serial.println();

  delay(250);

}
void Clench(){

  if (distance >= 7){
    //if(millis() - c_time > 250){
    //c_time = millis();
    myservo.write(90);
    myservo1.write(90);
   // }
  }
  else //if (distance <=7)
  {
  
   //if(millis() - c_time > 250){
  //c_time = millis();
   myservo.write(180);
   myservo1.write(0);
   // }
  }
}
