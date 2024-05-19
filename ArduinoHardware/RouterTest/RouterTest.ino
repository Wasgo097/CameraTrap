#include <ESP8266WiFi.h>
const char* ssid = "ssid";
const char* password = "password";
IPAddress local_IP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() 
{
  WiFi.mode(WIFI_AP); // Set ESP8266 to AP mode
  // Configure the SoftAP network settings
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.begin(9600);
  Serial.println("Wi-Fi Router Configured!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() 
{
}
