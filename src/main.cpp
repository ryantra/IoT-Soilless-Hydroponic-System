#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN D4     // Pin where the DHT11 is connected
#define DHTTYPE DHT11  

const char* ssid = "RupHotPot";
const char* password = "6was9before";
const char* mqtt_server = "192.168.135.3";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);


void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    // Try to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("MQTT connected");
    } else {
      Serial.print("MQTT failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}
void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
  Serial.println("DHT sensor initialized");
  Serial.println("MQTT client initialized");
  Serial.println("Setup complete");
}

void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int moistureVal = analogRead(A0); // Read the moisture value from the sensor
  int moisturePercent = map(moistureVal, 0, 1023, 0, 100); // Map the value to a percentage
  moisturePercent = constrain(moisturePercent, 0, 100); // Constrain the value to be between 0 and 100
  if (!isnan(h) && !isnan(t)) {
    String payload =  "{\"temperature\": " + String(t, 1) + 
                      ", \"humidity\": " + String(h, 0) + 
                      ", \"moisture\": " + String(moisturePercent) + "}";
    Serial.println(payload);    // payload
    client.publish("sensor/dht11", payload.c_str());
  } else {
    Serial.println("Failed to read from DHT sensor!");  
  }

  delay(5000);
}