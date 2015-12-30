// Client / Sender / ETH0 / UNO0

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>


EthernetClient client;


char myVar[100]; // contains string with variable to transmit

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Client starts...");

  Ethernet.begin(mac0, ip0/*, gateway, subnet*/);
  delay(1000);
  
  Serial.println("Try to connect to "+ip_to_string(ip1)+":"+httpport+" MAC "+mac_to_string(mac1));

  if (client.connect(ip1, httpport)) {
    Serial.println("connected");
  } else {
    Serial.println("connection failed");
    Serial.println(client.status(), DEC);
    Serial.println("Please reset \"Client\" Arduino Board until connection is good.");
  }
  // }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  // the server code above doesn't send anythingâ€¦
  // but if it did, this is where you would echo it
  int ii;

  delay(250);
  
  // char c = client.read();
  // Serial.print("***Server says:***\n");
  // Serial.print(c);

  // assume your variable myVar will have a valid string in it...
  strcpy(myVar, "123.456\n");
  // tell the serial port what you are sending:
  Serial.print("sending variable: ");
  Serial.print(myVar);
  for (ii = 0; ii < strlen(myVar); ii++) {
    if (client.connected()) {
      client.print(myVar[ii]);
    }
  }
  //client.print("\n");
  //client.println();
  //client.stop();

  
  // if the server's disconnected, stop the client:
 
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    client.connect(ip1, httpport);
    delay(500);
    // do nothing:
    // while (true);
  }
  
  // add appropriate delay here before sending next data element
}

