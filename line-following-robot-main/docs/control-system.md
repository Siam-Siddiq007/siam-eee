# Control System & Adaptive Speed Architecture

## Discrete PD Algorithm Derivation

For high-speed line tracking, integral control ($K_i$) is omitted ($0.000$) to prevent windup saturation during aggressive direction changes. The steering correction is derived strictly using Proportional and Derivative terms:

$$e(t) = \text{Position}(t) - \text{Target Centroid}$$

$$\frac{de(t)}{dt} \approx \frac{e(t) - e(t - dt)}{dt}$$

$$\text{Output}(t) = (K_p \cdot e(t)) + \left( K_d \cdot \frac{e(t) - e(t - dt)}{dt} \right)$$

---

## Adaptive Speed Scaling

To optimize lap times while preventing lateral wheel slip during sharp bends, the system dynamically scales motor base speed:

$$v_{\text{base\_scaled}} = v_{\text{base}} - \left( (v_{\text{base}} - v_{\text{corner}}) \cdot \text{constrain}\left( \frac{\vert{}e(t)\vert{} - e_{\text{thresh}}}{e_{\text{max}} - e_{\text{thresh}}}, 0.0, 1.0 \right) \right)$$

* **Straightaways ($\vert{}e(t)\vert{} < 2500$):** Drives at maximum configured base speed.
* **Corners ($\vert{}e(t)\vert{} \ge 2500$):** Linearly reduces base speed down to `cornerSpeed` to maximize turn torque and tracking accuracy.

---

## Line-Loss Directional Memory

When all 16 sensors detect white background ($\sum N_i < \text{THRESHOLD}$), the system engages trajectory memory:

1. **State Entry:** `isLineLost = true`, log `lineLostTime = millis()`.
2. **Action (< 600 ms):** Pivot in place towards `lastErrorSign` (Left: $-1$, Right: $+1$).
3. **Safety Timeout (> 600 ms):** Complete motor shutdown (`stopMotors()`) to prevent runaway off-track behavior.
