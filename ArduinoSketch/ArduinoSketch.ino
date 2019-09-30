#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define WIFI_SSID ""
#define WIFI_PASS ""

fauxmoESP fauxmo;

#define SERIAL_BAUDRATE 115200

#define LightRly 4
#define CompFillRly 5
#define CompEmptyRly 12

#define ID_LightRly "Shop Lights"
#define ID_CompFillRly "Fill Compressor"
#define ID_CompEmptyRly "Empty Compressor"

void setup() {

  // Init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.println();

  // PIN modes
  pinMode(LightRly, OUTPUT);
  pinMode(CompFillRly, OUTPUT);
  pinMode(CompEmptyRly, OUTPUT);

  // Default all to OFF
  digitalWrite(LightRly, LOW);
  digitalWrite(CompFillRly, LOW);
  digitalWrite(CompEmptyRly, LOW);

  // Wifi
  wifiSetup();

  fauxmo.setPort(80); // This is required for gen3 devices

  fauxmo.enable(true);

  // Add virtual devices
  fauxmo.addDevice(ID_LightRly);
  fauxmo.addDevice(ID_CompFillRly);
  fauxmo.addDevice(ID_CompEmptyRly);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
    // Otherwise comparing the device_name is safer.

    if (strcmp(device_name, "Shop Lights") == 0) {
      digitalWrite(LightRly, state ? HIGH : LOW);
    }

    if (strcmp(device_name, "Fill Compressor") == 0) {
      digitalWrite(CompFillRly, state ? HIGH : LOW);
    }

    if (strcmp(device_name, "Empty Compressor") == 0) {
      digitalWrite(CompEmptyRly, state ? HIGH : LOW);
    }
  });
}

void loop() {
  fauxmo.handle();
}

// Functions
void wifiSetup() {

  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
