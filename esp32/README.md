# ESP32 Weather Station Firmware

Firmware for the **Real-Time IoT Weather Monitoring System using ESP32 and Blynk IoT**.

This directory contains the embedded software responsible for reading environmental sensors, processing weather measurements, connecting the ESP32 to Wi-Fi, and sending real-time data to the Blynk IoT platform.

---

## 1. Overview

The ESP32 acts as the main sensing and communication unit of the weather monitoring system.

The basic firmware pipeline is:

```text id="f94d9f"
Environmental Sensors
        │
        ▼
      ESP32
        │
        ├── Read Sensors
        ├── Process Measurements
        ├── Connect to Wi-Fi
        └── Send Data
                │
                ▼
          Blynk IoT Cloud
                │
                ▼
        Blynk Dashboard
```

The firmware continuously collects environmental measurements and sends them to Blynk using Wi-Fi.

---

## 2. Firmware Responsibilities

The ESP32 firmware is responsible for:

- Initializing connected sensors
- Reading environmental measurements
- Processing raw sensor values
- Connecting to a Wi-Fi network
- Connecting to Blynk IoT
- Sending sensor measurements to Blynk
- Updating Blynk virtual pins
- Maintaining Wi-Fi connectivity
- Maintaining Blynk connectivity
- Providing serial debugging information

---

## 3. Directory Structure

```text id="4zy52k"
firmware/
└── esp32/
    ├── README.md
    │
    ├── src/
    │   └── Weather_Station.ino
    │
    └── config/
        └── config.example.h
```

### Files

| File | Purpose |
|---|---|
| `README.md` | ESP32 firmware documentation |
| `src/Weather_Station.ino` | Main ESP32 firmware |
| `config/config.example.h` | Example configuration template |

---

## 4. System Architecture

```text id="jhg9qu"
┌────────────────────────────┐
│   Environmental Sensors    │
│                            │
│ • Temperature              │
│ • Humidity                 │
│ • Pressure                 │
│ • Other Weather Parameters │
└─────────────┬──────────────┘
              │
              ▼
      ┌───────────────┐
      │     ESP32     │
      │               │
      │ Sensor Reading│
      │ Processing    │
      │ Wi-Fi         │
      │ Blynk Client  │
      └───────┬───────┘
              │
              │ Internet
              ▼
      ┌───────────────┐
      │  Blynk Cloud  │
      └───────┬───────┘
              │
              ▼
      ┌───────────────┐
      │ Blynk Web /   │
      │ Mobile        │
      │ Dashboard     │
      └───────────────┘
```

---

## 5. Firmware Execution Flow

When the ESP32 starts, the firmware initializes the system and establishes the required network connections.

```text id="mqh1av"
ESP32 Boot
    │
    ▼
Initialize Serial
    │
    ▼
Initialize Sensors
    │
    ▼
Connect to Wi-Fi
    │
    ▼
Connect to Blynk
    │
    ▼
Start Main Loop
    │
    ├── Read Sensors
    │
    ├── Process Values
    │
    ├── Send to Blynk
    │
    └── Maintain Connection
```

---

## 6. Hardware Requirements

Typical hardware required for the project includes:

- ESP32 development board
- Environmental sensors used by the weather station
- Breadboard or PCB
- Jumper wires
- USB cable
- Suitable power supply
- Wi-Fi network

For exact sensor connections and GPIO assignments, refer to:

```text id="59y20s"
docs/hardware/
├── circuit-diagram.md
├── sensor-connections.md
└── pinout.md
```

---

## 7. Software Requirements

The firmware can be developed and uploaded using the Arduino IDE.

Required software:

- Arduino IDE
- ESP32 board support package
- Blynk library
- Sensor-specific Arduino libraries

The exact sensor libraries depend on the hardware used in the project.

---

## 8. Blynk IoT

The project uses **Blynk IoT** as the cloud platform for real-time weather monitoring.

The communication flow is:

```text id="zdz5w3"
Sensor
   │
   ▼
ESP32
   │
   │ Wi-Fi
   ▼
Internet
   │
   ▼
Blynk Cloud
   │
   ├── Virtual Pins
   ├── Datastreams
   └── Device Data
           │
           ▼
      Blynk Dashboard
```

Blynk provides the interface for displaying sensor measurements without requiring a custom backend or database server.

---

## 9. Blynk Configuration

The firmware requires Blynk device configuration.

Typical configuration includes:

```cpp id="weezml"
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"
```

Replace the placeholder values with the credentials generated for your Blynk device.

### Security

Do **not** commit real Blynk authentication tokens to the public repository.

Use a local configuration file such as:

```text id="b6h4pu"
config.h
```

and add it to `.gitignore`.

Provide only:

```text id="egau76"
config.example.h
```

in the public repository.

---

## 10. Wi-Fi Configuration

The ESP32 requires Wi-Fi credentials to communicate with Blynk Cloud.

Example:

```cpp id="u82zvi"
#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
```

Do not commit real Wi-Fi credentials to GitHub.

---

## 11. Configuration Example

A configuration template can look like:

```cpp id="udw9l8"
#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#endif
```

Save the public template as:

```text id="brcfab"
config/config.example.h
```

The actual configuration containing private credentials should remain local.

---

## 12. Blynk Virtual Pins

Sensor measurements are sent to Blynk using virtual pins.

Example mapping:

| Virtual Pin | Parameter |
|---|---|
| `V0` | Temperature |
| `V1` | Humidity |
| `V2` | Pressure |
| `V3` | Additional Sensor |
| `V4` | Additional Sensor |

The actual mapping must correspond to the Blynk datastream configuration used by the project.

Example:

```cpp id="1w1x0j"
Blynk.virtualWrite(V0, temperature);
Blynk.virtualWrite(V1, humidity);
Blynk.virtualWrite(V2, pressure);
```

