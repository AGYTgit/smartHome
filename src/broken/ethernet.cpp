// #include <Arduino.h>
// #include <Wire.h>
// #include <SPI.h>
// #include <Ethernet.h>

// byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// IPAddress ip(192, 168, 0, 104);
// IPAddress myDns(192, 168, 0, 1);
// IPAddress gateway(192, 168, 0, 1);
// IPAddress subnet(255, 255, 255, 0);

// // SMTP server details for SendGrid
// const char* smtpServer = "smtp.sendgrid.net";
// int smtpPort = 587;  // Port for TLS

// // SendGrid credentials
// const char* username = "apikey";  // The literal "apikey"
// const char* apiKey = "";

// EthernetClient client;

// void waitForResponse() {
//   while (!client.available()) {
//     delay(100);
//   }
//   while (client.available()) {
//     char c = client.read();
//     Serial.print(c);
//   }
// }

// // Function to base64 encode strings (needed for SMTP authentication)
// String encodeBase64(const char* input) {
//   const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//   String output = "";
//   int i = 0, len = strlen(input);
//   unsigned char char_array_3[3], char_array_4[4];

//   while (len--) {
//     char_array_3[i++] = *(input++);
//     if (i == 3) {
//       char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//       char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//       char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//       char_array_4[3] = char_array_3[2] & 0x3f;

//       for (i = 0; i < 4; i++) {
//         output += base64_chars[char_array_4[i]];
//       }
//       i = 0;
//     }
//   }

//   if (i) {
//     for (int j = i; j < 3; j++) {
//       char_array_3[j] = '\0';
//     }
//     char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//     char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//     char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

//     for (int j = 0; (j < i + 1); j++) {
//       output += base64_chars[char_array_4[j]];
//     }
//     while ((i++ < 3)) {
//       output += '=';
//     }
//   }
//   return output;
// }

// void sendEmail() {
//     if (client.connected()) {
//       // Send the EHLO command
//       client.println("EHLO arduino");
//       waitForResponse();
  
//       // Authenticate with SendGrid using the API key
//       client.println("AUTH LOGIN");
//       waitForResponse();
//       client.println(encodeBase64(username));  // Send the encoded username ("apikey")
//       waitForResponse();
//       client.println(encodeBase64(apiKey));  // Send the encoded API key (password)
//       waitForResponse();
  
//       // Specify the sender and recipient
//       client.println("MAIL FROM:<your_email@yourdomain.com>");
//       waitForResponse();
//       client.println("RCPT TO:<recipient_email@domain.com>");
//       waitForResponse();
  
//       // Start the email content
//       client.println("DATA");
//       waitForResponse();
  
//       // Email headers
//       client.println("From: Your Name <your_email@yourdomain.com>");
//       client.println("To: Recipient <recipient_email@domain.com>");
//       client.println("Subject: Test email from Arduino using SendGrid");
//       client.println();
  
//       // Email body
//       client.println("Hello, this is a test email sent via SendGrid from my Arduino.");
      
//       // End the email
//       client.println(".");
//       waitForResponse();
  
//       // Close the connection
//       client.println("QUIT");
//       waitForResponse();
  
//       Serial.println("Email sent successfully!");
//     }
//   }

// void setup() {
//     Serial.begin(115200);

//     // Start Ethernet connection
//     if (Ethernet.begin(mac) == 0) {
//         Ethernet.begin(mac, ip, myDns, gateway, subnet);
//     }

//     Serial.println("Trying to connect to SendGrid SMTP server...");

//     if (client.connect(smtpServer, smtpPort)) {
//         Serial.println("Connected to SendGrid SMTP server");
//         sendEmail();
//     } else {
//         Serial.println("Failed to connect to SMTP server");
//     }
// }

// void loop() {
//     // Nothing to do here
// }