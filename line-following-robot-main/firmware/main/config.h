#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// =====================================================
// HARDWARE PIN DEFINITIONS (ESP32)
// =====================================================

// Multiplexer 74HC4051 Select Lines
#define MUX_S0 18
#define MUX_S1 19
#define MUX_S2 21
#define MUX_S3 22

// Multiplexer Analog Inputs (ADC1)
#define MUX_ANALOG_LEFT  34  // Sensors 0-7
#define MUX_ANALOG_RIGHT 35  // Sensors 8-15

// Motor Driver TB6612FNG
#define AIN1 16
#define AIN2 17
#define PWMA 4

#define BIN1 25
#define BIN2 26
#define PWMB 2

#define STBY 13

// =====================================================
// CONTROL SYSTEM PARAMETERS
// =====================================================

// PID Gains
extern float Kp;
extern float Ki;
extern float Kd;

// Speed Control (0 - 255 PWM)
extern int baseSpeed;
extern int cornerSpeed;
extern int maxSpeed;
extern int recoverySpeed;

#define CORNER_ERROR_THRESHOLD 2500
#define LINE_SUM_THRESHOLD     400

// Safety Limits
#define MAX_RECOVERY_MS        600
#define LOOP_DT_MS             10

// Debug & Modes
#define TEST_MODE_NO_MOTORS    false
#define DEBUG_SERIAL           true

#endif // CONFIG_H
