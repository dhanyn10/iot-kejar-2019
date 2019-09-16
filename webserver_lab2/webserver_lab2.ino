#include <WiFi.h>

#define PORT 8080
#define LED_BUILTIN 2
const char *SSID = "Redmiddd";
const char *PASSWORD = "sssss222";

String header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>";
String tailer = "</body></html>";

WiFiServer server(PORT);
WiFiClient client;

bool blinking = false;
bool ledOn = false;

String s;
String cmd;

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Web Server Active: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop() {
  client = server.available();
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
        // response(cmd);
        if(cmd.equals(""))
        {
          Serial.println("HOMEPAGE");
        }
        else if(cmd.equals("blink"))
        {
          blinking = true;
          ledOn = false;
        }
        else if(cmd.equals("on"))
        {
          blinking = false;
          ledOn = true;
        }
        else if(cmd.equals("off"))
        {
          blinking = false;
          ledOn = false;
        }
        else
        {
          // response(s);
          // client.stop();
        }
        response(s);
        client.stop();
      }
      else
      {
        client.stop();  
      }
    }
  }
  else
  {
    //
  }
  if(blinking || ledOn)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }
  if(blinking || !ledOn)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}

void response(String konten)
{
  client.println(header);
  client.println("<p><a href='blink'>LED Blinking</a></p>");
  client.println("<p><a href='on'>LED on</a></p>");
  client.println("<p><a href='off'>LED OFF</a></p>");
//  client.println(konten);
  client.println(tailer);
}

String getCommand(String s)
{
  return(s.substring(5, s.indexOf(' ', 5)));
}
