/*
  Connect servo and sensor in to board do when we come close
  the garbage bin will be open.

  Servo:
    - GND, 5V, pin 9
  Sensor:
    - GND, 5V, pin 3

*/

#include <Servo.h>

//Servo
Servo myServo;

int servoPin = 9;
int servoDelay=1000;
int servoMax=180; // servo could only move max 180
int servoMin=0;

// Sensor
int pirPin = 3;

bool isOpen = false;
int maxCounter = 5;
int counter = 0; // because the PIR sensor is INSANELY sensitive so add counter  
void setup() {
  Serial.begin(9600);
  
  myServo.attach(servoPin);
  pinMode(pirPin,INPUT);
  
}

void loop() {
  int pirState = digitalRead(pirPin);
  if(pirState == HIGH){
    Serial.println("Motion detected");
    counter++;
  }
  if (counter == maxCounter){
    isOpen = !isOpen;
    counter = 0;
    delay(servoDelay);
  }

  if(isOpen){
    myServo.write(servoMax);
  }else{
    myServo.write(servoMin);
  }
  delay(servoDelay);

}
