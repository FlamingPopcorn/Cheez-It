//Includes
#include <Servo.h>

//Sets motor varibles / 1 and 3 are left side and 2 and 4 are right side
int ESC1 = 3;        // 1 ----- 2
int ESC2 = 5;        // | Front |
int ESC3 = 6;        // |       |
int ESC4 = 9;        // |       |
Servo ESCs[4];       // 3 ----- 4

//Sets input pins
int analogL = A0;
int analogR = A1;


// Defines sppeds varibles and conversion
double speedL;
double speedR;
double conversion = 500.00/540.00;

//void search() {
//  for (int i = 0; i < 4095; i++){
//    ESCs[0].write(i);
//    Serial.println(i);
//    delay(100);
//  }
//}

//Debug function to print speed varibles
void debug() {
  Serial.println("----------[ ESCs ]---------");
  Serial.println(analogRead(analogL));
  Serial.println(analogRead(analogR));
  Serial.println(speedL);
  Serial.println(speedR);
  Serial.println("---------------------------");
}



// Actual code and functions

//Get inputs from the controller
void getInput() {
  speedL = (analogRead(analogL)*conversion);
  speedR = (analogRead(analogR)*conversion);
}

//Writes the speed to each ESC / 1000 = full backward / 1500 = neutral / 2000 = full forward
void setSpeeds() {
  //Left side
  ESCs[0].write(speedL + 1000);
  ESCs[2].write(speedL + 1000);
  
  //Right Side
  ESCs[1].write(speedR + 1000);
  ESCs[3].write(speedR + 1000);
}

//-----------------WIP code----------------

//Future function to have a way to remotely stop the robot
void EStop() {
  for (i=0;i<4;i++) {
    ESCs[i].write(1500);
  }
  while(1 == 1) {
    delay(100);
  }
}

//Future function to set led colors to represent information about current state of the robot
void infoLEDs() {

}

//-----------End of WIP code--------------

//Sets the robot up
void setup() {
  //Starts Serial monitor
  Serial.begin(115200);

  //Sets ESC output pins
  pinMode(ESC1, OUTPUT);
  pinMode(ESC2, OUTPUT);
  pinMode(ESC3, OUTPUT);
  pinMode(ESC4, OUTPUT);
  ESCs[0].attach(ESC1);
  ESCs[1].attach(ESC2);
  ESCs[2].attach(ESC3);
  ESCs[3].attach(ESC4);

  //Writes the neutral throttle value to all ESCs and waits
  for (i=0;i<4;i++) {
    ESCs[i].write(1500);
  }
  delay(1000);
}

//Loop to call all functions and make the robot work
void loop() {
  getInput();
  setSpeeds();

  //debug();
}
