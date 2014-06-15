#define txPin 5
#define ledPin 13
#define dataSize 30
#define fixMemDelay 3

byte index = 0;
byte lastIndex = 0;
char inChar=-1;
char inData[dataSize];

void setup() {
  Serial.begin(9600);
}

void loop() {
  waitForSerialInput();
  receiveData();
  delay(fixMemDelay);        // delay in between reads for stability
  int d = atoi(inData);
  Serial.println(d);
  delay(fixMemDelay);
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

void cleanSerialMemory(){
  delay(fixMemDelay);
  Serial.flush();
  delay(fixMemDelay);
  memset(inData, 0, strlen(inData));
}
