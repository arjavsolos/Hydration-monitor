#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char* ssid     = "";
const char* password = "";

String API_URL   = "";
String API_KEY   = "";
String TableName = "Sigma%20GSR";

#define GSR_PIN   36
#define ADC_MAX   4095.0
#define V_REF     3.3
#define V_SUPPLY  3.3
#define R_FIXED   100000.0

int sendinginterval = 10;
WiFiClientSecure client;
HTTPClient https;

void setup() {
  Serial.begin(115200);
  delay(500);
  client.setInsecure();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int adcValue = analogRead(GSR_PIN);
  float voltage = (adcValue / ADC_MAX) * V_REF;
  if (voltage >= V_SUPPLY) voltage = V_SUPPLY - 0.0001;
  float sensorResistance = R_FIXED * (voltage / (V_SUPPLY - voltage));
  float conductance_uS = (1.0 / sensorResistance) * 1e6;

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | R_skin: ");
  Serial.print(sensorResistance, 1);
  Serial.print(" ohms | GSR: ");
  Serial.print(conductance_uS, 2);
  Serial.println(" µS");

  https.begin(client, API_URL + "/rest/v1/" + TableName);
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Prefer", "return=representation");
  https.addHeader("apikey", API_KEY);
  https.addHeader("Authorization", "Bearer " + API_KEY);

  String jsonBody = "{\"GSR\":" + String(conductance_uS, 2) + "}";
  int httpCode = https.POST(jsonBody);
  String payload = https.getString();

  Serial.print("HTTP Code: ");
  Serial.println(httpCode);
  Serial.print("Response: ");
  Serial.println(payload);

  https.end();
  delay(sendinginterval * 1000L);
}
