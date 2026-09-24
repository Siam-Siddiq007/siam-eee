#include "config.h"
#include "motor.h"
#include "sensor.h"

MotorController motors;
SensorArray sensors;
PIDGains pid;

int32_t lastError = 0;

void setup() {
    Serial.begin(115200);
    
    motors.begin();
    sensors.begin();

    Serial.println(F("[SYSTEM] Starting Sensor Calibration..."));
    sensors.calibrate();
    Serial.println(F("[SYSTEM] Calibration Complete. Robot Ready!"));
    
    delay(1000);
}

void loop() {
    // 1. Get position from look-ahead sensor array
    uint16_t position = sensors.readLinePosition(false);
    
    // 2. Compute error relative to center (3500)
    int32_t error = (int32_t)position - LINE_CENTER_POSITION;
    int32_t derivative = error - lastError;
    lastError = error;

    // 3. Compute PD differential output
    float turnCorrection = (pid.kp * error) + (pid.kd * derivative);

    // 4. Calculate motor speeds
    int16_t leftSpeed  = MOTOR_BASE_SPEED + (int16_t)turnCorrection;
    int16_t rightSpeed = MOTOR_BASE_SPEED - (int16_t)turnCorrection;

    // 5. Update TB6612FNG outputs
    motors.setSpeeds(leftSpeed, rightSpeed);
}
