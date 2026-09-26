# Wiring

## BME680 — SPI

| BME680 | ESP32 |
|---|---|
| CS | GPIO 5 |
| SCK | GPIO 18 |
| SDO/MISO | GPIO 19 |
| SDI/MOSI | GPIO 23 |
| VCC | 3.3V |
| GND | GND |

## Rain Sensor

| Rain Sensor | ESP32 |
|---|---|
| AO | GPIO 34 |
| VCC | 3.3V |
| GND | GND |

GPIO 34 is input-only and is used for analog rain-sensor measurements.
