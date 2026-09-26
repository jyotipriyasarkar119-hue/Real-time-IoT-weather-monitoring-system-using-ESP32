# Real-Time IoT Weather Monitoring System using ESP32

A complete ESP32-based weather monitoring platform that collects environmental data from a **BME680** and **rain sensor**, publishes telemetry over **MQTT**, stores readings in **SQLite**, and displays live measurements through a **Flask web dashboard**.

## System Overview

```
BME680 + Rain Sensor
        |
        v
      ESP32
        |
        | MQTT
        v
  Mosquitto Broker
        |
        v
   Flask Backend
        |
     +--+--+
     |     |
     v     v
 SQLite  REST API
           |
           v
       Web Dashboard
```

## Features

- 🌡️ BME680 temperature monitoring
- 💧 Relative humidity monitoring
- 🌬️ Atmospheric pressure monitoring
- 🔥 BME680 gas-resistance measurement
- 🌧️ Analog rain-sensor monitoring
- 📡 MQTT telemetry from ESP32
- 🗄️ SQLite data persistence
- 🌐 Flask REST API
- 📊 Live browser dashboard
- 🔄 Automatic dashboard refresh
- 🧩 Modular project organization
- 🔐 Credentials kept out of the repository

## Hardware

| Component | Connection |
|---|---|
| ESP32 Dev Module | Main controller |
| BME680 | SPI |
| Rain Sensor | Analog |
| Fedora/Linux PC or Raspberry Pi | MQTT broker + Flask backend |

### BME680 SPI

| BME680 | ESP32 |
|---|---|
| CS | GPIO 5 |
| SCK | GPIO 18 |
| SDO / MISO | GPIO 19 |
| SDI / MOSI | GPIO 23 |
| VCC | 3.3V |
| GND | GND |

### Rain Sensor

| Rain Sensor | ESP32 |
|---|---|
| AO | GPIO 34 |
| VCC | 3.3V |
| GND | GND |

## Repository Structure

```
Real-time-IoT-weather-monitoring-system-using-ESP32/
│
├── firmware/
│   ├── src/
│   │   └── main.cpp
│   └── platformio.ini
│
├── backend/
│   ├── app.py
│   ├── requirements.txt
│   └── data/
│       └── weather.db          # generated locally, not committed
│
├── dashboard/
│   ├── index.html
│   ├── css/
│   │   └── style.css
│   └── js/
│       └── app.js
│
├── docs/
│   ├── architecture.md
│   └── wiring.md
│
├── .env.example
├── .gitignore
├── LICENSE
└── README.md
```

## MQTT

The ESP32 publishes telemetry to:

```
iot/sensing_node/data
```

Example payload:

```json
{
  "device_id": "ESP32_WEATHER_01",
  "temperature": 28.98,
  "humidity": 89.91,
  "pressure": 1008.11,
  "gas_resistance": 117.60,
  "rain_raw": 4095,
  "rain_voltage": 3.300,
  "rain_status": "NO_RAIN"
}
```

## ESP32 Setup

The firmware is written for the Arduino framework and can be built with PlatformIO.

1. Open `firmware/src/main.cpp`.
2. Set your Wi-Fi SSID and password.
3. Set the IP address of the machine running Mosquitto.
4. Verify the BME680 and rain-sensor wiring.
5. Build and upload to the ESP32.

Example:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* MQTT_BROKER = "YOUR_MQTT_BROKER_IP";
```

**Do not commit real Wi-Fi passwords or private credentials.**

## Backend Setup

From the repository root:

```bash
cd backend

python3 -m venv venv
source venv/bin/activate

pip install -r requirements.txt
```

Start Mosquitto separately:

```bash
mosquitto -v
```

Then start the Flask backend:

```python
python app.py
```

The backend exposes:

| Endpoint | Purpose |
|---|---|
| `/` | Web dashboard |
| `/health` | Backend health check |
| `/api/weather` | Latest weather reading |
| `/api/history` | Recent weather history |

## Test the Backend

Health:

```bash
curl http://127.0.0.1:5000/health
```

Latest sensor data:

```bash
curl http://127.0.0.1:5000/api/weather
```

History:

```bash
curl http://127.0.0.1:5000/api/history
```

## Dashboard

Once Flask is running, open:

```
http://localhost:5000
```

The dashboard reads the latest data from `/api/weather` and refreshes automatically.

## Data Pipeline

```
Sensors
  ↓
ESP32
  ↓
Wi-Fi
  ↓
MQTT
  ↓
Mosquitto
  ↓
Paho MQTT Client
  ↓
SQLite
  ↓
Flask REST API
  ↓
HTML / CSS / JavaScript Dashboard
```

## Development Notes

The SQLite database is generated locally at:

```
backend/data/weather.db
```

It is intentionally excluded from Git because sensor telemetry is runtime data.

## Future Improvements

- [ ] Historical charts
- [ ] CSV data export
- [ ] Weather-data analytics
- [ ] Sensor calibration interface
- [ ] MQTT authentication/TLS
- [ ] User authentication
- [ ] Docker deployment
- [ ] Mobile-responsive PWA
- [ ] Additional wind/light sensors
- [ ] Weather forecasting module

## License

This project is released under the MIT License.

## Author

**Jyotipriya Sarkar**

Embedded Systems • IoT • Edge Computing • Electronics Engineering
