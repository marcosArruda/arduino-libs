/*
// See the full tutorial on IRs at http://www.ladyada.net/learn/sensors/ir.html
*/

#include <IRArruda.h>
int IRPin = 11; // LED connected to digital pin 13

int minTime = 1000;
void setup() {

	pinMode(IRPin, OUTPUT);
}
void loop()
{
        delay(minTime);
        volumeUp();
}
//// This procedure sends a 38KHz pulse to the IRledPin
//// for a certain # of microseconds. We'll use this whenever we need to send codes

void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
  cli(); // this turns off any background interrupts
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRPin, HIGH); // this takes about 3 microseconds to happen
    delayMicroseconds(10); // hang out for 10 microseconds, you can also change this to 9 if its not working
    digitalWrite(IRPin, LOW); // this also takes about 3 microseconds
    delayMicroseconds(10); // hang out for 10 microseconds, you can also change this to 9 if its not working
    // so 26 microseconds altogether
    microsecs -= 26;
  }
  sei(); // this turns them back on
}

void netOn(boolean b) {
  int i = 0;
  while(IRArruda::NET_ONOFF[i] != 0){
  	//ON e a OFF
    pulseIR(IRArruda::NET_ONOFF[i++]); //sinal positivo ON
    delayMicroseconds(IRArruda::NET_ONOFF[i++]); //sinal negativo
  }
}

void volumeUp() {
  int i = 0;
  while(IRArruda::NET_VOL_UP[i] != 0){
    pulseIR(IRArruda::NET_VOL_UP[i++]);delayMicroseconds(IRArruda::NET_VOL_UP[i++]);
  }
}

void volumeDown() {
  int i = 0;
  while(IRArruda::NET_VOL_DOWN[i] != 0){
    pulseIR(IRArruda::NET_VOL_DOWN[i++]);delayMicroseconds(IRArruda::NET_VOL_DOWN[i++]);
  }
}

void channelUp() {
  int i = 0;
  while(IRArruda::NET_CHANNEL_UP[i] != 0){
    pulseIR(IRArruda::NET_CHANNEL_UP[i++]);delayMicroseconds(IRArruda::NET_CHANNEL_UP[i++]);
  }
}

void channelDown() {//not working
  int i = 0;
  while(IRArruda::NET_CHANNEL_DOWN[i] != 0){
    pulseIR(IRArruda::NET_CHANNEL_DOWN[i++]);delayMicroseconds(IRArruda::NET_CHANNEL_DOWN[i++]);
  }
}

void tvOnOff() {//not working
  int i = 0;
  while(IRArruda::TV_ONOFF[i] != 0){
    pulseIR(IRArruda::TV_ONOFF[i++]);delayMicroseconds(IRArruda::TV_ONOFF[i++]);
  }
}

void tvVolUp() {//not working
  int i = 0;
  while(IRArruda::TV_VOL_UP[i] != 0){
    pulseIR(IRArruda::TV_VOL_UP[i++]);delayMicroseconds(IRArruda::TV_VOL_UP[i++]);
  }
}

void numeric0() {//not working
  int i = 0;
  while(IRArruda::NET_NUMERIC_0[i] != 0){
    pulseIR(IRArruda::NET_NUMERIC_0[i++]);delayMicroseconds(IRArruda::NET_NUMERIC_0[i++]);
  }
}

void numeric1() {//not working
  int i = 0;
  while(IRArruda::NET_NUMERIC_1[i] != 0){
    pulseIR(IRArruda::NET_NUMERIC_1[i++]);delayMicroseconds(IRArruda::NET_NUMERIC_1[i++]);
  }
}

void numeric2() {//not working
  int i = 0;
  while(IRArruda::NET_NUMERIC_2[i] != 0){
    pulseIR(IRArruda::NET_NUMERIC_2[i++]);delayMicroseconds(IRArruda::NET_NUMERIC_2[i++]);
  }
}

void numeric5() {//not working
  int i = 0;
  while(IRArruda::NET_NUMERIC_5[i] != 0){
    pulseIR(IRArruda::NET_NUMERIC_5[i++]);delayMicroseconds(IRArruda::NET_NUMERIC_5[i++]);
  }
}

void numeric6() {//not working
  int i = 0;
  while(IRArruda::NET_NUMERIC_6[i] != 0){
    pulseIR(IRArruda::NET_NUMERIC_6[i++]);delayMicroseconds(IRArruda::NET_NUMERIC_6[i++]);
  }
}
