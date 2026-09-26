# System Architecture

ESP32 reads the BME680 and rain sensor and publishes JSON telemetry over MQTT.

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
   Flask MQTT Client
        |
        +----> SQLite
        |
        v
     Flask API
        |
        v
     Dashboard
```

## MQTT topic

`iot/sensing_node/data`

## Payload

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
