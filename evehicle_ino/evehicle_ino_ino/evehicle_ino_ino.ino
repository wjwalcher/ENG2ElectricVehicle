//The RUFF RIDERS Electric Vehicle Team
/*                           ;\ 
                            |' \ 
         _                  ; : ; 
        / `-.              /: : | 
       |  ,-.`-.          ,': : | 
       \  :  `. `.       ,'-. : | 
        \ ;    ;  `-.__,'    `-.| 
         \ ;   ;  :::  ,::'`:.  `. 
          \ `-. :  `    :.    `.  \ 
           \   \    ,   ;   ,:    (\ 
            \   :., :.    ,'o)): ` `-. 
           ,/,' ;' ,::"'`.`---'   `.  `-._ 
         ,/  :  ; '"      `;'          ,--`. 
        ;/   :; ;             ,:'     (   ,:)     
          ,.,:.    ; ,:.,  ,-._ `.     \""'/ 
          '::'     `:'`  ,'(  \`._____.-'"' 
             ;,   ;  `.  `. `._`-.  \\ 
             ;:.  ;:       `-._`-.\  \`. 
              '`:. :        |' `. `\  ) \ 
                 ` ;:       |    `--\__,' 
                   '`      ,' 
                       ,-' 
*/

//Imports 
#include <Servo.h>

//Set port numbers for I/O 
int pedalPot = 0;
int victorPort = 3;
int btnReverse = 4;
int btnNeutral = 5;
int btnDrive = 6;
int btnReset = 7;
int ledReverse = 9;
int ledNeutral = 10;
int ledDrive = 11;


//Proximity sensors (tbd at a later date - possibly need an Arduino MEGA)
int psLeft = ?;
int psRight = ?;
int psFwd = ?;
int psBckwd = ?;

//Deadzone value for the pedal
int deadzone = 10; 

//Range values for potentiometer mapping
int minPotRange =90;
int maxPotRange = 180;

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
    if(drive && pedalVal >= deadzone){
      writeVal = pedalVal;
      if(writeVal <= 180){ //Failsafe. Prevents program from crashing if value is greater than 180
        victor.write(writeVal);
      }
    }  
   if(btnNeutral == HIGH){
     neutral = true;
     drive = false;
     reverse = false;
     if(neutral){
      victor.write(90); 
      }
    }
    if(btnReverse == HIGH){
      reverse = true;
      drive = false;
      neutral = false;
      if(reverse && pedalVal >= deadzone){
       writeVal = pedalVal - 180;
       writeVal = abs(writeVal); 
       victor.write(writeVal);
      }  
    }
    if(btnReset == HIGH){
      reverse = false;
      drive = false;
      neutral = true; 
    }
}

boolean sensor(psLeft, psRight, psFwd, psBckwd){
 int minProximity = 2;
 boolean left;
 boolean right;
 boolean forward;
 boolean backward;
 boolean driveIsOk;
 if(psLeft >= minProximity){
  left = true;
 } 
 if(psRight >= minProximity){
  right = true; 
 }
 if(psFwd >= minProximity){
  forward = true; 
 }
 if(psBckwd >= minProximity){
  backward = true; 
 }
 if(left && right && forward && backward){
  driveIsOk = true;
 }
 else{
  driveIsOk = false; 
 }
 return driveIsOk;
}
