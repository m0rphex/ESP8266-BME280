#include <Wire.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

unsigned long myChannelNumber = 156985;
const char * myWriteAPIKey = "C545VVIFK0XDELQF";
const char* ssid = "Tomato24";
const char* password = "tonttu1234";

const char* server = "api.thingspeak.com";  
WiFiClient client;

Adafruit_BME280 bme; // I2C

void setup() {  
  Wire.begin(0, 2);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  ThingSpeak.begin(client);
}

void loop() {  
  float t = bme.readTemperature();
  float p = bme.readPressure();
  float h = bme.readHumidity();


  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" degrees Celcius Pressure: ");
  Serial.print(p);
  Serial.print(" Humidity: ");
  Serial.print(h);
  Serial.println("% send to Thingspeak");
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, p);
  ThingSpeak.setField(3, h);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(20000);
}
