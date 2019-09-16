
#include <WiFi.h>
const char *SSID = "Redmiddd";
const char *PASSWORD = "sssss222";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  connectToHotSpot();
}
void connectToHotSpot() {
  String mac_addr;
  WiFi.begin( SSID, PASSWORD );
  Serial.print("Trying to establish connection to WiFi Router");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
  mac_addr = WiFi.macAddress();
  Serial.println(mac_addr);
}
void loop() {
  // nothing here
  if(WiFi.status() != WL_CONNECTED)
  {
    connectToHotSpot();
  }
}
