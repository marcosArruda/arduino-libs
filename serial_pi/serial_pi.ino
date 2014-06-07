

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the charac
byte lastIndex = 0; // Index into array; where to store the charac
char junk = ' ';


void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.flush();
}

void loop()
{
  index = 0;
  waitForSerialInput();
  while(Serial.available() > 0){
    if(index < 19){
      inChar = Serial.read();
      inData[index] = inChar;
      index++;
    }
  }
  Serial.flush();
  lastIndex = index;
  index = 0;
  char repo[30];
  concatArr(repo, inData, " plustext");
    Serial.write(repo);
  //Serial.println();
  
}

void waitForSerialInput(){
  while (Serial.available() == 0) ;
}

void concatArr(char r[30], char str1[20], char str2[]){
  sprintf(r, "%s%s", str1,str2);
}
