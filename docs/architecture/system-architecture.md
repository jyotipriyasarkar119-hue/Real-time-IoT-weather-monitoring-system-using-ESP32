# System Architecture

## 1. Overview

The Real-Time IoT Weather Monitoring System is an ESP32-based weather station that collects environmental measurements from connected sensors and sends the data to the Blynk IoT cloud platform over Wi-Fi.

The Blynk platform provides the cloud infrastructure and dashboard used to remotely monitor the collected weather parameters.

The system follows a simple IoT architecture:

```text
Environmental Sensors
        │
        ▼
      ESP32
        │
        │ Wi-Fi
        ▼
    Internet
        │
        ▼
  Blynk IoT Cloud
        │
        ▼
 Blynk Dashboard
