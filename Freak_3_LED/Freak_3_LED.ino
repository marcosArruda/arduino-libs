

int GREEN[2] = {4, 0};
int YELLOW[2] = {3, 0};
int RED[2] = {5, 1};
int TEMPOMIN = 30;
int TEMPOMAX = 1000;
int DECREMENT = 100;
int TEMPO;
int currentStep = 0;
boolean lock = false;
int lockCount = 0;
int lockMax = 70;

void setup(){
  Serial.begin(9600);
  pinMode(GREEN[0], OUTPUT);
  pinMode(YELLOW[0], OUTPUT);
  pinMode(RED[0], OUTPUT);
  
  TEMPO = TEMPOMAX;
  
  //analogWrite(PINO, 0-255);
}

void loop(){
  //delay(100);
  //return;
  
  digitalWrite(GREEN[0], GREEN[1]);
  digitalWrite(YELLOW[0], YELLOW[1]);
  digitalWrite(RED[0], RED[1]);
  delay(TEMPO);
  nextStep();
  //tempo em porcetagem a tirar (somente valor inteiro)
  int TEMPO_MENOS_5_PERC = int(TEMPO * 0.05); //5% do TEMPO
  if(TEMPO_MENOS_5_PERC == 0){
    TEMPO_MENOS_5_PERC = 1;
  }
  if(TEMPO < TEMPOMIN){
    if(lockCount > lockMax){
      lockCount = 0;
      TEMPO = TEMPOMAX;
    }else{
      lockCount++;
      //TEMPO = TEMPOMIN;
    }
  }else{
    TEMPO = TEMPO - TEMPO_MENOS_5_PERC;
  }
  Serial.println(TEMPO);
}

void nextStep(){
  if(currentStep == 0){
    GREEN[1] = 0;
    YELLOW[1] = 1;
    RED[1] = 0;
    currentStep++;
  }
  else if(currentStep == 1){
    GREEN[1] = 1;
    YELLOW[1] = 0;
    RED[1] = 0;
    currentStep++;
  }
  else
  {
    GREEN[1] = 0;
    YELLOW[1] = 0;
    RED[1] = 1;
    currentStep = 0;
  }
  
  
}
