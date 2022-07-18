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

#define fl_IR 6
#define fr_IR 7
#define l_IR 16
#define r_IR 17

#define echo 18
#define trig 19

#define M1LH 8  //Left High
#define M1RH 9
#define M1LL 10
#define M1RL 11
#define M2LH 12
#define M2RH 13
#define M2LL 14
#define M2RL 15

int count = 1;
int distance;
long duration;

int fl_SensorState;
int fr_SensorState;
int l_SensorState;
int r_SensorState;

void setup() {
 sM1.attach(servo1Pin);
 sM2.attach(servo2Pin);
 sM3.attach(servo3Pin);
 sM4.attach(servo4Pin);
 sM5.attach(servo5Pin);
 pinMode(fl_IR, INPUT);
 pinMode(fr_IR, INPUT); 
 pinMode(l_IR, INPUT);
 pinMode(r_IR, INPUT);
 pinMode(echo, INPUT);
 pinMode(trig, OUTPUT);
 pinMode(M1LH, OUTPUT);
 pinMode(M1RH, OUTPUT);
 pinMode(M1LL, OUTPUT);
 pinMode(M1RL, OUTPUT);
 pinMode(M2LH, OUTPUT);
 pinMode(M2RH, OUTPUT);
 pinMode(M2LL, OUTPUT);
 pinMode(M2RL, OUTPUT);
}

void loop() {
fl_SensorState = digitalRead(fl_IR);
fr_SensorState = digitalRead(fr_IR);

if (fr_SensorState > 1 && fl_SensorState < 1)  {  //Turn Right
  right(255);
}
else if (fr_SensorState < 1 && fl_SensorState > 1) {  //Left
  left(255);
}
else if (fr_SensorState > 1 && fl_SensorState > 1) {  //Forward
  forward(255);
}

else if (fr_SensorState < 1 && fl_SensorState < 1) {   //Stop 
  stop_all();
  allign();
  harvest();
}

stop_all();
delay(100);
}

void allign(){
  do { 
    l_SensorState = digitalRead(l_IR);
    r_SensorState = digitalRead(r_IR);
    if (r_SensorState > 1 && l_SensorState < 1){
      right(100);
    }
    else if (r_SensorState > 1 && l_SensorState < 1){
      left(100);
    }
    else if (r_SensorState > 1 && l_SensorState > 1){
      if(calc_distance() < 30)  { //crossed the line
        backward(50);
      }
      else{
        forward(50);
      }
    }
    else if (r_SensorState < 1 && l_SensorState < 1){
      break;
    }
  } while(0);
}

int calc_distance(){
  digitalWrite(trig, LOW); //clear trigger pin from previous loop
  delayMicroseconds(5); //using Microseconds as the delay needs to be very very short - delay uses millisecond
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  //trigger pin high for 10 microsecond - sound wave sent
  digitalWrite(trig, LOW); //reset trigger pin

  duration = pulseIn(echo, HIGH);  //reading and storing time it takes for echo
  //duration contains sound travel time in microseconds
 
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  return distance;  //distance in cm
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

void harvest(){
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

void fruitPick(int deg1,int deg2, int deg3, int deg4){
  armMove(deg1,deg2,deg3,deg4);
  clawClose();  
}

void fruitPlace(){
  armMove(0,0,0,0);
  clawOpen();
}

void tree1(){
  fruitPick(0,0,0,0);  //1
  fruitPlace();
  fruitPick(0,0,0,0);  //2
  fruitPlace();
}

void tree2(){
  fruitPick(0,0,0,0);  //1
  fruitPlace();
  fruitPick(0,0,0,0);  //2
  fruitPlace();
  fruitPick(0,0,0,0);  //3
  fruitPlace();
}

void tree3(){
  fruitPick(0,0,0,0);  //1
  fruitPlace();
  fruitPick(0,0,0,0);  //2
  fruitPlace();
  fruitPick(0,0,0,0);  //3
  fruitPlace();
  fruitPick(0,0,0,0);  //4
  fruitPlace();
}

void unload(){
  armMove(0,0,0,0);
  clawClose();
  armMove(0,0,0,0);
  sM4.write(0);  //Claw Rotate
  delay(10000); //turn off
}
