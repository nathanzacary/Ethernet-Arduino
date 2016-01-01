// Server / Receiver / ETH1 / UNO1

#include "config.h"
#include <SPI.h>
#include <Ethernet.h>

int motrpm      = 0; // Motordrehwert
int motdirpin01 = 5; // Motordirection pin 1
int motdirpin02 = 7; // Motordirection pin 2
int motdir      = 2; // Motordirection
int calswpin1   = 0; // calibrateswitch connected to digital pin 0



EthernetServer server = EthernetServer(80);

void setup()
{  
  pinMode(calswpin1,    INPUT);
  pinMode(motdirpin01,  OUTPUT);
  pinMode(motdirpin02,  OUTPUT);
  digitalWrite(calswpin1, HIGH); // turn on pull resistor
  
  for (int i=0; i++; i<=sizeof(MOTORS)) {
    pinMode(MOTORS[i],  OUTPUT);
  }

  // Deactivate SD Card, See http://electronics.stackexchange.com/a/67214/3130
  pinMode(4,  OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(10, LOW);
  
  Serial.begin(serialspeed);
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
  EthernetClient client = server.available();
  
  if (client) {
    
    char    command_type;
    String  command;
    int     v_pos;
    String  m_tmp;
    int     m;
    String  v;
    
    command = client.readStringUntil('\n');
    command.toUpperCase();
    command.trim();

    command_type = command.charAt(0);
    switch (command_type) {
      
      // Motor Signal, zB. "A3v501" -> Motor 4 Wert 501
      case 1:
        v_pos   = command.indexOf("V");
        m_tmp   = command.substring(1, v_pos);
        m       = m_tmp.toInt();
        v       = command.substring(v_pos + 1);
        v       = v.toInt();
        motrpm  = v.toInt();
        Serial.println('Motor: '+m+' Value '+v);


        // Calulate Value for Motor Driver
        motdir = -1;
        if (motrpm > 512) {
          motdir    = 0;
          motrpm    = motrpm - 511;
        } else if (motrpm <= 512) {
          motdir    = 1;
          motrpm    = (motrpm - 511) * -1;
        }

        // Apply Motor Direction
        switch (motdir) {
          case 0:
            digitalWrite(motdirpin01, LOW);
            digitalWrite(motdirpin02, HIGH);
          break;
          case 1:
            digitalWrite(motdirpin01, HIGH);
            digitalWrite(motdirpin02, LOW);
          break;
          default:
            digitalWrite(motdirpin01, HIGH);
            digitalWrite(motdirpin02, HIGH);
          break;
        }

        // Apply Motor Speed
        motrpm = map(motrpm, 0, 520, 0, 245);
        analogWrite(MOTORS[m], motrpm);

        
        Serial.print("Motor RPM: ");
        Serial.print(motrpm);
        Serial.print(" Richtung: ");
        Serial.println(motdir);
      break;
      
      default:
        Serial.println('Command Type "'+command_type+'" ist nicht bekannt.');
      break;
    }
  }
}

