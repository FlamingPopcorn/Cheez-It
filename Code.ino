#include <Servo.h>

int ESC1 = 3;
Servo ESCs[1];

int analogX = A0;

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

void debug() {
  Serial.println("----------[ ESCs ]---------");
  Serial.println(analogRead(analogX));
  Serial.println(speedL);
  Serial.println(speedR);
  Serial.println("---------------------------");
}

// Actual code and functions

void getInput() {
  speedL = (analogRead(analogX)*conversion);
}

void setSpeeds() {
  ESCs[0].write(speedL + 1000);
}

void setup() {
  Serial.begin(115200);
  pinMode(ESC1, OUTPUT);
  ESCs[0].attach(ESC1);
  ESCs[0].write(1500);delay(5000);
}

void loop() {
  getInput();
  setSpeeds();

  //debug();
}

