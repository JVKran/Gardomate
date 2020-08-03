#include "ClimateManager.hpp"

ClimateManager::ClimateManager(ForcedClimate & climateSensor, MqttClient & client, const unsigned int updatePeriod):
	climateSensor(climateSensor),
	updatePeriod(updatePeriod),
	client(client)
{}

void ClimateManager::operator()(){
	if(millis() - lastUpdate > updatePeriod){
		climateSensor.takeForcedMeasurement();
		client.sendMessage("/kas/vochtigheid", String(climateSensor.getRelativeHumidity()).c_str());
		client.sendMessage("/kas/temperatuur", String(climateSensor.getTemperatureCelcius()).c_str());
		client.sendMessage("/kas/luchtdruk", String(climateSensor.getPressure()).c_str());
		lastUpdate = millis();
		if(climateSensor.getTemperatureCelcius(true) > 30){
			// Turn on fan
		}
	}
}