//Test and text transmission with RF module for Arduino http://zygzax.com
//RECEIVER
#include <VirtualWire.h>

#define rxPin 3
#define ledPin 2

void setup()
{
    Serial.begin(9600);          // Configure the serial connection to the computer
    vw_set_ptt_inverted(true);  // Required by the RF module
    vw_setup(2000);            // bps connection speed
    vw_set_rx_pin(rxPin);         // Arduino pin to connect the receiver data pin
    vw_rx_start();     // Start the receiver
    pinMode(ledPin, OUTPUT);
    Serial.println("Working. Listening to RF signals..");
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  //checa pra ver se recebeu mensagem
  if (vw_get_message(buf, &buflen))
  {
    String message = "";
    for (int i = 0; i < buflen; i++){
      message += char(buf[i]);
    }
    if(message.startsWith("@M")){
      Serial.println(phrase("Mensagem recebida: '", message.substring(2), "'"));
    }else if(message.startsWith("@L")){
      setLed(message.substring(2));
    }else{
      Serial.println(phrase("Full Message: '", message, "'"));
    }
  }
}

void setLed(String ledStatus){
  if(ledStatus == "0"){
    digitalWrite(ledPin, LOW);
  }else{
    digitalWrite(ledPin, HIGH);
  }
}

String phrase(String init, String midle, String final){
  String m = init;
  m += midle;
  m += final;
  return m;
}
