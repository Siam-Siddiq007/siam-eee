# Testing & Calibration Protocols

## Diagnostic Test Scripts

Before running the main controller, verify individual hardware modules using the diagnostic sketches located in `tests/diagnostic_scripts/`:

1. `mux_raw_scan.ino`: Reads raw 0–4095 ADC signals across all 16 channels to verify infrared emitter/phototransistor hardware.
2. `motor_direction_check.ino`: Drives left and right motors forward, reverse, and stop sequentially to confirm H-bridge polarity wiring.

---

## Systematic PID Tuning Guide

1. **Zero-Gain Baseline:** Set $K_p = 0.000$, $K_d = 0.000$. Verify both motors drive straight without pulling to one side.
2. **Proportional Gain ($K_p$):** Increase $K_p$ incrementally until the robot tracks straight lines with slight symmetrical oscillation ($K_p \approx 0.045$).
3. **Derivative Gain ($K_d$):** Increase $K_d$ to dampen oscillations and smooth out curve entries ($K_d \approx 0.180$).
4. **Adaptive Speed Floor:** Adjust `cornerSpeed` down until the chassis completes 90-degree curves without wheel scrub or drift.
