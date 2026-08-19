#define BLYNK_TEMPLATE_ID "Your BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Your BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "Your BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "Your WiFi NAME";
char pass[] = "WiFi Password";

// DHT11 setup
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Rain sensor pin
#define SENSOR_PIN 34

BlynkTimer timer;

void sendSensor()
{
  // Read DHT11
  float temperatureC = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check DHT errors first
  if (isnan(temperatureC) || isnan(humidity))
  {
    Serial.println("DHT11 Sensor Error!");
    return;
  }

  // Read analog rain sensor
  int sensorValue = analogRead(SENSOR_PIN);

  // Map raw value to rain percentage
  int rainPercent = map(sensorValue, 4095, 0, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  // ===== FEELS LIKE (HEAT INDEX) =====
  float feelsLike = dht.computeHeatIndex(temperatureC, humidity, false);

  // ===== DEW POINT =====
  float dewPoint = temperatureC - ((100 - humidity) / 5.0);

  // ===== RAIN STATUS =====
  String rainStatus;
  if (sensorValue > 3500)
    rainStatus = "No Rain";
  else if (sensorValue > 2000)
    rainStatus = "Light Rain";
  else if (sensorValue > 1000)
    rainStatus = "Moderate Rain";
  else
    rainStatus = "Heavy Rain";

  // ===== WEATHER SUMMARY =====
  String weatherSummary;

  if (sensorValue < 1000)
    weatherSummary = "Stormy";
  else if (sensorValue < 2000)
    weatherSummary = "Rainy";
  else if (sensorValue < 3500 && humidity > 70)
    weatherSummary = "Drizzling";
  else if (temperatureC > 38 && humidity < 40)
    weatherSummary = "Hot & Dry";
  else if (temperatureC > 35 && humidity > 70)
    weatherSummary = "Hot & Humid";
  else if (temperatureC > 35)
    weatherSummary = "Very Hot";
  else if (temperatureC < 15)
    weatherSummary = "Cold";
  else if (temperatureC < 20)
    weatherSummary = "Cool & Pleasant";
  else if (humidity > 80)
    weatherSummary = "Humid & Cloudy";
  else if (humidity < 30)
    weatherSummary = "Dry & Clear";
  else
    weatherSummary = "Normal";

  // ===== SERIAL MONITOR OUTPUT =====
  Serial.println("------ SENSOR DATA ------");
  Serial.print("Temperature    : ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  Serial.print("Humidity       : ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Feels Like     : ");
  Serial.print(feelsLike);
  Serial.println(" °C");
  Serial.print("Dew Point      : ");
  Serial.print(dewPoint);
  Serial.println(" °C");
  Serial.print("Rain Intensity : ");
  Serial.print(rainPercent);
  Serial.println(" %");
  Serial.print("Rain Status    : ");
  Serial.println(rainStatus);
  Serial.print("Weather Summary: ");
  Serial.println(weatherSummary);
  Serial.println("-------------------------\n");

  // ===== SEND TO BLYNK =====
  Blynk.virtualWrite(V0, temperatureC);    // Temperature (°C)
  Blynk.virtualWrite(V1, humidity);        // Humidity (%)
  Blynk.virtualWrite(V2, rainPercent);     // Rain Intensity (%)
  Blynk.virtualWrite(V3, rainStatus);      // Rain Status
  Blynk.virtualWrite(V4, feelsLike);       // Feels Like (°C)
  Blynk.virtualWrite(V5, dewPoint);        // Dew Point (°C)
  Blynk.virtualWrite(V6, weatherSummary);  // Weather Summary
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Weather Monitoring System...");
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connected to Blynk!");
  timer.setInterval(2000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
