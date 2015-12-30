// Client / Sender / ETH0 / UNO0

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
  Ethernet.begin(mac0, ip0, gateway, subnet);
  server.begin();
}

void loop()
{
  // if an incoming client connects, there will be bytes available to read:
  char incoming[100];
  EthernetClient client = server.available();
  if (client == true) {
    // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    int ii = 0;

    while ((c = client.read()) != '\n')
    {
      incoming[ii++] = c;
      Serial.print(c);
    }
    // the variable incoming[] now contains the most recent value sent
    // so you can do something with it
  }
}

