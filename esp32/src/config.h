#ifndef WEATHER_STATION_CONFIG_H
#define WEATHER_STATION_CONFIG_H

/*
 * ============================================================
 * ESP32 Real-Time IoT Weather Monitoring System
 * Configuration File
 * ============================================================
 *
 * IMPORTANT:
 * This file contains private credentials.
 *
 * Do NOT commit the real config.h to GitHub.
 *
 * Use config.example.h as the public template.
 *
 * ============================================================
 */


// ============================================================
// BLYNK IoT CONFIGURATION
// ============================================================

// Blynk Template ID
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"

// Blynk Template Name
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"

// Blynk Authentication Token
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"


// ============================================================
// WI-FI CONFIGURATION
// ============================================================

// Wi-Fi network name
#define WIFI_SSID           "YOUR_WIFI_SSID"

// Wi-Fi password
#define WIFI_PASSWORD       "YOUR_WIFI_PASSWORD"


// ============================================================
// SENSOR CONFIGURATION
// ============================================================
//
// Add the GPIO definitions that are actually used by your
// Weather_Station.ino here.
//
// IMPORTANT:
// Replace the example values with the actual GPIO pins
// used by your hardware.
//

// Example:
//
// #define DHT_PIN             4
// #define DHT_TYPE            DHT11
//
// #define BMP280_I2C_ADDRESS  0x76
//
// #define LIGHT_SENSOR_PIN    34
//
// #define RAIN_SENSOR_PIN     35


// ============================================================
// BLYNK VIRTUAL PIN CONFIGURATION
// ============================================================
//
// Keep the virtual-pin mapping in one place so that the
// firmware and Blynk dashboard remain synchronized.
//

#define BLYNK_TEMP_PIN       V0
#define BLYNK_HUMIDITY_PIN   V1
#define BLYNK_PRESSURE_PIN   V2


// ============================================================
// SENSOR UPDATE INTERVAL
// ============================================================
//
// Time between sensor updates sent to Blynk.
//
// 5000 ms = 5 seconds
//

#define SENSOR_UPDATE_INTERVAL 5000L


// ============================================================
// SERIAL MONITOR
// ============================================================

#define SERIAL_BAUD_RATE 115200


#endif // WEATHER_STATION_CONFIG_H
