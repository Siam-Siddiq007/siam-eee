#include "motor.h"

MotorController::MotorController() {}

void MotorController::begin() {
    // Configure direction control pins
    pinMode(PIN_MOTOR_A_IN1, OUTPUT);
    pinMode(PIN_MOTOR_A_IN2, OUTPUT);
    pinMode(PIN_MOTOR_B_IN1, OUTPUT);
    pinMode(PIN_MOTOR_B_IN2, OUTPUT);
    pinMode(PIN_MOTOR_STBY, OUTPUT);

    // Attach ESP32 LEDC PWM timers
    ledcSetup(PWM_CHANNEL_LEFT, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(PIN_MOTOR_A_PWM, PWM_CHANNEL_LEFT);

    ledcSetup(PWM_CHANNEL_RIGHT, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(PIN_MOTOR_B_PWM, PWM_CHANNEL_RIGHT);

    // Disable standby to enable H-bridge outputs
    standby(false);
    stop();
}

void MotorController::standby(bool enable) {
    digitalWrite(PIN_MOTOR_STBY, enable ? LOW : HIGH);
}

void MotorController::setMotorA(int16_t speed) {
    speed = constrain(speed, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);

    if (speed > 0) {
        digitalWrite(PIN_MOTOR_A_IN1, HIGH);
        digitalWrite(PIN_MOTOR_A_IN2, LOW);
        ledcWrite(PWM_CHANNEL_LEFT, speed);
    } else if (speed < 0) {
        digitalWrite(PIN_MOTOR_A_IN1, LOW);
        digitalWrite(PIN_MOTOR_A_IN2, HIGH);
        ledcWrite(PWM_CHANNEL_LEFT, -speed);
    } else {
        digitalWrite(PIN_MOTOR_A_IN1, LOW);
        digitalWrite(PIN_MOTOR_A_IN2, LOW);
        ledcWrite(PWM_CHANNEL_LEFT, 0);
    }
}

void MotorController::setMotorB(int16_t speed) {
    speed = constrain(speed, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);

    if (speed > 0) {
        digitalWrite(PIN_MOTOR_B_IN1, HIGH);
        digitalWrite(PIN_MOTOR_B_IN2, LOW);
        ledcWrite(PWM_CHANNEL_RIGHT, speed);
    } else if (speed < 0) {
        digitalWrite(PIN_MOTOR_B_IN1, LOW);
        digitalWrite(PIN_MOTOR_B_IN2, HIGH);
        ledcWrite(PWM_CHANNEL_RIGHT, -speed);
    } else {
        digitalWrite(PIN_MOTOR_B_IN1, LOW);
        digitalWrite(PIN_MOTOR_B_IN2, LOW);
        ledcWrite(PWM_CHANNEL_RIGHT, 0);
    }
}

void MotorController::setSpeeds(int16_t leftSpeed, int16_t rightSpeed) {
    setMotorA(leftSpeed);
    setMotorB(rightSpeed);
}

void MotorController::stop() {
    setSpeeds(0, 0);
}
