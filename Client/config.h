
// Client / Sender / ETH0 / UNO0
byte mac0[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip0[]      = { 192, 168, 188, 115 };
int a0          = A0; // Analog Port
int a1          = A1;
int a2          = A2;
int a3          = A3;

// Server / Receiver / ETH1 / UNO1
byte mac1[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };
byte ip1[]      = { 192, 168, 188, 116 };
int m0          = 3; // PWM Port
int m1          = 5;
int m2          = 6;
int m3          = 9;


// Wifi Router
byte gateway[]  = { 10, 0, 0, 1 };
byte subnet[]   = { 255, 255, 0, 0 };


// Misc
int httpport    = 80;
int serialspeed = 115200;

// Helper
String ip_to_string(byte ip[4]) {
    return (ip[0] + String(".") + ip[1] + String(".") + ip[2] + String(".") + ip[3]);
}

String mac_to_string(byte mac[6]) {
  return (String(mac[0], HEX) + String(":") + String(mac[1], HEX) + String(":") + String(mac[2], HEX) + String(":") + String(mac[3], HEX) + String(":") + String(mac[4], HEX) + String(":") + String(mac[5], HEX));
}


