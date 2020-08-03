#include "PlantManager.hpp"

PlantManager::PlantManager(const uint8_t fanPin, MqttClient & client, const uint8_t moisturePin, const unsigned int updatePeriod):
	fanPin(fanPin),
	moisturePin(moisturePin),
	client(client),
	updatePeriod(updatePeriod)
{}

void PlantManager::begin(){
	pinMode(fanPin, OUTPUT);
	pinMode(moisturePin, INPUT);
}

void PlantManager::operator()(){
	if(analogRead(moisturePin) < 500){
		// Plants should be watered.
	}
	if(millis() - lastUpdate > updatePeriod){
		client.sendMessage("/kas/grondvochtigheid", String(analogRead(moisturePin)).c_str());
		lastUpdate = millis();
	}
}