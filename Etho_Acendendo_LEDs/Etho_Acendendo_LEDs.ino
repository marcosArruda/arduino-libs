/*--------------------------------------------------------------
  Program:      Web Server do Marcos

  Description:  Web Server Mostrando os pinos e acesso direto
                  aos LEDs.
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe and Marcos Arruda
                - SD card examples by David A. Mellis and
                  Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet
                - SD Card library documentation:
                  http://arduino.cc/en/Reference/SD

  Date:         4 April 2013
  Modified:     19 June 2013 - removed use of the String class
                16 September 2013 - removed bunch and added bunch.
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <VirtualWire.h>
#include <LiquidCrystal.h>
#include <SD.h>
// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   60
#define txPin 32

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
File webFile;               // the web page file on the SD card
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer
boolean LED_state[6] = {0}; // stores the states of the LEDs
LiquidCrystal lcd(44, 45, 46, 47, 48, 49);


//===============================
// Pinagem dos LEDs
//===============================
int RED_BIG = 38;
int YELLOW_BIG = 39;
int GREEN_BIG = 40;
int RED_SMALL = 41;
int YELLOW_SMALL = 42;
int GREEN_SMALL = 43;

String LED_PREFIX = "@L";

void setup(){
    // disable Ethernet chip
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    
    Serial.begin(9600);// for debugging
    
    // initialize SD card
    if(initSDCard() == -1){
        return;
    }
    initRF();
    initLEDs();
    initEthernet();
    initLCD();
}

void loop(){
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        answerClient(client);
    }
}

void askPassword(EthernetClient client){
    //client.println("HTTP/1.1 401 Unauthorized");
    //client.println("WWW-Authenticate: Basic realm=\"website\"");

    //response
    //if (strContains(HTTP_req, "Authorization: Basic ")) {
    //Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==

    /*
        I generally use strstr() function:
        char buffer[]="+CBC: 0,99,4190" ; // this is a return string by GSM modem  0,charge level, millivolt
        char *ptr;  //temp pointer variable for pointer artihmetic
        char *fieldPtr; //temp pointer  variable for pointer artihmetic
        :
        :
        :
        :
        ptr=strstr(buffer,"+CBC:"); // if substring found in buffer it return address ofstart character of matched string
                              // if not matched it returned NULL
        if(ptr!=NULL)
        {
           ptr=strstr(ptr,",");
           Serial.println(ptr);         // will print :",99,4190"
                               // you can use pointer arithmetic to get the field
           while(ptr!=NULL)
           {
            ptr++;
            fieldPtr=ptr;
            ptr=strstr(ptr,",");
            *ptr='\0';
            Serial.println(fieldPtr);
           }
        }
    */
}

void answerClient(EthernetClient client){
    boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // limit the size of the stored received HTTP request
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    // remainder of header follows below, depending on if
                    // web page or XML page is requested
                    // Ajax request - send XML file
                    if (strContains(HTTP_req, "ajax_inputs")) {
                        // send rest of HTTP header
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();
                        updateLEDs();
                        // send XML file containing input states
                        sendXMLResponse(client);
                    }
                    else {  // web page request
                        // send rest of HTTP header
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send web page
                        webFile = SD.open("index.htm");        // open web page file
                        if (webFile) {
                            while(webFile.available()) {
                                client.write(webFile.read()); // send web page to client
                            }
                            webFile.close();
                        }
                    }
                    // display received HTTP request on serial port
                    Serial.print(HTTP_req);
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    strClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
}

