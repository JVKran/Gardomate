#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <forcedClimate.h>

#include "MqttClient.hpp"
#include "ClimateManager.hpp"
#include "PlantManager.hpp"

WiFiClient espClient;
MqttClient client("KraanBast2.4", "Snip238!", "192.168.178.81", "/raspberrypi/hassio", espClient);

ForcedClimate climateSensor = ForcedClimate();
ClimateManager climateManager = ClimateManager(climateSensor, client, CLM_10MIN);
PlantManager plantManager = PlantManager(D5, client);

void callback(char* topic, byte* payload, unsigned int length) {
    static String message;
    for (int i = 0; i < length; i++) {
        message.concat((char)payload[i]);
    }
    client.notifyListeners(message, topic);
    message = "";  
}

void setup(){
	Wire.begin();
	Serial.begin(115200);

	climateSensor.begin();
	plantManager.begin();

	client.setupWifi();
    client.setupConnections();

    climateSensor.takeForcedMeasurement();
    Serial.print("Temperature: ");
	Serial.print(climateSensor.getTemperatureCelcius());
	Serial.print(", Humidity: ");
	Serial.print(climateSensor.getRelativeHumidity());
	Serial.print(" and Pressure: ");
	Serial.print(climateSensor.getPressure());
	Serial.println();
}

void loop(){
	client();               // Handle incoming messages
	climateManager();
	plantManager();
}
