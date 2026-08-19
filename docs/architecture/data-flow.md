# Data Flow

## Real-Time IoT Weather Monitoring System Using ESP32

---

## 1. Overview

This document describes how weather data moves through the **Real-Time IoT Weather Monitoring System**.

The system uses an **ESP32** to collect measurements from environmental sensors and sends the processed data to **Blynk IoT Cloud** over Wi-Fi. The data is then displayed on the Blynk dashboard for real-time monitoring.

### Complete Data Flow

```text
Environmental Conditions
          │
          ▼
   Weather Sensors
          │
          ▼
        ESP32
          │
          ├── Read
          ├── Process
          └── Validate
          │
          ▼
        Wi-Fi
          │
          ▼
      Internet
          │
          ▼
   Blynk IoT Cloud
          │
          ▼
      Datastreams
          │
          ▼
   Blynk Dashboard
          │
          ▼
         User
