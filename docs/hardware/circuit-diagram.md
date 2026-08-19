# Circuit Diagram

## Real-Time IoT Weather Monitoring System Using ESP32

---

## 1. Overview

This document describes the electrical connections between the **ESP32 development board** and the environmental sensors used in the Real-Time IoT Weather Monitoring System.

The ESP32 acts as the central controller. It receives measurements from the connected sensors and transmits the processed data to the Blynk IoT Cloud through Wi-Fi.

```text
┌──────────────────────────┐
│    Environmental         │
│        Sensors           │
└────────────┬─────────────┘
             │
             │ Sensor Signals
             ▼
┌──────────────────────────┐
│          ESP32           │
│                          │
│  GPIO / I2C / ADC        │
│           │              │
│           ▼              │
│      Wi-Fi Module        │
└────────────┬─────────────┘
             │
             │ Wi-Fi
             ▼
        Blynk IoT Cloud
