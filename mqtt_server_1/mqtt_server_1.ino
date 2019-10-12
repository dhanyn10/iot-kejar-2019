#include <PubSubClient.h>
#include <WiFi.h>

#define trigPin 34
#define echoPin 35
float duration, distance;

const char *SSID = "Redmiddd";
const char *PASSWORD = "sssss222";
float value;
char str_value[8];


const char* mqttServer = "soldier.cloudmqtt.com";
const int mqttPort    = 14551;
const char* mqttUser  = "qykihtsd";
const char* mqttPassword  = "49DuLxHEYbcI";

WiFiClient espClient;
PubSubClient client(espClient);

void connectToMqttCloud()
{
  client.setServer(mqttServer, mqttPort);
  while(!client.connected())
  {
    Serial.println("Mencoba koneksi dengan broker MQTT");
    if(client.connect("ESP32Client", mqttUser, mqttPassword))
    {
      Serial.println("tersambung dengan mqtt");
    }
    else
    {
      Serial.print("error");
      delay(1000);
    }
  }
}


float cek_sensor(int out, int in)
{
  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, LOW);
  duration = pulseIn(in, HIGH);
  distance = (duration/2)/29.1;
  Serial.print("jarak : ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void setup() {
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  connectToMqttCloud();
  if(WiFi.status() != WL_CONNECTED)
  {
    connectToHotSpot();
  }
  float jarak = cek_sensor(trigPin, echoPin);
  Serial.println(value);
  sprintf(str_value, "%04f", jarak);
  client.publish("INIX", str_value);
  delay(5000);
}
