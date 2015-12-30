// Server / Receiver / ETH1 / UNO1

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>

char c;

EthernetServer server = EthernetServer(80);

void setup()
{
  Serial.begin(115200);
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

  delay(50);
  // if an incoming client connects, there will be bytes available to read:
  char incoming[100];
  EthernetClient client = server.available();
  if (client) {

    // client.println(200);
    // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    int ii = 0;

    while ((c = client.read()) != '\n')
    {
      incoming[ii++] = c;
      Serial.print(c);
    }

    Serial.print("Variable incoming[] enthält nun '");
    Serial.print(incoming);
    Serial.println("'.");
    
    // the variable incoming[] now contains the most recent value sent
    // so you can do something with it
  } else {
    Serial.println("client != true");
  }
}

