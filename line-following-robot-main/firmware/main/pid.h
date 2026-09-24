#ifndef PID_H
#define PID_H

#include "config.h"

class PIDController {
public:
    PIDController();

    void begin(float kp, float ki, float kd);
    void setGains(float kp, float ki, float kd);
    void setOutputLimits(float minVal, float maxVal);
    void setWindupLimits(float limit);
    
    float compute(int32_t setpoint, int32_t input, float dt);
    void reset();

    // Gain accessors for telemetry / dynamic tuning
    float getKp() const { return _kp; }
    float getKi() const { return _ki; }
    float getKd() const { return _kd; }

private:
    float _kp;
    float _ki;
    float _kd;

    float _minOutput;
    float _maxOutput;
    float _iTermLimit;

    float _integral;
    float _lastInput;
    bool _firstRun;
};

#endif // PID_H
