// Client / Sender / ETH0 / UNO0

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>


EthernetClient client;

String  manual_command = "";
String  command;
char    command_to_send[100];
int     i, j, v;


void setup() {

  for (j=0; j <= (sizeof(JOYSTICKS) - 1); j++) {
    pinMode(JOYSTICKS[i], INPUT);
  }

  // Deactivate SD Card, See http://electronics.stackexchange.com/a/67214/3130
  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(10, LOW);
  
  
  Serial.begin(serialspeed);
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
  // Manual Commands via Serial Console
  if (Serial.available()) {
    command = Serial.readString();
    command.trim();

    if (command != "") {
      Serial.println("****Manual Command \""+command+"\" ****");
      command += "\n";
      sendCommand(command);
    }
  }

  
  // Read Client sensors and send values to Server
  
  // 1. Joysticks
  for (j=0; j <= (sizeof(JOYSTICKS) - 1); j++) {
    v = analogRead(JOYSTICKS[j]);
    command = "A";
    command.concat(j);
    command.concat("v");
    command.concat(v);
    command.concat('\n');
    
    sendCommand(command);
  }


  // char c = client.read();
  // Serial.print("Server says: ");
  // Serial.println(c);

  delay(100);
}

void sendCommand(String command) {
  Serial.print("Sending: ");
  Serial.print(command);


  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnected/disconnecting...");
    client.flush();
    client.stop();
    client.connect(ip1, httpport);
    delay(500);
    
    // sendCommand(command); // Better use current command and not this one 
  }

  command.toCharArray(command_to_send, 100); // TODO append \n in any case

  if (client.connected()) {
    for (i = 0; i < strlen(command_to_send); i++) {
      client.print(command_to_send[i]); // TODO use println() here? With full command without for...
    }
  }
}




/*
calibrate = digitalRead(calswpin1);
if (calibrate == LOW){
  motrpm00    = analogRead(JOYSTICKS[j]);
  motrpm00cal = motrpm00 - 511;
  motrpm00    = motrpm00 - motrpm00cal;
} else{
  motrpm00    = analogRead(JOYSTICKS[j]);
  motrpm00    = motrpm00 - motrpm00cal;
}

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

