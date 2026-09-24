// Diagnostic: 16-Channel Multiplexer Raw ADC Scanner
#include <Arduino.h>

#define MUX_S0 18
#define MUX_S1 19
#define MUX_S2 21
#define MUX_S3 22

#define MUX_LEFT  34  // Sensors 0-7
#define MUX_RIGHT 35  // Sensors 8-15

void setup() {
  Serial.begin(115200);
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);

  pinMode(MUX_LEFT, INPUT);
  pinMode(MUX_RIGHT, INPUT);
}

void loop() {
  int rawVal[16];

  for (byte i = 0; i < 8; i++) {
    digitalWrite(MUX_S0, (i & 1) ? HIGH : LOW);
    digitalWrite(MUX_S1, (i & 2) ? HIGH : LOW);
    digitalWrite(MUX_S2, (i & 4) ? HIGH : LOW);
    digitalWrite(MUX_S3, (i & 8) ? HIGH : LOW);
    delayMicroseconds(20);

    rawVal[i]     = analogRead(MUX_LEFT);
    rawVal[i + 8] = analogRead(MUX_RIGHT);
  }

  for (int i = 0; i < 16; i++) {
    Serial.print("S"); Serial.print(i); Serial.print(":");
    Serial.print(rawVal[i]);
    if (i < 15) Serial.print(" ");
  }
  Serial.println();
  delay(100);
}
