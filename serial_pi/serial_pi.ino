
#include <VirtualWire.h>

#define txPin 5
#define ledPin 13
#define dataSize 30
#define fixMemDelay 3

int whatToDo = -1;
byte index = 0;
byte lastIndex = 0;
char inChar=-1;
char inData[dataSize];
char repo[90];


String MESSAGE_PREFIX = "@M";
String LED_PREFIX = "@L";

enum DoThings { SEND_HELLO, REPPLY_ME };
int charToEnum(char dataReceived[]){
  if(strlen(dataReceived) > 10){
    return SEND_HELLO;
  } else {
    return REPPLY_ME;
  }
}

void setup(){
  Serial.begin(9600); //bps
  Serial.flush();
  vw_set_ptt_inverted(true);// Required by the RF module
  vw_setup(2000);// bps connection speed
  vw_set_tx_pin(txPin);// Arduino pin to connect the receiver data pin
  pinMode(ledPin, OUTPUT);
}

void loop(){
  waitForSerialInput();
  receiveData();
  
  whatToDo = charToEnum(inData);
  
  switch(whatToDo){
    case REPPLY_ME:
      appendAndRepply();
      break;
    case SEND_HELLO:
    default:
      delay(fixMemDelay); //do nothing
      Serial.println(inData);
  }
  
  //clean and finish
  cleanSerialMemory();
}

void waitForSerialInput(){
  delay(fixMemDelay);
  index = 0;
  while (Serial.available() == 0) ;
}

void receiveData(){
  while(Serial.available() > 0){
    if(index < (dataSize - 1)){
      inChar = Serial.read();
      inData[index] = inChar;
      index++;
      delay(fixMemDelay);
    }
  }
  Serial.flush();
  lastIndex = index;
  index = 0;
  delay(fixMemDelay);
}

void appendAndRepply(){
  concatArr(repo, "initialtext ", inData, " endtext");
  delay(fixMemDelay);
  Serial.println(repo);
  Serial.flush();
}

void cleanSerialMemory(){
  delay(fixMemDelay);
  Serial.flush();
  delay(fixMemDelay);
  memset(inData, 0, strlen(inData));
  whatToDo = -1;
}

void concatArr(char r[90], char initial[30], char middle[30], char final[30]){
  sprintf(r, "%s%s%s", initial,middle,final);
}

void sendData(const char *msg, int ledStatus, int delayTime){
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
  digitalWrite(ledPin, ledStatus);
  delay(delayTime);
}

void sendData2(String m, int ledStatus, int delayTime){
  char msg[50];
  m.toCharArray(msg, 50);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
  digitalWrite(ledPin, ledStatus);
  delay(delayTime);
}
