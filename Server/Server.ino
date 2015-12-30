// Server / Receiver / ETH1 / UNO1

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>

String command;

EthernetServer server = EthernetServer(80);

void setup()
{  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  
  Ethernet.begin(mac1, ip1/*, gateway, subnet*/);
  delay(1000);
  server.begin();
  
  Serial.println("Server gestartet");
  Serial.println("warte auf ankommende Signale...");
}

void loop()
{
  delay(10);
  
  EthernetClient client = server.available();
  
  if (client) {
    command = client.readStringUntil('\n');
    Serial.print(command);
    Serial.println();
  }
}

