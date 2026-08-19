/*
 * ============================================================
 * ESP32 Real-Time IoT Weather Monitoring System
 * Sensor Implementation
 * ============================================================
 *
 * File:
 *     sensors.cpp
 *
 * Purpose:
 *     Implements sensor initialization, sensor reading,
 *     and sensor validation for the ESP32 weather station.
 *
 * ============================================================
 */

#include "sensors.h"
#include "../config/config.h"

// ============================================================
// SENSOR LIBRARIES
// ============================================================

#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>


// ============================================================
// SENSOR CONFIGURATION
// ============================================================
//
// These values should match your actual hardware.
//
// If they are already defined in config.h, do not define
// them again here.
//

#ifndef DHT_PIN
#define DHT_PIN 4
#endif

#ifndef DHT_TYPE
#define DHT_TYPE DHT11
#endif

#ifndef BMP280_I2C_ADDRESS
#define BMP280_I2C_ADDRESS 0x76
#endif


// ============================================================
// SENSOR OBJECTS
// ============================================================

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_BMP280 bmp;


// ============================================================
// INTERNAL SENSOR STATUS
// ============================================================

static bool dhtInitialized = false;
static bool bmpInitialized = false;


// ============================================================
// FUNCTION: initializeSensors()
// ============================================================

bool initializeSensors()
{
    Serial.println();
    Serial.println("Initializing weather sensors...");

    bool initializationSuccessful = true;


    // --------------------------------------------------------
    // Initialize DHT Sensor
    // --------------------------------------------------------

    dht.begin();

    delay(1000);

    dhtInitialized = true;

    Serial.println("DHT sensor initialized.");


    // --------------------------------------------------------
    // Initialize BMP280
    // --------------------------------------------------------

    if (bmp.begin(BMP280_I2C_ADDRESS))
    {
        bmpInitialized = true;

        Serial.println("BMP280 initialized.");
    }
    else
    {
        bmpInitialized = false;
        initializationSuccessful = false;

        Serial.println("ERROR: BMP280 initialization failed.");
    }


    // --------------------------------------------------------
    // Sensor Initialization Result
    // --------------------------------------------------------

    if (initializationSuccessful)
    {
        Serial.println("All sensors initialized successfully.");
    }
    else
    {
        Serial.println("One or more sensors failed to initialize.");
    }

    return initializationSuccessful;
}


// ============================================================
// FUNCTION: readTemperature()
// ============================================================

float readTemperature()
{
    if (!dhtInitialized)
    {
        Serial.println("DHT sensor is not initialized.");
        return NAN;
    }

    float temperature = dht.readTemperature();

    if (isnan(temperature))
    {
        Serial.println("ERROR: Failed to read temperature.");
        return NAN;
    }

    return temperature;
}


// ============================================================
// FUNCTION: readHumidity()
// ============================================================

float readHumidity()
{
    if (!dhtInitialized)
    {
        Serial.println("DHT sensor is not initialized.");
        return NAN;
    }

    float humidity = dht.readHumidity();

    if (isnan(humidity))
    {
        Serial.println("ERROR: Failed to read humidity.");
        return NAN;
    }

    return humidity;
}


// ============================================================
// FUNCTION: readPressure()
// ============================================================

float readPressure()
{
    if (!bmpInitialized)
    {
        Serial.println("BMP280 is not initialized.");
        return NAN;
    }

    /*
     * BMP280 returns pressure in Pascals.
     *
     * Convert:
     *
     *     Pa → hPa
     *
     * by dividing by 100.
     */

    float pressure = bmp.readPressure() / 100.0F;

    if (isnan(pressure))
    {
        Serial.println("ERROR: Failed to read pressure.");
        return NAN;
    }

    return pressure;
}


// ============================================================
// FUNCTION: readSensors()
// ============================================================

bool readSensors(WeatherData &data)
{
    /*
     * Read all weather parameters.
     */

    data.temperature = readTemperature();

    data.humidity = readHumidity();

    data.pressure = readPressure();


    /*
     * Validate the collected measurements.
     */

    if (!validateSensorData(data))
    {
        return false;
    }

    return true;
}


// ============================================================
// FUNCTION: validateSensorData()
// ============================================================

bool validateSensorData(const WeatherData &data)
{
    /*
     * Check for invalid sensor readings.
     */

    if (isnan(data.temperature))
    {
        return false;
    }

    if (isnan(data.humidity))
    {
        return false;
    }

    if (isnan(data.pressure))
    {
        return false;
    }


    /*
     * Basic physical range checks.
     */

    if (data.humidity < 0.0 || data.humidity > 100.0)
    {
        Serial.println("ERROR: Invalid humidity value.");
        return false;
    }


    /*
     * Temperature range check.
     *
     * This is intentionally broad because the system may
     * eventually be deployed outdoors.
     */

    if (data.temperature < -50.0 || data.temperature > 80.0)
    {
        Serial.println("ERROR: Invalid temperature value.");
        return false;
    }


    /*
     * Atmospheric pressure range.
     *
     * Approximate atmospheric range in hPa.
     */

    if (data.pressure < 300.0 || data.pressure > 1200.0)
    {
        Serial.println("ERROR: Invalid pressure value.");
        return false;
    }


    return true;
}
