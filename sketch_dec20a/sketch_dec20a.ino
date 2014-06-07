#include <Servo.h>

Servo myservo;
int pos = 0;
void setup(){
  myservo.attach(13);
}

void loop(){
  //return;
  for(pos=0; pos<180; pos++){
    myservo.write(pos);
    delay(5);
  }
  for(pos=180; pos>=1; pos--){
    myservo.write(pos);
    delay(5);
  }
}