// checks if received HTTP request is switching on/off LEDs
// also saves the state of the LEDs
void updateLEDs(void){
    // RED_BIG
    if (strContains(HTTP_req, "RED_BIG=1")) {LED_state[0] = 1;digitalWrite(RED_BIG, HIGH);}
    else if (strContains(HTTP_req, "RED_BIG=0")) {LED_state[0] = 0;digitalWrite(RED_BIG, LOW);}
    
    // YELLOW_BIG
    if (strContains(HTTP_req, "YELLOW_BIG=1")) {LED_state[1] = 1;digitalWrite(YELLOW_BIG, HIGH);}
    else if (strContains(HTTP_req, "YELLOW_BIG=0")) {LED_state[1] = 0;digitalWrite(YELLOW_BIG, LOW);}

    // GREEN_BIG
    if (strContains(HTTP_req, "GREEN_BIG=1")) {LED_state[2] = 1;digitalWrite(GREEN_BIG, HIGH);}
    else if (strContains(HTTP_req, "GREEN_BIG=0")) {LED_state[2] = 0;digitalWrite(GREEN_BIG, LOW);}


    // RED_SMALL
    if (strContains(HTTP_req, "RED_SMALL=1")) {LED_state[3] = 1;digitalWrite(RED_SMALL, HIGH);}
    else if (strContains(HTTP_req, "RED_SMALL=0")) {LED_state[3] = 0;digitalWrite(RED_SMALL, LOW);}
    
    // YELLOW_SMALL
    if (strContains(HTTP_req, "YELLOW_SMALL=1")) {LED_state[4] = 1;digitalWrite(YELLOW_SMALL, HIGH);}
    else if (strContains(HTTP_req, "YELLOW_SMALL=0")) {LED_state[4] = 0;digitalWrite(YELLOW_SMALL, LOW);}

    // GREEN_SMALL
    if (strContains(HTTP_req, "GREEN_SMALL=1")) {LED_state[5] = 1;digitalWrite(GREEN_SMALL, HIGH);}
    else if (strContains(HTTP_req, "GREEN_SMALL=0")) {LED_state[5] = 0;digitalWrite(GREEN_SMALL, LOW);}
}

// send the XML file with analog values, switch status
//  and LED status
//LED ORDER:
    //bigs fists: RED, GREEN, YELLOW, red, green, yellow
void sendXMLResponse(EthernetClient cl)
{
    int analog_val;            // stores value read from analog inputs
    int count;                 // used by 'for' loops
    
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");
    // read analog inputs
    for (count = 2; count <= 5; count++) { // A2 to A5
        analog_val = analogRead(count);
        cl.print("<analog>");
        cl.print(analog_val);
        cl.println("</analog>");
    }
    
    // checkbox LED states
    // RED_BIG
    cl.print("<RED_BIG>");if (LED_state[0]){cl.print("checked");}else{cl.print("unchecked");}cl.println("</RED_BIG>");
    // YELLOW_BIG
    cl.print("<YELLOW_BIG>");if (LED_state[1]){cl.print("checked");}else{cl.print("unchecked");}cl.println("</YELLOW_BIG>");
    // GREEN_BIG
    cl.print("<GREEN_BIG>");if (LED_state[2]){cl.print("checked");}else{cl.print("unchecked");}cl.println("</GREEN_BIG>");


    // button LED states
    // RED_SMALL
    cl.print("<RED_SMALL>");if(LED_state[3]){cl.print("on");}else{cl.print("off");}cl.println("</RED_SMALL>");
    // YELLOW_SMALL
    cl.print("<YELLOW_SMALL>");if(LED_state[4]){cl.print("on");}else{cl.print("off");}cl.println("</YELLOW_SMALL>");
    // GREEN_SMALL
    cl.print("<GREEN_SMALL>");if(LED_state[5]){cl.print("on");}else{cl.print("off");}cl.println("</GREEN_SMALL>");

    cl.print("</inputs>");
}

// sets every element of str to 0 (clears array)
void strClear(char *str, char length){
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char strContains(char *str, char *sfind){
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }else {
            found = 0;
        }
        index++;
    }
    return 0;
}

void initEthernet(){
    Ethernet.begin(mac, ip); // initialize Ethernet device
    server.begin();// start to listen for clients
}

void initLEDs(){
    pinMode(RED_BIG, OUTPUT);
    pinMode(YELLOW_BIG, OUTPUT);
    pinMode(GREEN_BIG, OUTPUT);
    pinMode(RED_SMALL, OUTPUT);
    pinMode(YELLOW_SMALL, OUTPUT);
    pinMode(GREEN_SMALL, OUTPUT);
}

void initRF(){
    vw_set_ptt_inverted(true);// Required by the RF module
    vw_setup(2000);// bps connection speed
    vw_set_tx_pin(txPin);// Arduino pin to connect the transmitter data pin
}

void initLCD(){
    lcd.begin(16, 2);
    lcd.print("Rede Online");
    lcd.setCursor(0, 1);
    lcd.print("IP:192.168.1.177");
}

int initSDCard(){
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return -1;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return -1;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
    return 0;
}

void sendData(String m){
   char msg[50];
   m.toCharArray(msg, 50);
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();
   //delay(delayTime);
}

