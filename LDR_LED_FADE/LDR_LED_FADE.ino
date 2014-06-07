int LDR = A3;//Pino do LDR
int LED = 6;//Pino do LED
int targetBrightness = 0;//Brilho alvo do LED
int currentBrightness = 0;//Brilho atual do LED
int fadeAmount = 1;    //Variacao do brilho do led a cada iteracao.

void setup()  { 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
} 

void loop()  { 
  int darknessLevel = analogRead(LDR);
  
  targetBrightness = 255 - int(darknessLevel/4);
  Serial.println(targetBrightness);
  if(currentBrightness < targetBrightness && targetBrightness > 200){
    currentBrightness = currentBrightness + fadeAmount;
    if(currentBrightness > 255)
      currentBrightness = 255;
  }else if(currentBrightness > targetBrightness){
    currentBrightness = currentBrightness - fadeAmount;
    if(currentBrightness < 100)
      currentBrightness = 0;
  }
  analogWrite(LED, currentBrightness);
}
