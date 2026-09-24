# 16-Channel Multiplexed Sensor Array Geometry

## Multiplexer Timing Sequence

To read 16 analog TCRT5000 IR phototransistor outputs using only 2 ESP32 ADC pins, dual **74HC4051** 8-channel analog multiplexers are used.

```text
[ESP32 GPIO 18, 19, 21] ---> S0, S1, S2 Select Lines (Shared)
                                  │
         ┌────────────────────────┴────────────────────────┐
         ▼                                                 ▼
[MUX 1: Left Array (S00-S07)]                     [MUX 2: Right Array (S08-S15)]
         │                                                 │
   Signal Output                                     Signal Output
         │                                                 │
         ▼                                                 ▼
 [ESP32 GPIO 34 (ADC1)]                           [ESP32 GPIO 35 (ADC1)]
