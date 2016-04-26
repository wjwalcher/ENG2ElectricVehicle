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
int brakeLightOne = 12;
int brakeLightTwo = 13;
int turnSignalOne = A5;
int turnSignalTwo = A6;

//Clean up this shit later 
int tsUno = 0;
int pedalVal;
int writeVal;
bool ts1IsOn = false;

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
  pinMode(brakeLightOne, OUTPUT);
  victor.attach(victorPort);
}

void loop(){
  //The Code between these two arrows (> <) has issues that need to be fixed. START >
  tsUno = analogRead(turnSignalOne);
  if(tsUno == HIGH){
    ts1IsOn = true;
  }
  if(ts1IsOn){
    digitalWrite(brakeLightOne, HIGH);
    delay(350);
    digitalWrite(brakeLightOne, LOW);
    delay(350);
  }
  // < END
  
  pedalVal = analogRead(pedalPot);
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
}
