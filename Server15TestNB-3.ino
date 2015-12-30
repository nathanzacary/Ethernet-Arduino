//http://stackoverflow.com/questions/19920796/how-to-have-2-arduinos-communicate-a-variable-over-ethernet

#include <SPI.h>
#include <Ethernet.h>

// network configuration.  
// gateway and subnet are optional.

 // the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  

//the IP address for the shield:
byte ip[] = { 192, 168, 188, 115 };    

// the router's gateway address:
byte gateway[] = { 10, 0, 0, 1 };

// the subnet:
byte subnet[] = { 255, 255, 0, 0 };

char c;

// telnet defaults to port 23
EthernetServer server = EthernetServer(80);

void setup()
{

   // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // initialize the ethernet device
 // Ethernet.begin(mac, ip, gateway, subnet);
Ethernet.begin(mac, ip);
  // start listening for clients
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
