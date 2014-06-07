int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6;
int F = 7;
int G = 9;
int H = 10;

int a = 1;
int b = 1;
int c = 1;
int d = 1;
int e = 1;
int f = 1;
int g = 1;
int h = 1;



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
}

void loop() {
  char myChar;
  if(Serial.available() >  0){
    myChar = Serial.read();
      if(myChar == 'a'){
        if(a == 1)
          a = 0;
        else
          a = 1;
      }
      if(myChar == 'b'){
        if(b == 1)
          b = 0;
        else
          b = 1;
      }
      if(myChar == 'c'){
        if(c == 1)
          c = 0;
        else
          c = 1;
      }
      if(myChar == 'd'){
        if(d == 1)
          d = 0;
        else
          d = 1;
      }
      if(myChar == 'e'){
        if(e == 1)
          e = 0;
        else
          e = 1;
      }
      if(myChar == 'f'){
        if(f == 1)
          f = 0;
        else
          f = 1;
      }
      if(myChar == 'g'){
        if(g == 1)
          g = 0;
        else
          g = 1;
      }
      if(myChar == 'h'){
        if(h == 1)
          h = 0;
        else
          h = 1;
      }
    }
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
  digitalWrite(E, e);
  digitalWrite(F, f);
  digitalWrite(G, g);
  digitalWrite(H, h);
}
