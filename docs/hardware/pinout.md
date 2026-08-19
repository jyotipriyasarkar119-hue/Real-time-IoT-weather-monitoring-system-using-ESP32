# ESP32 Pinout

## Real-Time IoT Weather Monitoring System Using ESP32

---

## 1. Overview

This document defines the GPIO and communication pins used by the ESP32 in the Real-Time IoT Weather Monitoring System.

The ESP32 is connected to environmental sensors for collecting weather measurements and uses Wi-Fi to transmit the data to the Blynk IoT Cloud.

The current reference hardware configuration uses:

- DHT11/DHT22 for temperature and humidity
- BMP280 for atmospheric pressure
- ESP32 for processing and communication

---

# 2. Pin Assignment Summary

| ESP32 Pin | Connected Component | Signal | Interface |
|---|---|---|---|
| GPIO 4 | DHT11/DHT22 | DATA | Digital |
| GPIO 21 | BMP280 | SDA | I2C |
| GPIO 22 | BMP280 | SCL | I2C |
| 3.3V | DHT11/DHT22 | VCC | Power |
| 3.3V | BMP280 | VCC | Power |
| GND | DHT11/DHT22 | GND | Ground |
| GND | BMP280 | GND | Ground |

---

# 3. ESP32 Pinout Diagram

```text
                    ESP32
             ┌───────────────────┐
             │                   │
       3V3 ──┤ 3.3V              │──────► Sensor VCC
             │                   │
       GND ──┤ GND               │──────► Sensor GND
             │                   │
      GPIO4 ─┤ GPIO 4            │──────► DHT DATA
             │                   │
     GPIO21 ─┤ GPIO 21 / SDA     │──────► BMP280 SDA
             │                   │
     GPIO22 ─┤ GPIO 22 / SCL     │──────► BMP280 SCL
             │                   │
             │                   │
             │   Wi-Fi           │
             │      │            │
             │      ▼            │
             │   Blynk IoT       │
             └───────────────────┘
