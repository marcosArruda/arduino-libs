
#include <VirtualWire.h>

#define txPin 5
#define ledPin 13
#define dataSize 30
#define fixMemDelay 3

byte index = 0;
byte lastIndex = 0;
char inChar=-1;
char inData[dataSize];
char repo[90];
char message[90];

int whatToDo = -1;
const int ON13 = 1;
const int OFF13 = 2;
const int GET_STATUS = 3;
const int RF_MESSAGE = 4;

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
  
  switch(whatToDo){
    case ON13:
      digitalWrite(ledPin, HIGH);
      Serial.println(message);
      break;
    case OFF13:
      digitalWrite(ledPin, LOW);
      Serial.println(message);
      break;
    case GET_STATUS:
    case RF_MESSAGE:
    default:
      delay(fixMemDelay); //do nothing
      Serial.println(inData);
      Serial.println(whatToDo);
  }
  delay(500);
  
  //clean and finish
  cleanSerialMemory();
}

void waitForSerialInput(){
  delay(fixMemDelay);
  index = 0;
  while (Serial.available() == 0) ;
  delay(fixMemDelay);
}

void receiveData(){
  int messageIndex = 0;
  while(Serial.available() > 0){
    if(index < (dataSize - 1)){
      inChar = Serial.read();
      inData[index] = inChar;
      if(index == 4){
        char _aux[2];
        _aux[0] = inChar;
        whatToDo = atoi(_aux);
      } else if(index >= 10 && inChar != ';'){
        message[messageIndex] = inChar;
        messageIndex++;
      }
      index++;
      delay(fixMemDelay);
    }
  }
  Serial.flush();
  lastIndex = index;
  index = 0;
  delay(fixMemDelay);
}

int getAction(){
  
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
  memset(message, 0, strlen(message));
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
