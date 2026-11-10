# Hardware Connections

The following mapping documents the prototype wiring used in the project.

| Module signal | AT89S52 pin / connection |
|---|---|
| LCD RS | P1.0 |
| LCD EN | P1.1 |
| LCD D4 | P1.4 |
| LCD D5 | P1.5 |
| LCD D6 | P1.6 |
| LCD D7 | P1.7 |
| LCD RW | GND |
| LCD VSS | GND |
| LCD VDD | +5 V |
| LCD V0 | GND (prototype configuration used without a contrast potentiometer) |
| IR sensor OUT / DO | P2.0 |
| IR sensor VCC | +5 V |
| IR sensor GND | GND |
| HC-SR04 TRIG | P3.6 |
| HC-SR04 ECHO | P3.7 |
| HC-SR04 VCC | +5 V |
| HC-SR04 GND | GND |

## Wiring Notes

- Connect all module grounds to the AT89S52 board ground.
- Use a regulated supply appropriate for the development board and modules.
- Verify the actual board header labels and sensor pin labels before applying power.
- The HC-SR04 timing conversion and fluid-level percentage are approximate and require calibration against the actual container geometry.
- This is a water-based educational prototype only, not a patient-connected medical device.
