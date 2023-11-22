//Includes
#include <Servo.h>
#include <IBusBM.h>

//Creates IBus Object. Plug IBus pin into RX1 of Arduino
IBusBM IBus;

int channel1 = 0;
int channel2 = 1;
int channel3 = 2;
int channel4 = 3;
int channel5 = 4;
int channel6 = 5;

//Sets motor varibles / 1 and 3 are left side and 2 and 4 are right side
int ESC1 = 3;   // 1 ----- 2
int ESC2 = 5;   // | Front |
int ESC3 = 6;   // |       |
int ESC4 = 9;   // |       |
Servo ESCs[4];  // 3 ----- 4


// Defines speeds varibles and conversion
int inputL, speedL, inputR, speedR, speedLimit;
double powerPercent;

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
  Serial.println("Channel 2: "+ String(IBus.readChannel(channel2)));
  Serial.println("Channel 3: "+ String(IBus.readChannel(channel3)));
  Serial.println("Channel 6: "+ String(IBus.readChannel(channel6)));
  Serial.println("Power Percentage: "+ String(powerPercent)); 
  Serial.println("Left side Speed: "+ String(speedL));
  Serial.println("Right side Speed: "+ String(speedR));
  Serial.println("---------------------------");
  delay(250);
}



// Actual code and functions

//Get inputs from the controller
void getInput() {
  inputL = IBus.readChannel(channel3);
  inputR = IBus.readChannel(channel2);
  speedLimit = IBus.readChannel(channel6);
  
  powerPercent = map(speedLimit, 1000, 2000, 0, 100) / 100.0;
  speedL = map(inputL, 1040, 2000, (1500 - (500 * powerPercent)), (1500 + (500 * powerPercent)));
  speedR = map(inputR, 1000, 1980, (1500 - (500 * powerPercent)), (1500 + (500 * powerPercent)));
}

//Writes the speed to each ESC / 1000 = full backward / 1500 = neutral / 2000 = full forward
void setSpeeds() {
  //Left side
  ESCs[0].write(speedL);
  ESCs[2].write(speedL);
  
  //Right Side
  ESCs[1].write(speedR);
  ESCs[3].write(speedR);
}

//-----------------WIP code----------------

//Future function to have a way to remotely stop the robot
void EStop() {
  for (int i = 0; i < 4; i++) {
    ESCs[i].write(1500);
  }
  while (1 == 1) {
    delay(100);
  }
}

//Future function to set led colors to represent information about current state of the robot
void infoLEDs() {
}

//-----------End of WIP code--------------

//Sets the robot up
void setup() {

  //Starts IBus on RX1 or Serial1 Pin
  IBus.begin(Serial1);

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
  delay(5000);
  for (int i = 0; i < 4; i++) {
    ESCs[i].write(1500);
  }
  delay(3000);
}

//Loop to call all functions and make the robot work
void loop() {
  getInput();
  setSpeeds();

  debug();
}
