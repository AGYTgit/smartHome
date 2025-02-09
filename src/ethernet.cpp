// #include <Arduino.h>
// #include <Wire.h>
// #include <SPI.h>
// #include <Ethernet.h>

// byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  // Unique MAC address
// IPAddress ip(192, 168, 0, 104); // Static IP for the device
// IPAddress myDns(192, 168, 0, 1);  // DNS server (usually your router)
// IPAddress gateway(192, 168, 0, 1);  // Default gateway (router)
// IPAddress subnet(255, 255, 255, 0);  // Subnet mask

// EthernetServer server(23);  // Server listening on port 23 (Telnet)
// bool gotAMessage = false;  // Flag for whether we got a message from the client yet

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) {
//     ; // Wait for serial port to connect. Needed for native USB port only
//   }

//   // Start the Ethernet connection:
//   Serial.println("Trying to get an IP address using DHCP");
//   if (Ethernet.begin(mac) == 0) {
//     Serial.println("Failed to configure Ethernet using DHCP");
//     // If DHCP fails, use static IP
//     Serial.println("Using static IP address");
//     Ethernet.begin(mac, ip, myDns, gateway, subnet);
//   }
  
//   // Print the local IP address:
//   Serial.print("My IP address: ");
//   Serial.println(Ethernet.localIP());
  
//   // Start the server:
//   server.begin();
// }

// void loop() {
//   // Wait for a new client:
//   EthernetClient client = server.available();
  
//   // When the client sends the first byte, say hello:
//   if (client) {
//     if (!gotAMessage) {
//       Serial.println("We have a new client");
//       client.println("Hello, client!");
//       gotAMessage = true;
//     }

//     // Read the incoming bytes from the client:
//     char thisChar = client.read();
    
//     // Echo the bytes back to the client:
//     server.write(thisChar);
    
//     // Echo the bytes to the server as well:
//     Serial.print(thisChar);
    
//     // Maintain the Ethernet connection:
//     Ethernet.maintain();
//   }
// }
