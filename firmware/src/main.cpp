#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Adafruit_BME680.h>

// ============================================================
// USER CONFIGURATION
// ============================================================

const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* MQTT_BROKER = "YOUR_MQTT_BROKER_IP";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "iot/sensing_node/data";
const char* DEVICE_ID = "ESP32_WEATHER_01";

// BME680 SPI
#define BME_CS   5
#define BME_SCK  18
#define BME_MISO 19
#define BME_MOSI 23

// Rain sensor analog output
#define RAIN_PIN 34

WiFiClient espClient;
PubSubClient mqttClient(espClient);
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

unsigned long lastReading = 0;
const unsigned long READING_INTERVAL = 5000;

// ============================================================
// WIFI
// ============================================================

void connectWiFi() {
    Serial.print("Connecting to WiFi");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

// ============================================================
// MQTT
// ============================================================

void connectMQTT() {
    while (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");

        if (mqttClient.connect(DEVICE_ID)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.println(mqttClient.state());
            delay(2000);
        }
    }
}

// ============================================================
// SETUP
// ============================================================

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("==============================");
    Serial.println("ESP32 Weather Monitoring Node");
    Serial.println("==============================");

    pinMode(RAIN_PIN, INPUT);

    connectWiFi();

    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);

    Serial.println("Initializing BME680...");

    if (!bme.begin()) {
        Serial.println("ERROR: BME680 not detected!");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("BME680 detected!");

    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);

    Serial.println("Sensor configuration complete");
}

// ============================================================
// LOOP
// ============================================================

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
    }

    if (!mqttClient.connected()) {
        connectMQTT();
    }

    mqttClient.loop();

    if (millis() - lastReading < READING_INTERVAL) {
        return;
    }

    lastReading = millis();

    if (!bme.performReading()) {
        Serial.println("ERROR: BME680 reading failed!");
        return;
    }

    float temperature = bme.temperature;
    float humidity = bme.humidity;
    float pressure = bme.pressure / 100.0F;
    float gasResistance = bme.gas_resistance / 1000.0F;

    int rainRaw = analogRead(RAIN_PIN);
    float rainVoltage = (rainRaw / 4095.0F) * 3.3F;

    String rainStatus;

    if (rainRaw < 1500) {
        rainStatus = "RAIN";
    } else {
        rainStatus = "NO_RAIN";
    }

    String payload = "{";
    payload += "\"device_id\":\"" + String(DEVICE_ID) + "\",";
    payload += "\"temperature\":" + String(temperature, 2) + ",";
    payload += "\"humidity\":" + String(humidity, 2) + ",";
    payload += "\"pressure\":" + String(pressure, 2) + ",";
    payload += "\"gas_resistance\":" + String(gasResistance, 2) + ",";
    payload += "\"rain_raw\":" + String(rainRaw) + ",";
    payload += "\"rain_voltage\":" + String(rainVoltage, 3) + ",";
    payload += "\"rain_status\":\"" + rainStatus + "\"";
    payload += "}";

    bool success = mqttClient.publish(MQTT_TOPIC, payload.c_str());

    Serial.println();
    Serial.println("========== SENSOR DATA ==========");
    Serial.printf("Temperature: %.2f °C\n", temperature);
    Serial.printf("Humidity: %.2f %%\n", humidity);
    Serial.printf("Pressure: %.2f hPa\n", pressure);
    Serial.printf("Gas Resistance: %.2f kΩ\n", gasResistance);
    Serial.printf("Rain ADC: %d\n", rainRaw);
    Serial.printf("Rain Voltage: %.3f V\n", rainVoltage);
    Serial.print("Rain Status: ");
    Serial.println(rainStatus);
    Serial.print("MQTT: ");
    Serial.println(success ? "Published" : "Publish FAILED");
    Serial.println("=================================");
}
