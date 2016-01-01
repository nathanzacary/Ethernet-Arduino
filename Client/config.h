// Client / Sender / ETH0 / UNO0
byte mac0[]             = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip0[]              = {192, 168, 179, 0};
const byte JOYSTICKS[]  = {A2/*, A3, A4, A5*/}; // Analog Ports only! A0 and A1 can not be used with Ethernet shield!!!


// Server / Receiver / ETH1 / UNO1
byte mac1[]             = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC};
byte ip1[]              = {192, 168, 179, 1}; // Bei AVM, wenn die IPs im DHCP Bereich sind, werden sie nicht erkannt von AVM Hardware. 
const byte MOTORS[]     = {3/*, 5, 6, 9*/}; // PWM Ports only!


// Wifi Router
byte _dns[]     = {192, 168, 178, 1};
byte gateway[]  = {192, 168, 178, 1};
byte subnet[]   = {255, 255, 255, 0};


// Misc
int httpport    = 80;
int serialspeed = 9600;

// Helper
String ip_to_string(byte ip[4]) {
    return (ip[0] + String(".") + ip[1] + String(".") + ip[2] + String(".") + ip[3]);
}

String mac_to_string(byte mac[6]) {
  return (String(mac[0], HEX) + String(":") + String(mac[1], HEX) + String(":") + String(mac[2], HEX) + String(":") + String(mac[3], HEX) + String(":") + String(mac[4], HEX) + String(":") + String(mac[5], HEX));
}

// Additional information
/*
 * Note that because the W5100 and SD card share the SPI bus, 
 * only one can be active at a time. If you are using both peripherals 
 * in your program, this should be taken care of by the corresponding 
 * libraries. If you're not using one of the peripherals in your 
 * program, however, you'll need to explicitly deselect it. To do this 
 * with the SD card, set pin 4 as an output and write a high to it. 
 * For the W5100, set digital pin 10 as a high output. 
 * /
 */


