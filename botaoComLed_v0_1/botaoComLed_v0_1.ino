
#define RED 2 // RGB PWM RED
#define GREEN 3 // RGB PWM GREEN
#define BLUE 4 // RGB PWM BLUE



int ledState = 0;
int red_power = 255, green_power = 0, blue_power = 0; // valores de 0 a 255 (variá-los para obter cores diferentes).
int colorState = 1;
int stepSize = 5;
int waitStepSize = 30;
int standbySize = 30;
int boo = 0;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode (RED, OUTPUT); // Pino 2 declarado como saída
  pinMode (GREEN, OUTPUT); // Pino 3 declarado como saída
  pinMode (BLUE, OUTPUT); // Pino 4 declarado como saída;
}

char letra = 'b';
// the loop routine runs over and over again forever:
void loop() {
  //red_power = 255, green_power = 0, blue_power = 0;
  Serial.print("red_power:");Serial.print(red_power);
  Serial.print("     ");
  Serial.print("green_power:");Serial.print(green_power);
  Serial.print("     ");
  Serial.print("blue_power:");Serial.println(blue_power);
  if(Serial.available() > 0){
    letra = (char) Serial.read();
  }
  if(letra == 'a' || boo == 1){
      if(colorStateChange() == 1){
        boo = 0;
        Serial.println("boo = 0");
      }else{
        boo = 1;
        Serial.println("boo = 1");
      }
      letra = 'b';
    }
  delay(standbySize);
}

int colorStateChange(){
  analogWrite (GREEN, green_power); // Envia o sinal de "green" para o terminal de cor verde do LED
  analogWrite (BLUE, blue_power); // Envia o sinal de "blue" para o terminal de cor azul do LED
  analogWrite (RED, red_power);
  if(colorState == 1)
  {
    if(othersToGreen() == 1)
    {
      delay(standbySize);
      colorState = 2;
      return 1;
    }else{
      return 0;
    }
  }
  else if(colorState == 2)
  {
    if(othersToRed() == 1)
    {
      delay(standbySize);
      colorState = 3;
      return 1;
    }else{
      return 0;
    }
  }
  else if(colorState == 3)
  {
    if(othersToBlue() == 1)
    {
      delay(standbySize);
      colorState = 1;
      return 1;
    }else{
      return 0;
    }
  }
}

int othersToBlue(){
  if(blue_power < 255){
    blue_power = blue_power + stepSize;
  }
  if(green_power > 0){
    green_power = green_power - stepSize;
  }
  if(red_power > 0){
    red_power = red_power - stepSize;
  }
  delay(waitStepSize);
  if(green_power == 0 && red_power == 0)
  {
    return 1;
  }
  return 0;
}

int othersToRed(){
  if(red_power < 255){
    red_power = red_power + stepSize;
  }
  if(green_power > 0){
    green_power = green_power - stepSize;
  }
  if(blue_power > 0){
    blue_power = blue_power - stepSize;
  }
  delay(waitStepSize);
  if(green_power == 0 && blue_power == 0)
  {
    return 1;
  }
  return 0;
}

int othersToGreen(){
  if(green_power < 255){
    green_power = green_power + stepSize;
  }
  if(red_power > 0){
    red_power = red_power - stepSize;
  }
  if(blue_power > 0){
    blue_power = blue_power - stepSize;
  }
  delay(waitStepSize);
  if(red_power == 0 && blue_power == 0)
  {
    return 1;
  }
  return 0;
}
