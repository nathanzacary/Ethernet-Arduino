// Server / Receiver / ETH1 / UNO1

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>

String command;

int motrpm00      = 0; // Motordrehwert
int mot00         = 3; // Motor connected to digital pin 3
int motdirpin01   = 5; // Motordirection pin 1
int motdirpin02   = 7; // Motordirection pin 2
int motdir0       = 2; // Motordirection
int fivevpin      = 8;
int calswpin1     = 0; // calibrateswitch connected to digital pin 0

EthernetServer server = EthernetServer(80);

void setup()
{  
  pinMode(calswpin1,    INPUT);
  pinMode(motdirpin01,  OUTPUT);
  pinMode(motdirpin02,  OUTPUT);
  pinMode(mot00,        OUTPUT);
  digitalWrite(calswpin1, HIGH);      // turn on pull resistor

  // Deactivate SD Card, See http://electronics.stackexchange.com/a/67214/3130
  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(10, LOW);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Ethernet.begin(mac1, ip1, _dns/*, gateway, subnet*/);
  delay(1000);
  Serial.println(Ethernet.localIP());
  
  server.begin();
  
  Serial.println("Server gestartet");
  Serial.println("warte auf ankommende Signale...");
}

void loop()
{
  // delay(10);
  
  EthernetClient client = server.available();
  
  if (client) {
    command = client.readStringUntil('\n');
    command.toUpperCase();
    command.trim();
    // Serial.print(command);
    // Serial.println();

    // Motor Signal, zB. "A3v501" -> Motor 4 Wert 501
    if (command.startsWith("A")) {
      int vPos = command.indexOf("V");
      String m = command.substring(1, vPos);
      String v = command.substring(vPos+1);
      v = v.toInt();
      Serial.println("Motor: "+m+" setze "+v);
      motrpm00 = v.toInt();


      // Calulate Value for Motor Driver
      if (motrpm00 > 512) {
        digitalWrite(motdirpin01, LOW);
        digitalWrite(motdirpin02, HIGH);
        motdir0   = 0;
        motrpm00  = motrpm00 - 511;
      } else if (motrpm00 <= 512) {
        digitalWrite(motdirpin01, HIGH);
        digitalWrite(motdirpin02, LOW);
        motdir0   = 1;
        motrpm00  = (motrpm00 - 511) * -1;
      } else {
        digitalWrite(motdirpin01, HIGH);
        digitalWrite(motdirpin02, HIGH);
      }
      
      motrpm00 = map(motrpm00, 0, 520, 0, 245);
      analogWrite(mot00, motrpm00);
      
      Serial.print("Motor RPM: ");
      Serial.print(motrpm00);
      Serial.print(" Richtung: ");
      Serial.println(motdir0);
      
      
    } else {
      Serial.println("\""+command+"\" ist kein Motor Signal");
    }
  }
}

