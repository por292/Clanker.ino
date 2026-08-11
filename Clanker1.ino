#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
Servo myservo2;


void setup() {

  myservo.attach(4);
  myservo1.attach(5);
  myservo2.attach(6);
  Serial.begin(9600);

}



void loop() {
 Claw();

}

void Claw(){

  myservo.write(0); 
  myservo1.write(0);
  myservo2.write(0);
  Serial.println(myservo.read());
  Serial.println(myservo1.read());
  Serial.println(myservo2.read());
  //delay(500);
  myservo.write(110);
  myservo1.write(110);
  myservo2.write(110);
  Serial.println(myservo.read());
  Serial.println(myservo1.read());
  Serial.println(myservo2.read());
  //delay(500);

}
