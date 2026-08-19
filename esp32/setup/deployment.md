# Deployment Guide

## Real-Time IoT Weather Monitoring System Using ESP32

---

## 1. Overview

This document describes how to deploy the **Real-Time IoT Weather Monitoring System** as a standalone ESP32-based IoT device.

The system uses:

- ESP32
- DHT11/DHT22 temperature and humidity sensor
- BMP280 atmospheric pressure sensor
- Wi-Fi
- Blynk IoT Cloud
- Blynk Dashboard

The ESP32 performs sensor acquisition and processing, while Blynk IoT provides cloud connectivity and remote visualization.

### Deployment Architecture

```text
┌─────────────────────────┐
│   Weather Environment   │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│    Weather Sensors      │
│                         │
│ DHT11/DHT22             │
│ BMP280                  │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│          ESP32          │
│                         │
│ Sensor Acquisition      │
│ Data Processing         │
│ Wi-Fi Communication     │
└────────────┬────────────┘
             │
             │ Wi-Fi
             ▼
┌─────────────────────────┐
│        Internet         │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│     Blynk IoT Cloud     │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│     Blynk Dashboard     │
└────────────┬────────────┘
             │
             ▼
           User
