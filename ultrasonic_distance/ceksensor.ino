#define trigPin 34
#define echoPin 35
float duration, distance;

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
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float jarak = cek_sensor(trigPin, echoPin);
  delay(1000);
}
