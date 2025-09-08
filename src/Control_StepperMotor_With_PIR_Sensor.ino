/*
  Connect Stepper and PIR sensor in to board do when we come close
  the garbage bin will be open.

  Stepper : 
    - 8 -> IN1, 9 -> IN2, 10 -? IN3, 11 -> IN4
    - GND, 5V
    - Stepper : red -> C 
  Sensor:
    - GND, 5V, pin 3

*/


#include <Stepper.h>


// Pin definitions
const int STEPPER_PIN1 = 8;
const int STEPPER_PIN2 = 9;
const int STEPPER_PIN3 = 10;
const int STEPPER_PIN4 = 11;
const int PIR_PIN = 3; // Sensor

const int STEPS_PER_REVOLUTION   = 2048;

Stepper myStepper(STEPS_PER_REVOLUTION ,STEPPER_PIN1, STEPPER_PIN3, STEPPER_PIN2, STEPPER_PIN4);

// State variables
enum BinState {
  CLOSED,
  OPENING,
  OPEN,
  CLOSING
};

BinState currentState = CLOSED;


const int STEPPER_SPEED = 10;
const int ROTATION_COUNT = 4;
const int STEP_DELAY = 200;             // Delay between rotations (ms)


const int MOTION_THRESHOLD = 5;
int motionCounter = 0; // because the PIR sensor is INSANELY sensitive so add counter  
bool motionDetected = false; 
void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  myStepper.setSpeed(STEPPER_SPEED); // RPM
  Serial.println("Smart Garbage Bin Controller Started");
}

void loop() {
   readMotionSensor();
   updateBinState();
   delay(1000);
}

void readMotionSensor() {
  int pirState = digitalRead(PIR_PIN);
  
  if(pirState == HIGH){
    Serial.println("Motion detected");
    motionCounter++;
    
    if (motionCounter >= MOTION_THRESHOLD) {
      motionDetected = true;
      motionCounter = 0; // Reset counter
      Serial.println("Motion threshold reached!");
    }
  }

}

void updateBinState(){
  switch (currentState) {
    case CLOSED: // then we will open bin
      if(motionDetected){
        Serial.println("Opening!");
        changeState(OPENING);
        openBin();
        
        motionDetected = false;
      }
      break;
    case OPENING: // do nothing 
      break; 
    
    case OPEN: // then we will open bin
      if(motionDetected){
        Serial.println("Closing!");
        changeState(CLOSING);
        closeBin();
        
        motionDetected = false;
      }
      break; 
    
     case CLOSING: // do nothing 
      break; 
    
  }

}

void changeState(BinState newState){
  currentState = newState;
  Serial.println("State change");
}

void openBin(){
  for (int rotation = 0; rotation < ROTATION_COUNT; rotation++) {
      myStepper.step(STEPS_PER_REVOLUTION); 
      rotation++;
      delay(STEP_DELAY);
  }
  changeState(OPEN);
}

void closeBin(){
  for (int rotation = 0; rotation < ROTATION_COUNT; rotation++) {
      myStepper.step(-STEPS_PER_REVOLUTION); 
      rotation++;
      delay(STEP_DELAY);
  }
  changeState(CLOSED);
}














