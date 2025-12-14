#include <WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

const char* ssid = "IobiT Solutions";        
const char* password = "IobiT@2025"; 

unsigned long myChannelNumber = 3103846;    
const char* myWriteAPIKey = "67RUXUSMKKNURW8T";  

WiFiClient client;

#define DHTPIN 23
#define DHTTYPE DHT11
#define SOIL_PIN 34
#define RELAY_PIN 2

const int soilDry = 3800;  // Raw analog reading for dry soil
const int soilWet = 1200;  // Raw analog reading for wet soil

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

int moistureThreshold = 40;  // Below 40% → relay ON

unsigned long lastThingSpeak = 0;
const long uploadInterval = 20000; // 20 sec minimum interval

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(SOIL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Relay OFF initially

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Smart Irrigation Init...");
  display.display();
  delay(2000);

  Serial.print("Connecting to WiFi");
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("Connecting to WiFi...");
  display.display();

  WiFi.begin(ssid, password);
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("WiFi Connected!");
    display.display();
  } else {
    Serial.println("\nWiFi Failed!");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("WiFi Failed!");
    display.display();
  }

  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilValue = analogRead(SOIL_PIN);

  float moisturePercent = (float)(soilValue - soilDry) / (soilWet - soilDry) * 100.0;
  moisturePercent = constrain(moisturePercent, 0, 100);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temp: "); Serial.print(temperature);
    Serial.print(" C | Humi: "); Serial.print(humidity);
    Serial.print(" % | Soil: "); Serial.print(moisturePercent); Serial.println(" %");
  }

  if (moisturePercent < moistureThreshold) {
    digitalWrite(RELAY_PIN, HIGH);  // Pump ON
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Pump OFF
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Smart Irrigation");
  display.setCursor(0, 16);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.setCursor(0, 28);
  display.print("Humi: "); display.print(humidity); display.println(" %");
  display.setCursor(0, 40);
  display.print("Soil: "); display.print(moisturePercent); display.println(" %");
  display.setCursor(0, 52);
  display.print("Relay: "); display.println(moisturePercent < moistureThreshold ? "ON" : "OFF");
  display.display();

  if (millis() - lastThingSpeak >= uploadInterval) {
    lastThingSpeak = millis();

    if (WiFi.status() == WL_CONNECTED) {
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      ThingSpeak.setField(3, moisturePercent);

      int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      if (statusCode == 200) {
        Serial.println("ThingSpeak update success!");
      } else {
        Serial.print("ThingSpeak error: "); Serial.println(statusCode);
      }
    } else {
      Serial.println("WiFi disconnected. Reconnecting...");
      WiFi.reconnect();
    }
  }

  delay(1000); 
}
