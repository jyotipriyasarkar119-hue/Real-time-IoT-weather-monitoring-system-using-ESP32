const elements = {
    status: document.getElementById("connection-status"),
    dot: document.getElementById("connection-dot"),
    device: document.getElementById("device-id"),
    temperature: document.getElementById("temperature"),
    humidity: document.getElementById("humidity"),
    pressure: document.getElementById("pressure"),
    gasResistance: document.getElementById("gas-resistance"),
    rainRaw: document.getElementById("rain-raw"),
    rainVoltage: document.getElementById("rain-voltage"),
    rainStatus: document.getElementById("rain-status"),
    timestamp: document.getElementById("timestamp")
};

function setConnection(connected) {
    elements.status.textContent = connected
        ? "Server Connected"
        : "Server Disconnected";

    elements.dot.textContent = connected ? "●" : "●";
    elements.dot.style.color = connected ? "#22c55e" : "#ef4444";
}

function showData(data) {
    elements.device.textContent = data.device_id ?? "--";
    elements.temperature.textContent = data.temperature ?? "--";
    elements.humidity.textContent = data.humidity ?? "--";
    elements.pressure.textContent = data.pressure ?? "--";
    elements.gasResistance.textContent = data.gas_resistance ?? "--";
    elements.rainRaw.textContent = data.rain_raw ?? "--";
    elements.rainVoltage.textContent = data.rain_voltage ?? "--";
    elements.rainStatus.textContent = data.rain_status ?? "--";
    elements.timestamp.textContent = data.timestamp ?? "--";
}

async function updateDashboard() {
    try {
        const response = await fetch("/api/weather", {
            cache: "no-store"
        });

        if (!response.ok) {
            throw new Error("API request failed");
        }

        const data = await response.json();
        setConnection(true);

        if (data.status === "success") {
            showData(data);
        } else {
            elements.status.textContent = "Waiting for ESP32 data";
        }
    } catch (error) {
        console.error(error);
        setConnection(false);
    }
}

updateDashboard();
setInterval(updateDashboard, 2000);
