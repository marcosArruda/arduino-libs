//Test and text transmission with RF module for Arduino http://zygzax.com
//TRANSMITTER
#include <VirtualWire.h>

#define txPin 32
#define ledPin 31

String MESSAGE_PREFIX = "@M";
String LED_PREFIX = "@L";

void setup()
{
    Serial.begin(9600);
    vw_set_ptt_inverted(true);// Required by the RF module
    vw_setup(2000);// bps connection speed
    vw_set_tx_pin(txPin);// Arduino pin to connect the receiver data pin
    pinMode(ledPin, OUTPUT);
}

int i = 0;

void loop()
{
  
   digitalWrite(31, HIGH);
   sendData2(MESSAGE_PREFIX+"Marcos "+String((++i)), 0, 30);
   Serial.println(MESSAGE_PREFIX+"Marcos "+String((i)));
   //sendData2(LED_PREFIX+"1", 1, 8000);
   //sendData2(LED_PREFIX+"0", 0, 1000);
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
