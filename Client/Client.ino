// Client / Sender / ETH0 / UNO0

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>


EthernetClient client;


char myVar[100]; // contains string with variable to transmit
String debug = "";
String command;
int ii;
int j;

// int a0         = A0;      //Poti connected to pin A0
int motrpm00      = 0; // Motordrehwert
int mot00         = 3;    // Motor connected to digital pin 3
int motdirpin01   = 4; //Motordirection pin 1
int motdirpin02   = 7; //Motordirection pin 2
int motdir0       = 2; //Motordirection
int fivevpin      = 8;
int calswpin1     = 0; // calibrateswitch connected to digital pin 0
int calibrate     = HIGH;
int motrpm00cal   = 0;
//boolean calibrate = false;

int v;










void setup() {
  pinMode(INPUTS[0], INPUT);
  pinMode(INPUTS[1], INPUT);
  pinMode(INPUTS[2], INPUT);
  pinMode(INPUTS[3], INPUT);

  // Deactivate SD Card, See http://electronics.stackexchange.com/a/67214/3130
  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(10, LOW);

  pinMode(calswpin1,    INPUT);
  pinMode(motdirpin01,  OUTPUT);
  pinMode(motdirpin02,  OUTPUT);
  pinMode(mot00,        OUTPUT);
  digitalWrite(calswpin1, HIGH);      // turn on pull resistor

  
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Client starts...");



  Ethernet.begin(mac0, ip0, _dns, gateway, subnet);
  delay(1000);

  Serial.println(Ethernet.localIP());

  Serial.println("Try to connect to "+ip_to_string(ip1)+":"+httpport+" MAC "+mac_to_string(mac1));

  if (client.connect(ip1, httpport)) {
    Serial.println("connected");
  } else {
    Serial.println("connection failed");
    Serial.println(client.status(), DEC);
    Serial.println("Please reset \"Client\" Arduino Board until connection is valid.");
  }
}

void loop()
{
  delay(100);
  
  // Debugging (Commands via Serial Console)
  if (Serial.available()) {
      debug = Serial.readString();
      debug.trim();
  }
  if (debug != "") {
    Serial.println("****Command \""+debug+"\" ****");
  }

  // char c = client.read();
  // Serial.print("***Server says:***\n");
  // Serial.print(c);
  


    
  if (debug == "") {

    // Only 1 Motor: use "j <= 0"
    
    for (j=0; j <= (sizeof(INPUTS) - 1); j++) {
      /*
      calibrate = digitalRead(calswpin1);
      
      if (calibrate == LOW){
        motrpm00    = analogRead(INPUTS[j]);
        motrpm00cal = motrpm00 - 511;
        motrpm00    = motrpm00 - motrpm00cal;
      } else{
        motrpm00    = analogRead(INPUTS[j]);
        motrpm00    = motrpm00 - motrpm00cal;
      }
      */

      // Wert lesen
      v = analogRead(INPUTS[j]);
      
      command = "A";
      command.concat(j);
      command.concat("v");
      command.concat(v);
      command.concat('\n');
      
      Serial.print(command);
      strcpy(myVar, command.c_str());
      
      sendCommand(myVar);
    }

/*
    // Calibrate?
    v = digitalRead(calswpin1);
    if (v == LOW) {
      command = "C";
      command.concat(j);
      command.concat("v");
      command.concat(v);
      command.concat('\n');
      Serial.print(command);
      strcpy(myVar, command.c_str());
      sendCommand(myVar);
    }
*/
    
    // strcpy(myVar, "123.456\n");
  } else {
    debug += "\n";
    debug.toCharArray(myVar, 100);
    sendCommand(myVar);
  }

 


  
  j = 0;
  debug = "";
}

void sendCommand(char myVar[100]) {
  Serial.print("sending: ");
  Serial.println(myVar);
  
  for (ii = 0; ii < strlen(myVar); ii++) {
    if (client.connected()) { // wieso??? wenn disconnected werden Zeichen übersprungen!
      client.print(myVar[ii]);
    }
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnected/disconnecting...");
    client.flush();
    client.stop();
    client.connect(ip1, httpport);
    delay(500);
  }
}

