// http://stackoverflow.com/questions/19920796/how-to-have-2-arduinos-communicate-a-variable-over-ethernet

#include <SPI.h>
#include <Ethernet.h>
// inspired by/copied from http://arduino.cc/en/Tutorial/TelnetClient

// Enter a MAC address and IP address for your controller below:
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xDE, 0xEF, 0xFE, 0xED };
// IPAddress ip(192,168,1,176);  // this is the data source card IP address
IPAddress ip(192, 168, 188, 116); //Client = COM16 daher ip-Adresse: 192.168.188.116

// the IP address of the server you're connecting to:
IPAddress server(192, 168, 188, 115);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 23 is default for telnet;
EthernetClient client;
int port = 80;   // telnet default port

char myVar[100]; // contains string with variable to transmit

void setup() {
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, port)) {
    Serial.println("connected");
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  // the server code above doesn't send anythingâ€¦
  // but if it did, this is where you would echo it
  int ii;
  if (client.available()) {
    char c = client.read();
    Serial.print("***Server says:***\n");
    Serial.print(c);
  }

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

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    while (true);
  }
  // add appropriate delay here before sending next data element
}

