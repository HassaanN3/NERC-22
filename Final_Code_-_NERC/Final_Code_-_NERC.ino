//TODO
//1. Add values to armMove function calls
//2. Default position
//3. Claw movement
//4. Pins
//5. Stop Inertia - Testing

#include <Servo.h>

Servo sM1,sM2,sM3,sM4,sM5;

#define servo1Pin 1
#define servo2Pin 2
#define servo3Pin 3
#define servo4Pin 4
#define servo5Pin 5

#define left_IR 6
#define right_IR 7

#define M1LH 8  //Left High
#define M1RH 9
#define M1LL 10
#define M1RL 11
#define M2LH 2
#define M2RH 5
#define M2LL 16
#define M2RL 17

int count = 1;

int left_SensorState;
int right_SensorState;

void setup() {
 sM1.attach(servo1Pin);
 sM2.attach(servo2Pin);
 sM3.attach(servo3Pin);
 sM4.attach(servo4Pin);
 sM5.attach(servo5Pin);
 pinMode(left_IR, INPUT);
 pinMode(right_IR, INPUT);  
 pinMode(M1LH, OUTPUT);
 pinMode(M1RH, OUTPUT);
 pinMode(M1LL, OUTPUT);
 pinMode(M1RL, OUTPUT);
 pinMode(M2LH, OUTPUT);
 pinMode(M2RH, OUTPUT);
 pinMode(M2LL, OUTPUT);
 pinMode(M2RL, OUTPUT);
 Serial.begin(9600);
}

void loop() {

left_SensorState = analogRead(left_IR);
right_SensorState = analogRead(right_IR);

if (right_SensorState > 500 && left_SensorState < 500)  {  //Turn Right
  right(255);
}
else if (right_SensorState < 500 && left_SensorState > 500) {  //Left
  left(255);
}
else if (right_SensorState > 500 && left_SensorState > 500) {  //Forward
  forward(255);
}

else if (right_SensorState < 500 && left_SensorState < 500) {   //Stop 
  stop_all();
  fruitPick();
}
stop_all();
delay(200);
}

void forward(int speed_factor) { // Turns both motor CW -> forward direction
    // Motor 1 -> Clockwise
    analogWrite(M1LH, speed_factor);
    analogWrite(M1RH, 0);
    digitalWrite(M1LL, LOW);
    digitalWrite(M1RL, HIGH);

    // Motor 2 -> Clockwise
    analogWrite(M2LH, speed_factor);
    analogWrite(M2RH, 0);
    digitalWrite(M2LL, LOW);
    digitalWrite(M2RL, HIGH);
}

void backward(int speed_factor) { // Turns both motor CCW -> backward direction
    // Motor 1 -> Counter Clockwise
    analogWrite(M1LH, 0);
    analogWrite(M1RH, speed_factor);
    digitalWrite(M1LL, HIGH);
    digitalWrite(M1RL, LOW);

    // Motor 2 -> Counter Clockwise
    analogWrite(M2LH, 0);
    analogWrite(M2RH, speed_factor);
    digitalWrite(M2LL, HIGH);
    digitalWrite(M2RL, LOW);
}

void left(int speed_factor) { // Turns left motor CCW and right motor CW
    // Robot turns left around its own axis
    // Motor 1 -> Counter Clockwise
    analogWrite(M1LH, 0);
    analogWrite(M1RH, speed_factor);
    digitalWrite(M1LL, HIGH);
    digitalWrite(M1RL, LOW);

    // Motor 2 -> Clockwise
    analogWrite(M2LH, speed_factor);
    analogWrite(M2RH, 0);
    digitalWrite(M2LL, LOW);
    digitalWrite(M2RL, HIGH);
}

void right(int speed_factor) { // Turns left motor CW and right motor CCW
    // Robot turns right around its own axis
    // Motor 1 -> Clockwise
    analogWrite(M1LH, speed_factor);
    analogWrite(M1RH, 0);
    digitalWrite(M1LL, LOW);
    digitalWrite(M1RL, HIGH);

    // Motor 2 -> Counter Clockwise
    analogWrite(M2LH, 0);
    analogWrite(M2RH, speed_factor);
    digitalWrite(M2LL, HIGH);
    digitalWrite(M2RL, LOW);
}

void stop_all() { // Turns both motor off -> Stopped
    // Motor 1 -> Stop
    analogWrite(M1LH, 0);
    analogWrite(M1RH, 0);
    digitalWrite(M1LL, LOW);
    digitalWrite(M1RL, LOW);

    // Motor 2 -> Stop
    analogWrite(M2LH, 0);
    analogWrite(M2RH, 0);
    digitalWrite(M2LL, LOW);
    digitalWrite(M2RL, LOW);
}

void defaultPos(){
  armMove(0,0,0,0);
  clawOpen();
}

void armMove(int deg1,int deg2, int deg3, int deg4) {
  sM1.write(deg1);
  sM2.write(deg2);
  sM3.write(deg3);
  sM4.write(deg4);  
}

void clawOpen(){
  sM5.write(0);
}

void clawClose(){
  sM5.write(180);
}

void fruitPick(){
  if(count == 1){
    tree1();
  }
  else if(count == 2){
    tree2();
  }
  else if(count == 3){
    tree3();
  }
  else{ //unload
    unload();
  }
  count++;
}

void tree1(){
  defaultPos();
  //Fruit 1
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
  //Fruit 2
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
}

void tree2(){
  defaultPos();
  //Fruit 1
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
  //Fruit 2
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
  //Fruit 3
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
}

void tree3(){
  defaultPos();
  //Fruit 1
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
  //Fruit 2
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
  //Fruit 3
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  clawOpen();
  defaultPos();
  //Fruit 4
  armMove(0,0,0,0);
  clawClose();
  fruitPlace();
  defaultPos();
}

void fruitPlace(){
  armMove(0,0,0,0);
  clawOpen();
}

void unload(){
  armMove(0,0,0,0);
  clawClose();
  armMove(0,0,0,0);
  sM4.write(0);  //Claw Rotate
  delay(10000); //turn off
}
