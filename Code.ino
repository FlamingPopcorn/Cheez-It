//Includes
#include <Servo.h>

//Sets motor varibles
int ESC1 = 3;
Servo ESCs[1];

//Sets input pins
int analogX = A0;

// Defines sppeds varibles and conversion
double speedL;
double speedR;
double conversion = 500.0/540.0;

//void search() {
//  for (int i = 0; i < 4095; i++){
//    ESCs[0].write(i);
//    Serial.println(i);
//    delay(50);
//  }
//}

//Debug function to print speed varibles
void debug() {
  Serial.println("----------[ ESCs ]---------");
  Serial.println(analogRead(analogX));
  Serial.println(speedL);
  Serial.println(speedR);
  Serial.println("---------------------------");
}

// Actual code and functions

//Get inputs from the controller
void getInput() {
  speedL = (analogRead(analogX)*conversion);
}

//Writes the speed to each ESC / 1000 = full back / 1500 = nothing / 2000 = full forward
void setSpeeds() {
  ESCs[0].write(speedL + 1000);
}

//Sets the robot up
void setup() {
  //Starts Serial monitor
  Serial.begin(115200);

  //Sets ESC output pins
  pinMode(ESC1, OUTPUT);
  ESCs[0].attach(ESC1);

  //Writes the neutral throttle value and waits
  ESCs[0].write(1500);
  //delay(5000);
}

//Loop to call all functions and make the robot work
void loop() {
  getInput();
  setSpeeds();

  //debug();
}
