# IoT-Soilless-Hydroponic-System
Smart farming prototype: ESP8266 collects sensor data, Raspberry Pi processes and visualizes it with MQTT and Node-RED dashboard.

# IoT Soilless Farming (Hydroponics) Monitoring System

This project is a smart hydroponics monitoring prototype using MQTT and Node-RED. It combines a Raspberry Pi, ESP8266, DHT11, and a DFRobot Capacitive Soil Moisture Sensor v2 to monitor temperature, humidity, and moisture levels in real-time. The data is visualized on a live Node-RED dashboard, and all communication happens via MQTT using a lightweight publish-subscribe model.

---

## System Overview

- **ESP8266**: Collects sensor data and publishes it over MQTT.
- **DHT11**: Measures **temperature** and **humidity**.
- **DFRobot Capacitive Moisture Sensor v2**: Measures **soil moisture**.
- **Raspberry Pi 4**: 
  - Runs the **MQTT broker** (`mosquitto`).
  - Hosts the **Node-RED server** for data visualization.
- **Node-RED Dashboard**: Displays gauges for temperature, humidity, and moisture in a web UI.
- **Mobile Hotspot**: Used for portability during live demos.

---

## MQTT Pub-Sub Architecture

- **ESP8266** publishes sensor data to topic `sensor/dht11`.
- **Raspberry Pi** (running Node-RED) subscribes to the topic and parses the payload.
- The data is extracted into separate values and visualized via gauges.

---

## Node-RED Dashboard Features

- Real-time gauges for:
  - Temperature
  - Humidity
  - Moisture
- All gauges shown on a single dashboard panel.
- MQTT communication ensures low-latency updates.

---

## Getting Started

### Hardware Requirements

- Raspberry Pi 4 with Wi-Fi
- ESP8266 (NodeMCU or similar)
- DHT11 Sensor
- DFRobot Capacitive Moisture Sensor v2
- Jumper wires
- Power source
- Internet connection or mobile hotspot

---

### Software Requirements

- PlatformIO or Arduino IDE
- Node-RED
- Mosquitto MQTT Broker
- Wi-Fi hotspot (SSID: `RupHotPot`)

---

## Installation Steps

### On ESP8266

1. Flash this firmware using PlatformIO:
   ```cpp
   // include code to publish DHT and moisture to sensor/dht11
   ```
2. Connect sensors:
   - DHT11 → D4
   - Moisture sensor → A0

### On Raspberry Pi

1. Connect Raspberry Pi to mobile hotspot.
2. Install MQTT Broker:
   ```bash
   sudo apt install mosquitto mosquitto-clients
   ```
3. Start Node-RED:
   ```bash
   node-red-start
   ```
4. Open Node-RED UI:  
   http://<your-raspi-ip>:1880

5. Import the provided Node-RED flow for gauges.

---

## Testing

You can test MQTT data with:
```bash
mosquitto_sub -t sensor/dht11 -v
```

Expected output:
```json
{"temperature": 24.5, "humidity": 38, "moisture": 92}
```

---



## Future Improvements

- Add water level sensors
- Control pump via relay based on moisture
- Deploy to cloud dashboard (e.g., ThingsBoard, Blynk)
- Add logging or data history

---

## Credits

- Designed and implemented by: **[Your Name]**
- Tampere University Embedded IoT Project

---

## License

This project is open-source. Feel free to use, fork, and improve!
