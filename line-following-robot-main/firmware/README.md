# Firmware Architecture

The firmware is structured into isolated, single-responsibility C++ modules executing on a non-blocking fixed 100 Hz ($dt = 10\text{ ms}$) loop cycle.

---

## Module Breakdown

* `main.ino`: System initialization, non-blocking timing loop, line-loss recovery FSM, and adaptive speed scaling.
* `config.h`: System pin definitions, hardware constants, base speeds, and tuning gains.
* `sensor.h / sensor.cpp`: Controls 74HC4051 select lines (`S0`-`S3`), reads raw ADC values, applies dynamic baseline calibration, and computes line position using weighted centroid equations.
* `motor.h / motor.cpp`: TB6612FNG drive interface handling PWM directional control, minimum threshold mapping, and differential steering commands.
* `pid.h / pid.cpp`: Discrete Proportional-Derivative (PD) controller calculating steering offsets and derivative dampening.

---

## Control Flow Architecture

```text
+-----------------------+
|  Read 16 MUX Channels |
+-----------+-----------+
            |
  Sum(Norm) >= 400?
   /             \
 YES              NO ---> [ Line Lost Mode: Pivot in Last Known Direction ]
  |
Compute Weighted Centroid Position (-7500 to +7500)
  |
Compute PD Steering Correction Output
  |
Scale Base Speed based on Error Magnitude
  |
Apply PWM to Left & Right Motors
