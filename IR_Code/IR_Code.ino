#define left_IR 1
#define right_IR 2

int left_SensorState;
int right_SensorState;

void setup() {
  pinMode(left_IR, INPUT);
  pinMode(right_IR, INPUT);  
}

void loop() {

left_SensorState = analogRead(left_IR);
right_SensorState = analogRead(right_IR);

if (right_SensorState > 500 && left_SensorState < 500)  {  //Turn Right
  
}
else if (right_SensorState < 500 && left_SensorState > 500) {  //Left
  
}
else if (right_SensorState > 500 && left_SensorState > 500) {  //Forward

}

else if (right_SensorState < 500 && left_SensorState < 500) {   //Stop 

}
 
}










 
