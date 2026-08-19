# Installation Guide

## Real-Time IoT Weather Monitoring System Using ESP32

---

## 1. Overview

This guide explains how to set up and run the **Real-Time IoT Weather Monitoring System** using an ESP32, environmental sensors, and Blynk IoT.

The current project uses:

- ESP32
- DHT11/DHT22 temperature and humidity sensor
- BMP280 atmospheric pressure sensor
- Arduino IDE or compatible ESP32 development environment
- Wi-Fi
- Blynk IoT Cloud

The current architecture does **not** require:

- MQTT
- Flask
- A custom backend server
- A local database
- A separate operating system/server environment

---

# 2. System Requirements

## Hardware

Required hardware:

- ESP32 development board
- DHT11 or DHT22 sensor
- BMP280 sensor
- Breadboard
- Jumper wires
- USB cable
- Computer for programming the ESP32
- Wi-Fi network

---

## Software

Required software:

- Arduino IDE
- ESP32 board package
- Blynk library
- DHT sensor library
- Adafruit Unified Sensor library
- Adafruit BMP280 library

---

# 3. Repository Structure

The relevant project structure is:

```text
Real-time-IoT-weather-monitoring-system-using-ESP32/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── firmware/
│   └── esp32/
│       ├── README.md
│       │
│       ├── src/
│       │   ├── main.ino
│       │   ├── sensors.h
│       │   └── sensors.cpp
│       │
│       └── config/
│           ├── config.example.h
│           └── config.h
│
├── docs/
│   ├── architecture/
│   │   ├── system-architecture.md
│   │   ├── data-flow.md
│   │   ├── mqtt-architecture.md
│   │   └── database-architecture.md
│   │
│   ├── hardware/
│   │   ├── circuit-diagram.md
│   │   ├── sensor-connections.md
│   │   └── pinout.md
│   │
│   └── setup/
│       └── installation.md
│
└── assets/
    ├── screenshots/
    └── diagrams/
