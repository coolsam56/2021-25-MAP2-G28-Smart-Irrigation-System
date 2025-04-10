#define BLYNK_TEMPLATE_ID "TMPL39OhMxRT5"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "iEvApRFsgPqEQEZH3wFj67_O4U7ZPk5V"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "iEvApRFsgPqEQEZH3wFj67_O4U7ZPk5V"; // Blynk Auth Token
char ssid[] = "Shahnawaz Alam"; // WiFi Network Name
char pass[] = "Sam#@7774"; // WiFi Password

int sensorPin = A0; // Soil Moisture Sensor Pin
int relayPin = D1; // Relay Pin
int threshold = 40; // Moisture threshold percentage


BLYNK_WRITE(V1) { 
  int buttonState = param.asInt();
  Serial.print("Button state: ");
  Serial.println(buttonState);
  if (buttonState == 1) {
    digitalWrite(relayPin, LOW); 
    Serial.println("Water pump turned ON");
  } else {
    digitalWrite(relayPin, HIGH);
    Serial.println("Water pump turned OFF");
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); 

  Serial.println("Setup complete. Connecting to Blynk...");
}

void loop() {
  Blynk.run();
  
  int moistureValue = analogRead(sensorPin); 
  int moisturePercentage = map(moistureValue, 1023, 0, 0, 100);
  Blynk.virtualWrite(V2, moisturePercentage);
  
  Serial.print("Raw Sensor Value: ");
  Serial.println(moistureValue);
  Serial.print("Moisture Level: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  if (moisturePercentage < threshold) {
    Blynk.logEvent("lowmoisture", "Low Moisture Detected!");
    Serial.println("Low moisture detected, alert sent.");
  }
  
  delay(1000);
}