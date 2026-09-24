#ifndef MOTOR_H
#define MOTOR_H

#include "config.h"

class MotorController {
public:
    MotorController();

    void begin();
    void setSpeeds(int16_t leftSpeed, int16_t rightSpeed);
    void stop();
    void standby(bool enable);

private:
    void setMotorA(int16_t speed);
    void setMotorB(int16_t speed);
};

#endif // MOTOR_H
