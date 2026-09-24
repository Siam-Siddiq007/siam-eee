#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"

class SensorArray {
public:
    SensorArray();

    void begin();
    void calibrate();
    uint16_t readLinePosition(bool whiteLine = false);
    
    uint16_t rawValues[SENSOR_COUNT];
    uint16_t calibratedValues[SENSOR_COUNT];
    bool isLineLost();

private:
    uint16_t minValues[SENSOR_COUNT];
    uint16_t maxValues[SENSOR_COUNT];
    uint16_t lastPosition;
    bool lineLost;
};

#endif // SENSOR_H
