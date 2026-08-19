# Sensor Connections

## Real-Time IoT Weather Monitoring System Using ESP32

---

## 1. Overview

This document describes how the environmental sensors are connected to the ESP32 in the **Real-Time IoT Weather Monitoring System**.

The ESP32 acts as the central sensing and processing unit. The connected sensors measure environmental parameters, and the ESP32 reads these measurements before sending them to the Blynk IoT Cloud through Wi-Fi.

### Sensor Data Path

```text
┌──────────────────────┐
│ Environmental        │
│ Conditions           │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│      Sensors         │
│                      │
│ Temperature          │
│ Humidity             │
│ Pressure             │
└──────────┬───────────┘
           │
           │ GPIO / I2C
           ▼
┌──────────────────────┐
│        ESP32         │
└──────────┬───────────┘
           │
           │ Wi-Fi
           ▼
┌──────────────────────┐
│    Blynk IoT Cloud   │
└──────────────────────┘
