from flask import Flask, jsonify, send_from_directory
from flask_cors import CORS
import sqlite3
import json
import os
import threading
from datetime import datetime
import paho.mqtt.client as mqtt

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DATABASE = os.path.join(BASE_DIR, "data", "weather.db")

MQTT_BROKER = os.getenv("MQTT_BROKER", "127.0.0.1")
MQTT_PORT = int(os.getenv("MQTT_PORT", "1883"))
MQTT_TOPIC = os.getenv("MQTT_TOPIC", "iot/sensing_node/data")

DASHBOARD_DIR = os.path.abspath(os.path.join(BASE_DIR, "..", "dashboard"))

app = Flask(__name__, static_folder=DASHBOARD_DIR, static_url_path="")
CORS(app)

def init_database():
    os.makedirs(os.path.dirname(DATABASE), exist_ok=True)
    conn = sqlite3.connect(DATABASE)
    conn.execute("""
        CREATE TABLE IF NOT EXISTS weather_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            device_id TEXT,
            temperature REAL,
            humidity REAL,
            pressure REAL,
            gas_resistance REAL,
            rain_raw INTEGER,
            rain_voltage REAL,
            rain_status TEXT,
            timestamp TEXT
        )
    """)
    conn.commit()
    conn.close()

def save_weather(data):
    conn = sqlite3.connect(DATABASE)
    conn.execute("""
        INSERT INTO weather_data (
            device_id, temperature, humidity, pressure,
            gas_resistance, rain_raw, rain_voltage,
            rain_status, timestamp
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
    """, (
        data.get("device_id"),
        data.get("temperature"),
        data.get("humidity"),
        data.get("pressure"),
        data.get("gas_resistance"),
        data.get("rain_raw"),
        data.get("rain_voltage"),
        data.get("rain_status"),
        datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    ))
    conn.commit()
    conn.close()

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("MQTT connected")
        client.subscribe(MQTT_TOPIC)
        print(f"Subscribed: {MQTT_TOPIC}")
    else:
        print(f"MQTT connection failed, rc={rc}")

def on_message(client, userdata, message):
    try:
        data = json.loads(message.payload.decode("utf-8"))
        print("\n========== MQTT DATA ==========")
        print(json.dumps(data, indent=2))
        save_weather(data)
        print("Database: SAVED")
    except json.JSONDecodeError:
        print("Invalid JSON received from MQTT")
    except Exception as exc:
        print(f"Database/message error: {exc}")

def mqtt_thread():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1, client_id="weather_dashboard_backend")
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_forever()

@app.route("/")
def dashboard():
    return send_from_directory(DASHBOARD_DIR, "index.html")

@app.route("/api/weather")
def latest_weather():
    try:
        conn = sqlite3.connect(DATABASE)
        conn.row_factory = sqlite3.Row
        row = conn.execute("""
            SELECT device_id, temperature, humidity, pressure,
                   gas_resistance, rain_raw, rain_voltage,
                   rain_status, timestamp
            FROM weather_data
            ORDER BY id DESC LIMIT 1
        """).fetchone()
        conn.close()

        if row is None:
            return jsonify({
                "status": "no_data",
                "message": "Waiting for ESP32 weather data."
            })

        return jsonify({
            "status": "success",
            **dict(row)
        })
    except Exception as exc:
        return jsonify({"status": "error", "message": str(exc)}), 500

@app.route("/api/history")
def history():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    rows = conn.execute("""
        SELECT device_id, temperature, humidity, pressure,
               gas_resistance, rain_raw, rain_voltage,
               rain_status, timestamp
        FROM weather_data
        ORDER BY id DESC LIMIT 100
    """).fetchall()
    conn.close()
    return jsonify([dict(row) for row in rows])

@app.route("/health")
def health():
    return jsonify({
        "status": "running",
        "service": "Weather Monitoring System",
        "mqtt_broker": MQTT_BROKER,
        "mqtt_port": MQTT_PORT,
        "mqtt_topic": MQTT_TOPIC
    })

if __name__ == "__main__":
    init_database()

    thread = threading.Thread(target=mqtt_thread, daemon=True)
    thread.start()

    host = os.getenv("FLASK_HOST", "0.0.0.0")
    port = int(os.getenv("FLASK_PORT", "5000"))

    print("========================================")
    print("     ESP32 WEATHER MONITORING SYSTEM")
    print("========================================")
    print(f"MQTT: {MQTT_BROKER}:{MQTT_PORT}")
    print(f"Topic: {MQTT_TOPIC}")
    print(f"Dashboard: http://localhost:{port}")
    print("========================================")

    app.run(host=host, port=port, debug=False, use_reloader=False)
