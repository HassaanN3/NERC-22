//TODO
//1. Add values to armMove function calls
//2. Default position
//3. claw movement
//4. Pins

#include <Servo.h>

Servo sM1,sM2,sM3,sM4,sM5;

#define servo1Pin 1
#define servo2Pin 2
#define servo3Pin 3
#define servo4Pin 4
#define servo5Pin 5

int count = 1;

void setup() {
 sM1.attach(servo1Pin);
 sM2.attach(servo2Pin);
 sM3.attach(servo3Pin);
 sM4.attach(servo4Pin);
 sM5.attach(servo5Pin);
}

void loop() {
  
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
