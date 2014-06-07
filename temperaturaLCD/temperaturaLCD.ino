
/*
  Variaveis
*/
#include <LiquidCrystal.h> // Inclui a biblioteca para utilizar o LCD.

#define tempSensorPin A1 // Define o pino A1 como “sensor”
float S = 0; // Variável para ler o sinal do pino do Arduino
float T = 0; // Variável que recebe o valor convertido para temperatura.
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup(){
  lcd.begin(16, 2); // Diz para o Arduino que o display é 16x2.
  lcd.print("Temperatura: "); // Manda o texto para a tela do display
  Serial.begin(9600);
}

void loop(){
  S = analogRead (tempSensorPin);  /*  Manda o Arduino ler o pino e armazena

 o valor em “Ventrada”. */

  T = (S * 500) / 1023;
  lcd.setCursor(0, 1);
  Serial.println();
  Serial.print(S);
  Serial.println(" from 1023.");
  
  Serial.print(T);
  Serial.println(" C");
  lcd.print(T);
  lcd.print(" C");
  delay(1000);
}
