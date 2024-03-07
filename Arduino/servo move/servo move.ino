#include <Servo.h>

Servo myservo1; //servo for the small container d4
Servo myservo2; //servo for the large container d5
Servo myservo3; //servo for the bridge d13

int pos1 = 90; //servo1 position for setup
int pos2 = 0; //servo1 to drop container and bridge
int pos3 = 180; //servo3 position for the bridge
int pos4 = 50;  //servo2 posiiton for setup
int pos5 = 150; //servo2 to drop container


void setup(){
 
  myservo1.attach(4);
  myservo2.attach(5);
  myservo3.attach(13);
 
 
}

void loop(){
//works for servo 1(small package) and for servo 3 (bridge)
servoInit(myservo1, pos1); 
delay(500);
servoInit(myservo3, pos2); 
delay(500);
servoInit(myservo2, pos4);
delay(500);
  
servoUnlock(myservo3, pos3);
delay(500);
servoUnlock(myservo1, pos2);
delay(500);
servoUnlock(myservo2, pos5);
 
 
// servoUnlock(myservo3, pos3);
 // delay(500);
 
//  myservo1.write(0);
//  delay(15);
//
//  delay(100);
//
//  for (pos2 = 90; pos2 <= 180; pos2 += 1) {
//    myservo2.write(pos2);
//    delay(15);
//  }
//
//  delay(1000);
//
//  for (pos3 = 0; pos3 <= 180; pos3 += 1) {
//    myservo3.write(pos3);
//    delay(15);
//  }
//
//  delay(100);
}

void servoInit(Servo servoi, int initial_pos) {
  servoi.write(initial_pos);
  delay(100);
  //servoi.detach();
}
void servoUnlock( Servo servo, int pos_move){
 
  servo.write(pos_move);
  delay(500);
  servo.detach();
  }
