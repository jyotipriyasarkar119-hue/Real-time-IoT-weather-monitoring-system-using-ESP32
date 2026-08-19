#ifndef WEATHER_STATION_CONFIG_H
#define WEATHER_STATION_CONFIG_H

/*
 * ============================================================
 * Real-Time IoT Weather Monitoring System
 * ESP32 + Blynk IoT
 *
 * File:
 *     config.example.h
 *
 * Purpose:
 *     Public configuration template.
 *
 * IMPORTANT:
 *     Copy this file to:
 *
 *     config.h
 *
 *     and replace the placeholder values with your
 *     actual Wi-Fi and Blynk credentials.
 *
 *     DO NOT commit config.h to GitHub.
 * ============================================================
 */


// ============================================================
// BLYNK IoT CONFIGURATION
// ============================================================

#define BLYNK_TEMPLATE_ID   "YOUR_BLYNK_TEMPLATE_ID"

#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"

#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"


// ============================================================
// WI-FI CONFIGURATION
// ============================================================

#define WIFI_SSID           "YOUR_WIFI_SSID"

#define WIFI_PASSWORD       "YOUR_WIFI_PASSWORD"


// ============================================================
// SENSOR CONFIGURATION
// ============================================================

// ------------------------------------------------------------
// DHT Sensor
// ------------------------------------------------------------

// ESP32 GPIO connected to the DHT data pin
#define DHT_PIN             4

// Select the sensor type:
//
// DHT11
// DHT22
//
#define DHT_TYPE            DHT11


// ------------------------------------------------------------
// BMP280
// ------------------------------------------------------------

// Common I2C addresses:
// 0x76
// 0x77
//
#define BMP280_I2C_ADDRESS  0x76


// ============================================================
// BLYNK VIRTUAL PIN CONFIGURATION
// ============================================================
//
// These must match the Datastreams configured in Blynk IoT.
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
// 5000 milliseconds = 5 seconds
//

#define SENSOR_UPDATE_INTERVAL 5000L


// ============================================================
// SERIAL MONITOR
// ============================================================

#define SERIAL_BAUD_RATE 115200


#endif // WEATHER_STATION_CONFIG_H
