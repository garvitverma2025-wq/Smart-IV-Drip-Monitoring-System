# Smart IV Drip Monitoring System

An educational embedded-systems prototype developed as part of the Microcontroller and Embedded C Programming course at VIT Chennai.

## Overview

The prototype monitors IV fluid level and drip activity using an AT89S52 microcontroller. Sensor readings are processed by embedded C firmware and displayed on a 16×2 LCD.

## Hardware

- AT89S52 microcontroller development board
- IR drop sensor
- HC-SR04 ultrasonic distance sensor
- 16×2 LCD
- Breadboard, jumper wires and regulated 5 V supply

## Pin Connections

| Module | AT89S52 pin |
|---|---|
| LCD RS | P1.0 |
| LCD EN | P1.1 |
| LCD D4–D7 | P1.4–P1.7 |
| IR sensor OUT | P2.0 |
| HC-SR04 TRIG | P3.6 |
| HC-SR04 ECHO | P3.7 |
| LCD RW | GND |

All modules share a common ground.

## Working Principle

1. The IR sensor detects drops and the microcontroller counts drop events.
2. The HC-SR04 measures the distance to the fluid surface.
3. The firmware estimates fluid level using the prototype's calibration references.
4. The LCD displays the measured drip-rate and fluid-level information.

## Development Tools

- Keil µVision / C51 compiler
- PROGISP for programming the AT89S52
- Embedded C

## Repository Structure

```text
Smart-IV-Drip-Monitoring-System/
├── README.md
├── firmware/
│   └── (add the verified Keil C source file here)
├── hardware/
│   └── (add circuit diagram and prototype photographs here)
└── docs/
    └── (add the project report PDF here)
```

## Current Scope and Limitations

This is a classroom prototype for demonstration with water. It displays sensor-derived estimates of fluid level and drip activity. It is not a medical device, has not been clinically validated, and must not be connected to or used to control an infusion for a patient.

Potential future work includes improved calibration, abnormal-rate detection, low-fluid alerts and more robust fault handling. These are proposed extensions, not claims about features already implemented.

## Contributors

- Garvit Verma
- Arsh Thakral
- Prakhar Sachan

## Academic Context

VIT Chennai — Microcontroller and Embedded C Programming.
