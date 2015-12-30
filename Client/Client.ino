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

const byte INPUTS[] = {A2, A3, A4, A5};

void setup() {
  pinMode(INPUTS[0], INPUT);
  pinMode(INPUTS[1], INPUT);
  pinMode(INPUTS[2], INPUT);
  pinMode(INPUTS[3], INPUT);

  // Deactivate SD Card
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Client starts...");



  Ethernet.begin(mac0, ip0/*, gateway, subnet*/);
  delay(200);

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
  delay(500);
  
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

    // Programm Logik hier
    // Read value 1, 2, 3, 4
    // Send them

    for (j=0; j <= 3; j++) {

      int v = analogRead(INPUTS[j]);
      
      command = "A";
      command.concat(j);
      command.concat("v");
      command.concat(v);
      command.concat('\n');
      
      Serial.print(command);
      strcpy(myVar, command.c_str());
      
      sendCommand(myVar);
    }
    
    
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
    client.stop();
    client.connect(ip1, httpport);
    delay(500);
  }
}

