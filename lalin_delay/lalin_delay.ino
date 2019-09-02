 //jalur 1
#define MERAH 27
#define KUNING 26
#define HIJAU 25

//jalur 2
#define MERAH_2 18
#define KUNING_2 19
#define HIJAU_2 21

//sensor jarak
#define trigPin 34
#define echoPin 35
float duration, distance, lalin_delay;

float cek_sensor(int out, int in)
{
  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, LOW);
  duration = pulseIn(in, HIGH);
  distance = (duration/29)/2;
  Serial.print("jarak : ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void setup() {
  //lalin
  Serial.begin(115200);
  pinMode(MERAH, OUTPUT);
  pinMode(KUNING, OUTPUT);
  pinMode(HIJAU, OUTPUT);

  pinMode(MERAH_2, OUTPUT);
  pinMode(KUNING_2, OUTPUT);
  pinMode(HIJAU_2, OUTPUT);

  //sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    float jarak = cek_sensor(trigPin, echoPin);
    if(jarak >= 5 && jarak <= 20)
    {
      lalin_delay = 7000;
    }
    else
    {
      lalin_delay = 3000;
    }
    
    digitalWrite(MERAH, HIGH);
    digitalWrite(HIJAU_2, HIGH);
    delay(lalin_delay);
    digitalWrite(MERAH, LOW);
    digitalWrite(KUNING, HIGH);
    delay(lalin_delay);
    digitalWrite(KUNING, LOW);
    digitalWrite(HIJAU, HIGH);
    
    digitalWrite(MERAH_2, HIGH);
    digitalWrite(HIJAU_2, LOW);
    delay(3000);
    digitalWrite(MERAH_2, LOW);
    digitalWrite(KUNING_2, HIGH);
    delay(3000);
    digitalWrite(KUNING_2, LOW);
    digitalWrite(HIJAU_2, HIGH);
    digitalWrite(HIJAU, LOW);
}
