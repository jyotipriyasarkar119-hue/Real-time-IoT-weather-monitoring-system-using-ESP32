#ifndef WEATHER_STATION_SENSORS_H
#define WEATHER_STATION_SENSORS_H

/*
 * ============================================================
 * ESP32 Real-Time IoT Weather Monitoring System
 * Sensor Interface
 * ============================================================
 *
 * File:
 *     sensors.h
 *
 * Purpose:
 *     Defines the interface used by the main firmware to
 *     initialize and read the weather sensors.
 *
 * Responsibilities:
 *     - Sensor initialization
 *     - Sensor data acquisition
 *     - Sensor value storage
 *     - Sensor validation
 *
 * ============================================================
 */


// ============================================================
// WEATHER DATA STRUCTURE
// ============================================================

struct WeatherData
{
    float temperature;
    float humidity;
    float pressure;

    // Add additional parameters if your project uses them.
    //
    // float rainfall;
    // float lightIntensity;
    // float windSpeed;
};


// ============================================================
// SENSOR INITIALIZATION
// ============================================================

/*
 * Initialize all connected sensors.
 *
 * Returns:
 *     true  → sensors initialized successfully
 *     false → one or more sensors failed
 */
bool initializeSensors();


// ============================================================
// SENSOR DATA ACQUISITION
// ============================================================

/*
 * Read all connected sensors.
 *
 * The function updates the WeatherData structure.
 */
bool readSensors(WeatherData &data);


// ============================================================
// INDIVIDUAL SENSOR FUNCTIONS
// ============================================================

/*
 * Read temperature.
 */
float readTemperature();


/*
 * Read relative humidity.
 */
float readHumidity();


/*
 * Read atmospheric pressure.
 */
float readPressure();


// ============================================================
// SENSOR VALIDATION
// ============================================================

/*
 * Check whether the collected sensor values are valid.
 */
bool validateSensorData(const WeatherData &data);


#endif // WEATHER_STATION_SENSORS_H
