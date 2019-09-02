 //jalur 1
#define MERAH 27
#define KUNING 26
#define HIJAU 25

//jalur 2
#define MERAH_2 18
#define KUNING_2 19
#define HIJAU_2 21

void setup() {
  Serial.begin(115200);
  pinMode(MERAH, OUTPUT);
  pinMode(KUNING, OUTPUT);
  pinMode(HIJAU, OUTPUT);

  pinMode(MERAH_2, OUTPUT);
  pinMode(KUNING_2, OUTPUT);
  pinMode(HIJAU_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(MERAH, HIGH);
    digitalWrite(HIJAU_2, HIGH);
    delay(1000);
    digitalWrite(MERAH, LOW);
    digitalWrite(KUNING, HIGH);
    delay(1000);
    digitalWrite(KUNING, LOW);
    digitalWrite(HIJAU, HIGH);
    digitalWrite(MERAH_2, HIGH);
    digitalWrite(HIJAU_2, LOW);
    delay(1000);
    digitalWrite(MERAH_2, LOW);
    digitalWrite(KUNING_2, HIGH);
    delay(1000);
    digitalWrite(KUNING_2, LOW);
    digitalWrite(HIJAU_2, HIGH);
    digitalWrite(HIJAU, LOW);
}
