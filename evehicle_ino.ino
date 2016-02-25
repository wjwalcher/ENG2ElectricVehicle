//The RUFF RIDERS Electric Vehicle Team

//Imports 
#include <Servo.h>

//Set port numbers for I/O 
int pedalPot = 0;
int victorPort = 3;
int btnReverse = 2;
int btnNeutral = 3;
int btnDrive = 4;
int ledReverse = 9;
int ledNeutral = 10;
int ledDrive = 11;

int minPotRange = 0;
int maxPotRange = 200;

//Start the vehicle in neutral (for safety reasons)
boolean drive = false;
boolean neutral = true;
boolean reverse = false;

Servo victor;

void setup(){
  victor.attach(victorPort);
}

void loop(){
  pedalVal = pedalPot.analogRead(pedalPot);
  pedalVal = map(pedalVal, 0, 1023, minPotRange, maxPotRange);
  if(btnDrive == HIGH){
    drive = true;
    neutral = false;
    reverse = false;
    if(drive && pedalVal >= 10){
      writeVal = pedalVal * 0.5; //Fix this. Currently, this will cause the car to run in reverse... yikes!
      victor.write(writeVal);
    }  
   if(btnNeutral == HIGH){
     neutral = true;
     drive = false;
     reverse = false;
     if(neutral){
      victor.write(90); 
    }
  }
}
