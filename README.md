# ESP32 Weather Station with Blynk

A real-time IoT weather monitoring system built with an ESP32, DHT11 temperature/humidity sensor, and a rain sensor. Live data is pushed to the Blynk cloud dashboard every 2 seconds.

---

📸 Features

- 🌡️ **Temperature** — Real-time in °C
- 💧 **Humidity** — Relative humidity in %
- 🌧️ **Rain Intensity** — 0–100% wetness level
- 🏷️ **Rain Status** — No Rain / Light Rain / Moderate Rain / Heavy Rain
- 🌡️ **Feels Like** — Heat index combining temperature and humidity
- 💦 **Dew Point** — Atmospheric dew point in °C
- 🌤️ **Weather Summary** — Smart condition label (Stormy, Rainy, Hot & Humid, Normal, etc.)
- 📊 **Historical Chart** — Live graph of temperature, humidity, and rain over time

---

🛠️ Hardware Required

| Component | Quantity |
|---|---|
| ESP32 Development Board | 1 |
| DHT11 Temperature & Humidity Sensor | 1 |
| Rain / Moisture Sensor Module | 1 |
| Jumper Wires | As needed |
| USB Cable (for programming) | 1 |

---

🔌 Wiring

### DHT11 Sensor
| DHT11 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 4 |

### Rain Sensor Module
| Rain Sensor Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| AO (Analog Out) | GPIO 34 |

> **Note:** GPIO 34 on the ESP32 is input-only, which makes it ideal for analog sensor reading.

---

📦 Libraries Required

Install these libraries via **Arduino IDE → Library Manager**:

| Library | Purpose |
|---|---|
| `Blynk` | Blynk IoT cloud connectivity |
| `DHT sensor library` by Adafruit | DHT11 sensor reading |
| `Adafruit Unified Sensor` | Dependency for DHT library |
| `WiFi` | Built-in ESP32 WiFi (no install needed) |

---

⚙️ Setup & Configuration

### 1. Clone the Repository

```bash
git clone https://github.com/ANKAN-22/Weather-Station.git
cd Weather-Station
```

### 2. Configure Credentials

Open `weather_station.ino` and update these lines with your details:

```cpp
#define BLYNK_TEMPLATE_ID   "your_template_id"
#define BLYNK_TEMPLATE_NAME "Weather Station"
#define BLYNK_AUTH_TOKEN    "your_auth_token"

char ssid[] = "your_wifi_ssid";
char pass[] = "your_wifi_password";
```

### 3. Upload to ESP32

- Open the `.ino` file in Arduino IDE
- Select **Tools → Board → ESP32 Dev Module**
- Select the correct **COM Port**
- Click **Upload**

---

📱 Blynk Dashboard Setup

### Step 1 — Datastreams

Go to **Blynk Console → Templates → Weather Station → Datastreams** and create:

| Name | Virtual Pin | Data Type | Min | Max | Unit |
|---|---|---|---|---|---|
| Temperature | V0 | Double | 0 | 60 | °C |
| Humidity | V1 | Double | 0 | 100 | % |
| Rain Intensity | V2 | Integer | 0 | 100 | % |
| Rain Status | V3 | String | — | — | — |
| Feels Like | V4 | Double | 0 | 60 | °C |
| Dew Point | V5 | Double | 0 | 40 | °C |
| Weather Summary | V6 | String | — | — | — |

### Step 2 — Widgets

| Widget Type | Datastream | Label |
|---|---|---|
| Gauge | V0 | Temperature (°C) |
| Gauge | V1 | Humidity (%) |
| Gauge | V2 | Rain Intensity (%) |
| Label | V3 | Rain Status |
| Gauge | V4 | Feels Like (°C) |
| Gauge | V5 | Dew Point (°C) |
| Label | V6 | Weather Summary |
| Chart | V0, V1, V2 | Weather History |

---

🌧️ Rain Sensor Logic

The rain sensor outputs an analog value from 0 to 4095:

| Raw Value | Rain Status | Rain Intensity |
|---|---|---|
| 3500 – 4095 | No Rain | 0 – 14% |
| 2000 – 3500 | Light Rain | 15 – 51% |
| 1000 – 2000 | Moderate Rain | 52 – 75% |
| 0 – 1000 | Heavy Rain | 76 – 100% |

> More water on the sensor = lower raw value = higher rain intensity percentage.

---

🌤️ Weather Summary Conditions

| Condition | Trigger |
|---|---|
| Stormy | Rain sensor < 1000 |
| Rainy | Rain sensor < 2000 |
| Drizzling | Rain sensor < 3500 and humidity > 70% |
| Hot & Dry | Temp > 38°C and humidity < 40% |
| Hot & Humid | Temp > 35°C and humidity > 70% |
| Very Hot | Temp > 35°C |
| Cold | Temp < 15°C |
| Cool & Pleasant | Temp < 20°C |
| Humid & Cloudy | Humidity > 80% |
| Dry & Clear | Humidity < 30% |
| Normal | All other conditions |

---

📟 Serial Monitor Output

When running, the Serial Monitor (115200 baud) displays:

```
------ SENSOR DATA ------
Temperature    : 31.80 °C
Humidity       : 67.00 %
Feels Like     : 34.20 °C
Dew Point      : 24.60 °C
Rain Intensity : 56 %
Rain Status    : Moderate Rain
Weather Summary: Rainy
-------------------------
```

---

📁 Project Structure

```
Weather-Station/
│
├── code/
│   └── weather_station.ino     # Main Arduino sketch
├── README.md                   # Project documentation
└── LICENSE                     # MIT License
```

---

🔧 Troubleshooting

| Problem | Fix |
|---|---|
| DHT11 Sensor Error in Serial | Check wiring on GPIO 4 |
| Device offline on Blynk | Verify WiFi credentials |
| Rain gauge shows 0–1 | Fix V2 datastream range to 0–100 |
| Rain Status label blank | Ensure V3 datastream type is String |
| No data on widgets | Check virtual pin numbers match V0–V6 |
| Upload fails | Select correct board and COM port in Arduino IDE |

---

🚀 Future Improvements

- [ ] Rain alarm notification (Blynk push alert on heavy rain)
- [ ] BMP280 pressure sensor for weather forecasting
- [ ] LDR light sensor for day/night detection
- [ ] Wind speed sensor (anemometer)
- [ ] Deep sleep mode for battery-powered operation

---

📄 License

This project is open source and available under the MIT License.

---

🙌 Acknowledgements

- [Blynk IoT Platform](https://blynk.io)
- [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
