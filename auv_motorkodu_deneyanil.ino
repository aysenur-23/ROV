// Ping sensörünün bağlantı pinleri
const int TRIGGER_PIN = 9;
const int ECHO_PIN = 10;

// Motorların bağlantı pinleri
const int UP_DOWN_PIN = 5;
const int LEFT_RIGHT_PIN = 6;
const int FORWARD_BACKWARD_PIN = 7;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(UP_DOWN_PIN, OUTPUT);
  pinMode(LEFT_RIGHT_PIN, OUTPUT);
  pinMode(FORWARD_BACKWARD_PIN, OUTPUT);
  
  Serial.begin(9600);
}

float roundToDecimal(float value, int decimalPlaces) {
  float factor = pow(10, decimalPlaces);
  return round(value * factor) / factor;
}

float getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  
  float distance = duration * 0.034 / 2;  // Sesin hızına göre mesafeyi hesapla
  distance = roundToDecimal(distance, 2);
  
  return distance;
}

void moveMotors(float distance) {
  if (distance > 50) {
    // Yeterince uzaksa ileri git
    digitalWrite(FORWARD_BACKWARD_PIN, HIGH);
  } else {
    // Yakınsa geri git
    digitalWrite(FORWARD_BACKWARD_PIN, LOW);
  }
  
  if (distance > 100) {
    // Çok uzaksa yukarı çık
    digitalWrite(UP_DOWN_PIN, HIGH);
  } else if (distance < 50) {
    // Çok yakınsa aşağı in
    digitalWrite(UP_DOWN_PIN, LOW);
  } else {
    // Orta mesafedeyse dur
    digitalWrite(UP_DOWN_PIN, LOW);
  }
  
  if (distance > 75) {
    // Uzaksa sola dön
    digitalWrite(LEFT_RIGHT_PIN, HIGH);
  } else if (distance < 25) {
    // Yakınsa sağa dön
    digitalWrite(LEFT_RIGHT_PIN, LOW);
  } else {
    // Orta mesafedeyse dur
    digitalWrite(LEFT_RIGHT_PIN, LOW);
  }
}

void loop() {
  float distance = getDistance();  // Mesafe ölçümü yap
  moveMotors(distance);  // Motorları hareket ettir
  
  delay(100);
}
