// Su altı manyetik sensör pin bağlantıları
const int magnetSensor1 = 2;
const int magnetSensor2 = 3;
const int magnetSensor3 = 4;
const int magnetSensor4 = 5;
const int magnetSensor5 = 6;
const int magnetSensor6 = 7;

// Motor kontrol pin bağlantıları
const int motor1Pin1 = 8;
const int motor1Pin2 = 9;
const int motor2Pin1 = 10;
const int motor2Pin2 = 11;
const int motor3Pin1 = 12;
const int motor3Pin2 = 13;
const int motor4Pin1 = A0;
const int motor4Pin2 = A1;
const int motor5Pin1 = A2;
const int motor5Pin2 = A3;
const int motor6Pin1 = A4;
const int motor6Pin2 = A5;

// Dönme hareketi için sabitler
const int magnetThreshold = 500;  // Dönme hareketinin algılanması için manyetik sensör eşik değeri

void setup() {
  // Manyetik sensör pinlerini giriş olarak ayarlama
  pinMode(magnetSensor1, INPUT);
  pinMode(magnetSensor2, INPUT);
  pinMode(magnetSensor3, INPUT);
  pinMode(magnetSensor4, INPUT);
  pinMode(magnetSensor5, INPUT);
  pinMode(magnetSensor6, INPUT);

  // Motor kontrol pinlerini çıkış olarak ayarlama
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
  pinMode(motor5Pin1, OUTPUT);
  pinMode(motor5Pin2, OUTPUT);
  pinMode(motor6Pin1, OUTPUT);
  pinMode(motor6Pin2, OUTPUT);

  // Seri haberleşme başlatma
  Serial.begin(9600);
}

void loop() {
  // Manyetik sensör verilerini okuma
  int magnet1 = analogRead(magnetSensor1);
  int magnet2 = analogRead(magnetSensor2);
  int magnet3 = analogRead(magnetSensor3);
  int magnet4 = analogRead(magnetSensor4);
  int magnet5 = analogRead(magnetSensor5);
  int magnet6 = analogRead(magnetSensor6);

  // Hareketin algılanması
  if (magnet1 > magnetThreshold || magnet2 > magnetThreshold ||
      magnet3 > magnetThreshold || magnet4 > magnetThreshold ||
      magnet5 > magnetThreshold || magnet6 > magnetThreshold) {
    rotateClockwise();  // Saat yönünde dönme hareketi
  } else {
    stopMoving();  // Durma
  }

  // Verilerin seri port üzerinden gönderilmesi
  Serial.print("Magnet 1: ");
  Serial.print(magnet1);
  Serial.print(", Magnet 2: ");
  Serial.print(magnet2);
  Serial.print(", Magnet 3: ");
  Serial.print(magnet3);
  Serial.print(", Magnet 4: ");
  Serial.print(magnet4);
  Serial.print(", Magnet 5: ");
  Serial.print(magnet5);
  Serial.print(", Magnet 6: ");
  Serial.println(magnet6);

  // Kısa bir bekleme süresi
  delay(100);
}

// Saat yönünde dönme fonksiyonu
void rotateClockwise() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
  digitalWrite(motor5Pin1, HIGH);
  digitalWrite(motor5Pin2, LOW);
  digitalWrite(motor6Pin1, HIGH);
  digitalWrite(motor6Pin2, LOW);
}

// Durma fonksiyonu
void stopMoving() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  digitalWrite(motor5Pin1, LOW);
  digitalWrite(motor5Pin2, LOW);
  digitalWrite(motor6Pin1, LOW);
  digitalWrite(motor6Pin2, LOW);
}
