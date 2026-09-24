#include "sensor.h"

SensorArray::SensorArray() : lastPosition(LINE_CENTER_POSITION), lineLost(false) {
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        minValues[i] = ADC_MAX_VAL;
        maxValues[i] = 0;
    }
}

void SensorArray::begin() {
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        pinMode(SENSOR_PINS[i], INPUT);
    }
}

void SensorArray::calibrate() {
    for (uint16_t sample = 0; sample < CALIBRATION_SAMPLES; sample++) {
        for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
            uint16_t val = analogRead(SENSOR_PINS[i]);
            if (val < minValues[i]) minValues[i] = val;
            if (val > maxValues[i]) maxValues[i] = val;
        }
        delay(5);
    }
}

uint16_t SensorArray::readLinePosition(bool whiteLine) {
    uint32_t weightedSum = 0;
    uint32_t valueSum = 0;
    bool onLine = false;

    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
        rawValues[i] = analogRead(SENSOR_PINS[i]);
        
        // Normalize raw readings to 0 - 1000 range based on calibration limits
        uint16_t minVal = minValues[i];
        uint16_t maxVal = maxValues[i];
        
        if (maxVal <= minVal) maxVal = minVal + 1; // Prevent divide-by-zero

        int32_t calibrated = map(rawValues[i], minVal, maxVal, 0, 1000);
        calibrated = constrain(calibrated, 0, 1000);

        if (whiteLine) {
            calibrated = 1000 - calibrated;
        }

        calibratedValues[i] = (uint16_t)calibrated;

        // Check if any sensor detects the line (threshold 200/1000)
        if (calibratedValues[i] > 200) {
            onLine = true;
        }

        weightedSum += (uint32_t)calibratedValues[i] * (i * 1000);
        valueSum += calibratedValues[i];
    }

    if (!onLine) {
        lineLost = true;
        // Keep last position extreme to turn back toward line quickly
        return (lastPosition < LINE_CENTER_POSITION) ? 0 : 7000;
    }

    lineLost = false;
    lastPosition = (uint16_t)(weightedSum / valueSum);
    return lastPosition;
}

bool SensorArray::isLineLost() {
    return lineLost;
}
