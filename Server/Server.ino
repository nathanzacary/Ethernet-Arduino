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
    command.toUpperCase();
    // Serial.print(command);
    // Serial.println();

    // Motor Signal, zB. "A3v501" -> Motor 4 Wert 501
    if (command.startsWith("A")) {
      int vPos = command.indexOf("V");
      String m = command.substring(1, vPos);
      String v = command.substring(vPos+1);
      v = v.toInt();
      Serial.println("Motor: "+m+" setze "+v.toInt());
    } else {
      Serial.println("\""+command+"\" ist kein Motor Signal");
    }







    
  }
}

