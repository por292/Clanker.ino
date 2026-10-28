#include <Servo.h>
#include <QTRSensors.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;




#define S0 3
#define S1 4
#define S2 7
#define S3 6
#define sensorOut 8
#define OE 5


//white
int white[] = {20, 20, 20};
bool whiteFlag[] = {false, false, false};
int frequency = 0;
int difference = 0;
//black
int black [] = {129, 170, 170};
bool blackFlag[] = {false, false, false};
int frequencyB = 0;
int differenceB = 0;
//purple
int purp[] = {90, 110, 75};
bool purpFlag[] = {false, false, false};
int frequencyC = 0;
int differenceC = 0;
//yellow
int yellow[] = {33, 53, 61};
bool yellowFlag[] = {false, false, false};
int frequencyD = 0;
int differenceD = 0;

//ultrasonic 
const int echoPin = (12);
const int trigPin = (11);
int duration, distance;
unsigned long c_time;
unsigned long p_time;
unsigned long t_time;
//wheels
const int In1 = A4;
const int In2 = A5;
const int In3 = 2;
const int In4 = 13;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

QTRSensors qtrA;
QTRSensors qtrB;

void setup() {

  for (uint16_t i = 0; i < 400; i++){
    qtrB.calibrate();
    Serial.print("Calibrated: ");
    Serial.println(i);
  }
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

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);


  Serial.begin(9600);

}

void loop() { 
 //Claw();
 
 //Clench();
 //Wheels();
 Line();
StayOnTheLine();
sensorfunc();
 //White();
 //Black();
 //Yellow();
 //Purple();
}

/*void Claw(){

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
}*/

void StayOnTheLine(){
  uint16_t position = qtrA.readLineBlack(sensorValues);
  if (position > 1200 && position < 1400){
    digitalWrite(In1, HIGH);
    digitalWrite(In3, LOW);
    Serial.println("Moving Left 20ms");
    Serial.println(position);
    delay(20);
    digitalWrite(In1, LOW);
    digitalWrite(In3, LOW);
  }

  if (position < 1200){
    digitalWrite(In1, LOW);
    digitalWrite(In3, HIGH);
    Serial.println("Moving Right 20ms");
    Serial.println(position);
    delay(20);
    digitalWrite(In1, LOW);
    digitalWrite(In3, LOW);
  }
  if (position > 1400){
    digitalWrite(In1, LOW);
    digitalWrite(In3, LOW);
    Serial.println(position);
    Serial.println("On The Line");
  }

}
void sensorfunc() {

  // this code can be updated to use the built in location function in qtr
  uint16_t position = qtrA.readLineBlack(sensorValues);
  Serial.print("Position: ");
  Serial.println(position);
  delay(500);
  
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

  delay(100);

}
/*void Clench(){

  if (distance <= 7){
    delay(250);
    myservo.write(90);
    myservo1.write(90);
    
  }
  else 
  {
   delay(250);
   myservo.write(180);
   myservo1.write(0);
   
  }
}*/
void White()
{
   // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - white[0];
  if(abs(difference)<15){
    whiteFlag[0] = true;
  }
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - white[1];
  if(abs(difference)<15){
    whiteFlag[1] = true;
  } 
  delay(50);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - white[2];
  if(abs(difference)<15){
    whiteFlag[2] = true;
  }
  if (whiteFlag[0] && whiteFlag[1] && whiteFlag[2]){
    Serial.println("It is white");
  }else{
    //Serial.println("UNKNOWN");
  }
  whiteFlag[0] = false; whiteFlag[1] = false; whiteFlag[2] = false;
  delay(100);
   
   // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  // Printing the value on the serial monitor
  //Serial.print("R= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  //Serial.print("  ");

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  // Printing the value on the serial monitor
  //Serial.print("G= ");//printing name
  //Serial.print(frequency);//printing Green color frequency
  //Serial.print("  ");

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  // Printing the value on the serial monitor
  //Serial.print("B= ");//printing name
  //Serial.print(frequency);//printing Blue color frequency
  //Serial.println("  ");
  
}


void Black(){

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  frequencyB = pulseIn(sensorOut, LOW);
  difference = frequencyB - black[0];
  if(abs(difference)<15){
    blackFlag[0] = true;
  }
  delay(50);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequencyB = pulseIn(sensorOut, LOW);
  difference = frequencyB - black[1];
  if(abs(difference)<15){
    blackFlag[1] = true;
  } 
  delay(50);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequencyB = pulseIn(sensorOut, LOW);
  difference = frequencyB - black[2];
  if(abs(difference)<15){
    blackFlag[2] = true;
  }
  if (blackFlag[0] && blackFlag[1] && blackFlag[2]){
    Serial.println("It is black");
  }else{
    //Serial.println("UNKNOWN");
  }
  blackFlag[0] = false; blackFlag[1] = false; blackFlag[2] = false;
  delay(100);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  frequencyB = pulseIn(sensorOut, LOW);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequencyB = pulseIn(sensorOut, LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequencyB = pulseIn(sensorOut, LOW);
}

void Purple(){

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  frequencyC = pulseIn(sensorOut, LOW);
  difference = frequencyC - purp[0];
  if(abs(difference)<15){
    purpFlag[0] = true;
  }
  delay(50);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequencyC = pulseIn(sensorOut, LOW);
  difference = frequencyC - purp[1];
  if(abs(difference)<15){
    purpFlag[1] = true;
  } 
  delay(50);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequencyC = pulseIn(sensorOut, LOW);
  difference = frequencyC - purp[2];
  if(abs(difference)<15){
    purpFlag[2] = true;
  }
  if (purpFlag[0] && purpFlag[1] && purpFlag[2]){
    Serial.println("It is Purple");
  }else{
    //Serial.println("UNKNOWN");
  }
  purpFlag[0] = false; purpFlag[1] = false; purpFlag[2] = false;
  delay(100);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  frequencyC = pulseIn(sensorOut, LOW);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequencyC = pulseIn(sensorOut, LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequencyC = pulseIn(sensorOut, LOW);
}

void Yellow(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  frequencyD = pulseIn(sensorOut, LOW);
  difference = frequencyD - yellow[0];
  if(abs(difference)<15){
    yellowFlag[0] = true;
  }
  delay(50);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequencyD = pulseIn(sensorOut, LOW);
  difference = frequencyD - yellow[1];
  if(abs(difference)<15){
    yellowFlag[1] = true;
  } 
  delay(50);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequencyD = pulseIn(sensorOut, LOW);
  difference = frequencyD - yellow[2];
  if(abs(difference)<15){
    yellowFlag[2] = true;
  }
  if (yellowFlag[0] && yellowFlag[1] && yellowFlag[2]){
    Serial.println("It is Yellow");
  }else{
    //Serial.println("UNKNOWN");
  }
  yellowFlag[0] = false; yellowFlag[1] = false; yellowFlag[2] = false;
  delay(100);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  frequencyD = pulseIn(sensorOut, LOW);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  frequencyD = pulseIn(sensorOut, LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  frequencyD = pulseIn(sensorOut, LOW);
}

void Wheels()
{
  if (whiteFlag || blackFlag == true){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  }
  else if (yellowFlag == true){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  }
  if(whiteFlag || blackFlag == true){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  }
  else if (purpFlag == true){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  }
}
