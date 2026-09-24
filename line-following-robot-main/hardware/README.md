# Hardware & Mechanical Specifications

## Complete ESP32 Pinout Mapping

| ESP32 Pin | Function | Connected Peripheral / Hardware |
| :--- | :--- | :--- |
| `GPIO 18` | MUX Select `S0` | 74HC4051 Pin 11 (Both MUX) |
| `GPIO 19` | MUX Select `S1` | 74HC4051 Pin 10 (Both MUX) |
| `GPIO 21` | MUX Select `S2` | 74HC4051 Pin 9 (Both MUX) |
| `GPIO 22` | MUX Select `S3` | 74HC4051 Enable Line Control |
| `GPIO 34` | ADC Input (Left) | Left MUX Signal Output (Sensors 0–7) |
| `GPIO 35` | ADC Input (Right) | Right MUX Signal Output (Sensors 8–15) |
| `GPIO 16` | Motor Control | TB6612FNG `AIN1` |
| `GPIO 17` | Motor Control | TB6612FNG `AIN2` |
| `GPIO 4`  | PWM Speed | TB6612FNG `PWMA` |
| `GPIO 25` | Motor Control | TB6612FNG `BIN1` |
| `GPIO 26` | Motor Control | TB6612FNG `BIN2` |
| `GPIO 2`  | PWM Speed | TB6612FNG `PWMB` |
| `GPIO 13` | Standby | TB6612FNG `STBY` |

---

## 3D Printing Manufacturing Specs

### Chassis Frame
* **Material:** PETG or PLA+
* **Infill:** 30% Gyroid
* **Walls:** 4 Perimeter Wall Lines
* **Layer Height:** 0.2 mm

### Custom Wheels & Tires
* **Wheel Rim:** PLA+ (100% Infill, M3 Set-Screw Hub Interface)
* **Tires:** TPU 95A Flexible Filament (2 Perimeters, 15% Infill for ground grip)
* **Outer Diameter:** 32.0 mm
* **Tire Width:** 12.0 mm
