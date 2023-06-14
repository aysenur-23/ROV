#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define MOTOR_1_PIN 2
#define MOTOR_2_PIN 3
#define MOTOR_3_PIN 4
#define MOTOR_4_PIN 5
#define MOTOR_5_PIN 6
#define MOTOR_6_PIN 7
#define LEAK_SENSOR_PIN A0

Adafruit_MPU6050 mpu;
int16_t gyroX, gyroY, gyroZ;
float depth;
float distance;
int leakSensorValue;

void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_1_PIN, OUTPUT);
  pinMode(MOTOR_2_PIN, OUTPUT);
  pinMode(MOTOR_3_PIN, OUTPUT);
  pinMode(MOTOR_4_PIN, OUTPUT);
  pinMode(MOTOR_5_PIN, OUTPUT);
  pinMode(MOTOR_6_PIN, OUTPUT);
  pinMode(LEAK_SENSOR_PIN, INPUT);
  
  Wire.begin();
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
}

void loop() {
  // Motorları çalıştır
  runMotors();

  // Derinlik sensöründen veri al
  readDepthSensor();

  // Gyro sensöründen veri al
  readGyroSensor();

  // Ultrasonik sensörden mesafe al
  readUltrasonicSensor();

  // Sızdırmazlık sensöründen veri al
  readLeakSensor();

  // Verileri seri porta yazdır
  Serial.print("Depth: ");
  Serial.print(depth);
  Serial.print(" meters\t");
  Serial.print("Gyro (X,Y,Z): ");
  Serial.print(gyroX);
  Serial.print(", ");
  Serial.print(gyroY);
  Serial.print(", ");
  Serial.print(gyroZ);
  Serial.print("\tDistance: ");
  Serial.print(distance);
  Serial.print(" cm\tLeak Sensor: ");
  Serial.println(leakSensorValue);

  delay(1000);
}

void runMotors() {
  // Motorları ileri yönde çalıştır
  analogWrite(MOTOR_1_PIN, 255);
  analogWrite(MOTOR_2_PIN, 255);
  analogWrite(MOTOR_3_PIN, 255);
  analogWrite(MOTOR_4_PIN, 255);
  analogWrite(MOTOR_5_PIN, 255);
  analogWrite(MOTOR_6_PIN, 255);
}

void readDepthSensor() {
  // Derinlik sensöründen veri al
  // Bu örnekte depth değişkenine rasgele bir değer atandı
  depth = random(0, 10);
}

void readGyroSensor() {
  // Gyro sensöründen veri al
  sensors_event_t gyroEvent;
  mpu.getGyroSensor()->getEvent(&gyroEvent);
  gyroX = gyroEvent.gyro.x;
  gyroY = gyroEvent.gyro.y;
  gyroZ = gyroEvent.gyro.z;
}

void readUltrasonicSensor() {
  // Ultrasonik sensörden mesafe ölçümü yap
  // Bu örnekte distance değişkenine rasgele bir değer atandı
  distance = random(0, 100);
}

void readLeakSensor() {
  // Sızdırmazlık sensöründen veri al
  leakSensorValue = analogRead(LEAK_SENSOR_PIN);
}
