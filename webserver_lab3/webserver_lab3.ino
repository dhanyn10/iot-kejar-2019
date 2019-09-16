#include <WiFi.h>

#define trigPin 34
#define echoPin 35
float duration, distance;

#define PORT 8080
#define LED_BUILTIN 2


const char *SSID = "Redmiddd";
const char *PASSWORD = "sssss222";

String header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
String tailer = "</body></html>";

WiFiServer server(PORT);
WiFiClient client;

long randomnumber;

String s;
String cmd;

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
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(SSID, PASSWORD);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Web Server Active: ");
  Serial.println(WiFi.localIP());
  server.begin();
  randomSeed(42);
}
void loop() {
  client = server.available();
  float jarak = cek_sensor(trigPin, echoPin);
//  Serial.println("tunggu client");
  if(client)
  {
//    Serial.print("dapat client");
    while(client.connected())
    {
      if(client.available())
      {
//        Serial.println("data bisa dibaca");
        s = client.readString();
        cmd = getCommand(s);
        if(cmd.equals(""))
        {
          refresh(0);
        }
        else if(cmd.equals("refresh?"))
        {
          refresh(jarak);
        }
        else
        {
          refresh(0);
          client.stop();
        }
        Serial.println(cmd);
        delay(100);
      }
      else
      {
        client.stop();  
      }
    }
  }
  else
  {
    Serial.println("no client");
  }
  delay(1000);
}

void refresh(int nilai)
{
  client.println(header);
  client.print("<html><head>");
  client.print("<title>Sensor</title>");
  client.print("<meta name='viewport' content='width=device-width,initial-scale=1.0'>");
  client.print("</head>");
  client.print("<body>");
  client.print("<h1>Data Sensor</h1>");
  client.printf("<p>Nilai data dari Sensor adalah: %d </p>", nilai);  
  client.print("<p><form action='/refresh'><input type='submit' value='Refresh'></p>");
  client.print("</body>");
  client.print("</html>");
}

String getCommand(String s)
{
  int i;
  i = s.indexOf(' ', 5);
  return(s.substring(5,i));
}
