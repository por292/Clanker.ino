#include <Servo.h>
#include <QTRSensors.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
QTRSensors qtrA;

#define S0 3
#define S1 4
#define S2 7
#define S3 6
#define sensorOut 8
#define OE 5


int green[] = {47, 40, 55};
//int blue [] = {0, 0, 255}
bool greenFlag[] = {false, false, false};
//bool blueFlag[] = {false, false, false}
int frequency = 0;
int difference = 0;


const int echoPin = (12);
const int trigPin = (11);
int duration, distance;
unsigned long c_time;
unsigned long p_time;
unsigned long t_time;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

void setup() {

 

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(OE, LOW);

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
 colour();
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
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
  }
}

void Line(){

if (millis() - t_time > 250){
  t_time = millis();
  qtrA.read(sensorValues);
}
  //print the sensor values as numbers from 0 to 1023, where 0 means maximum
  //reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    //Serial.print(sensorValues[i]);
    //Serial.print('\t');
  }
  //Serial.println();

  delay(250);

}
void Clench(){

  if (distance <= 7){
    delay(250);
    myservo.write(90);
    myservo1.write(90);
    delay(250);
  }
  else 
  {
   delay(250);
   myservo.write(180);
   myservo1.write(0);
   delay(250);
  }
}
void colour()
{
   // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - green[0];
  if(abs(difference)<10){
    greenFlag[0] = true;
  }
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - green[1];
  if(abs(difference)<10){
    greenFlag[1] = true;
  } 
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - green[2];
  if(abs(difference)<10){
    greenFlag[2] = true;
  }
  if (greenFlag[0] && greenFlag[1] && greenFlag[2]){
    Serial.println("It is green");
  }else{
    Serial.println("UNKOWN");
  }
  greenFlag[0] = false; greenFlag[1] = false; greenFlag[2] = false;
  delay(1000);
   
   // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing Green color frequency
  Serial.print("  ");
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing Blue color frequency
  Serial.println("  ");
  delay(1000);
}

void Wheels()
{

}

}
}