---

## 13. Sensor Reading

The ESP32 periodically reads the connected sensors.

Conceptually:

```text id="up0xw4"
Read Temperature
       │
Read Humidity
       │
Read Pressure
       │
Read Other Sensors
       │
       ▼
Validate Measurements
       │
       ▼
Send to Blynk
```

Sensor-reading functions should be kept separate from Blynk communication logic where possible.

---

## 14. Sending Data to Blynk

Weather measurements should be transmitted at a controlled interval rather than continuously inside the main loop.

A typical implementation uses a Blynk timer:

```cpp id="ghm4ym"
BlynkTimer timer;
```

A function can periodically send measurements:

```cpp id="gm3v6k"
void sendSensorData() {

    // Read sensors

    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, pressure);
}
```

Then configure the interval:

```cpp id="esil60"
timer.setInterval(5000L, sendSensorData);
```

This example updates Blynk approximately every five seconds.

---

## 15. Main Loop

The main loop should remain lightweight.

Typical structure:

```cpp id="eyvqxc"
void loop() {

    Blynk.run();

    timer.run();
}
```

Sensor processing should preferably be handled by scheduled functions rather than long blocking operations inside `loop()`.

---

## 16. Serial Monitoring

Serial output can be used to verify firmware operation.

Example:

```text id="bmb6l9"
===================================
 ESP32 IoT Weather Monitoring Node
===================================

Initializing sensors...
Sensors initialized.

Connecting to Wi-Fi...
Wi-Fi connected.

Connecting to Blynk...
Blynk connected.

Temperature : 29.4 °C
Humidity    : 71.0 %
Pressure    : 1008.5 hPa

Sending data to Blynk...

Data sent successfully.
```

Serial Monitor is particularly useful for debugging sensor and network problems.

---

## 17. Uploading Firmware

### Step 1 — Install Arduino IDE

Install the Arduino IDE and configure ESP32 board support.

### Step 2 — Install Libraries

Install:

```text id="jcwue3"
Blynk
ESP32 board libraries
Sensor-specific libraries
```

### Step 3 — Configure Credentials

Configure:

```text id="h75fch"
Wi-Fi SSID
Wi-Fi Password
Blynk Template ID
Blynk Template Name
Blynk Auth Token
```

### Step 4 — Connect ESP32

Connect the ESP32 to the computer using USB.

### Step 5 — Select Board

In Arduino IDE, select the appropriate ESP32 development board.

### Step 6 — Select Port

Select the serial port corresponding to the ESP32.

### Step 7 — Compile

Compile the firmware and resolve any library or configuration errors.

### Step 8 — Upload

Upload the firmware to the ESP32.

### Step 9 — Serial Monitor

Open Serial Monitor and verify that the device successfully connects to Wi-Fi and Blynk.

---

## 18. Testing

Test the system in stages.

### Sensor Test

```text id="ql0z9v"
Sensor
   ↓
ESP32
   ↓
Serial Monitor
```

Confirm that the measurements are reasonable.

### Wi-Fi Test

```text id="gjcmc6"
ESP32
   ↓
Wi-Fi Router
   ↓
Internet
```

Confirm that the ESP32 connects successfully.

### Blynk Test

```text id="lsv5k2"
ESP32
   ↓
Internet
   ↓
Blynk Cloud
```

Confirm that the device appears online.

### Dashboard Test

```text id="g0ylau"
Sensors
   ↓
ESP32
   ↓
Blynk Cloud
   ↓
Blynk Dashboard
```

Confirm that the dashboard values update correctly.

---

## 19. Troubleshooting

### ESP32 Cannot Connect to Wi-Fi

Check:

- Wi-Fi SSID
- Wi-Fi password
- Wi-Fi signal strength
- Router availability
- ESP32 power supply

### Blynk Device Shows Offline

Check:

- Internet connection
- Blynk Auth Token
- Template ID
- Template Name
- Blynk library
- Wi-Fi connection

### Dashboard Does Not Update

Check:

```text id="csw4l3"
Sensor
   ↓
Sensor Reading
   ↓
ESP32 Variable
   ↓
Blynk.virtualWrite()
   ↓
Correct Virtual Pin
   ↓
Blynk Datastream
   ↓
Dashboard Widget
```

Make sure the virtual pin used by the firmware matches the datastream configured in Blynk.

### Incorrect Sensor Values

Check:

- Sensor wiring
- GPIO assignment
- Power supply
- Sensor library
- Calibration
- Sensor placement

---

## 20. Security

Never publish:

- Blynk authentication tokens
- Wi-Fi passwords
- Private credentials

The repository should contain only configuration templates with placeholder values.

Example:

```text id="0s0pjg"
YOUR_WIFI_SSID
YOUR_WIFI_PASSWORD
YOUR_TEMPLATE_ID
YOUR_AUTH_TOKEN
```

---

## 21. Related Documentation

Additional project documentation is available under:

```text id="e4qdhx"
docs/
├── architecture/
│   ├── system-architecture.md
│   └── data-flow.md
│
├── hardware/
│   ├── circuit-diagram.md
│   ├── sensor-connections.md
│   └── pinout.md
│
└── setup/
    ├── installation.md
    └── blynk-setup.md
```

---

## 22. Firmware Flow Summary

```text id="2abuxv"
Environmental Sensors
        │
        ▼
      ESP32
        │
        ├── Sensor Acquisition
        ├── Data Processing
        ├── Wi-Fi Connection
        └── Blynk Communication
                  │
                  ▼
             Blynk Cloud
                  │
                  ▼
          Real-Time Dashboard
```

The ESP32 acts as the bridge between the physical weather sensors and the Blynk IoT platform, enabling real-time remote monitoring without requiring a dedicated application server or external database.
