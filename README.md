# Soil Sense – Smart IoT-Based Soil Monitoring System

## Project Overview
Soil Sense is an IoT-based system designed to monitor soil moisture, temperature, and humidity in real-time. It automates irrigation based on sensor readings, helping optimize water usage for plants and crops.

---

## Components Used

### Sensors
- **Capacitive Soil Moisture Sensor V2.0** – Measures soil moisture accurately and is corrosion-resistant  
- **DHT11 Temperature & Humidity Sensor** – Measures air temperature and relative humidity  

### Microcontroller
- **ESP32 Development Board** – Built-in Wi-Fi & Bluetooth for IoT connectivity  

### Actuators
- **5V Relay Module** – Controls the water pump  
- **5V Water Pump** – Automates irrigation based on moisture readings  

### Communication
- **Built-in ESP32 Wi-Fi Module** – Transmits real-time data to ThingSpeak  

### Power Supply
- **12V Rechargeable Battery** – Provides stable power backup  

### Display
- **0.96” OLED Display** – Shows live temperature, humidity, and moisture readings  

### Enclosure & Connectors
- **PVC Enclosure** – Protects hardware  
- **Jumper Wires & Connectors** – Secure electrical connections  
- **USB Cable** – Powers/programs ESP32  

---

## Programming Platform
- **Arduino IDE** – Used for writing, compiling, and uploading code to ESP32  
- **ESP32 Board Package/Library** – Required for enabling ESP32 coding in Arduino IDE  

## Programming Language
- **C++** – Implements sensor logic, relay control, OLED output, and Wi-Fi communication  

## Cloud Platform
- **ThingSpeak IoT Analytics Platform** – For real-time data visualization, storing historical data, and generating graphs for moisture, temperature, and humidity  

## Required Libraries
- `WiFi.h` – Establishes Wi-Fi connection  
- `DHT.h` – Reads temperature & humidity sensor values  
- `Adafruit_SSD1306.h` – Controls OLED display  
- `Adafruit_GFX.h` – Graphics support for OLED  
- `ThingSpeak.h` – Sends data from ESP32 to ThingSpeak cloud  

## Communication Protocol
- **Wi-Fi Communication (via ESP32)** – Enables real-time data transmission and remote monitoring through ThingSpeak dashboard  

---

## Features
- Real-time monitoring of soil moisture, temperature, and humidity  
- Automatic irrigation control using relay and water pump  
- Live display on OLED screen  
- Data upload to ThingSpeak for visualization and analysis  

---

## How to Run
1. Connect the sensors, relay, pump, and OLED to the ESP32 as per the circuit diagram.  
2. Power the ESP32 using a 12V battery or USB cable.  
3. Open Arduino IDE and install the required libraries if not already installed.  
4. Upload `esp32_code.ino` to the ESP32.  
5. Open ThingSpeak dashboard to monitor live data.  
6. Observe real-time readings on the OLED display.  

---

## Learning Outcome
- Hands-on experience with IoT hardware and sensors  
- Embedded programming with ESP32 using C++  
- Cloud data visualization using ThingSpeak  
- Integrating automated irrigation systems with real-time sensor data  

---

## Optional Enhancements
- Integrate soil pH sensor for soil quality monitoring  
- Implement mobile app notifications for irrigation alerts  
- Add solar-powered energy supply for sustainability

---
