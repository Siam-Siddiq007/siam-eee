// Diagnostic: Motor Driver & Direction Check (TB6612FNG)
#include <Arduino.h>

#define AIN1 16
#define AIN2 17
#define PWMA 4

#define BIN1 25
#define BIN2 26
#define PWMB 2

#define STBY 13

void setup() {
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT); pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);
}

void loop() {
  // 1. Both Motors FORWARD
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW); analogWrite(PWMA, 120);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW); analogWrite(PWMB, 120);
  delay(2000);

  // 2. STOP
  analogWrite(PWMA, 0); analogWrite(PWMB, 0);
  delay(1000);

  // 3. Both Motors REVERSE
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH); analogWrite(PWMA, 120);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH); analogWrite(PWMB, 120);
  delay(2000);

  // 4. STOP
  analogWrite(PWMA, 0); analogWrite(PWMB, 0);
  delay(2000);
}
