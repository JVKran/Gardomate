#ifndef __PLANT_MANAGER
#define __PLANT_MANAGER

#include "MqttClient.hpp"

class PlantManager {
	private:
		const uint8_t fanPin;
		const uint8_t moisturePin;

		MqttClient & client;
		unsigned int updatePeriod;
		unsigned int lastUpdate = 0;
	public:
		PlantManager(const uint8_t fanPin, MqttClient & client, const uint8_t moisturePin = A0, const unsigned int updatePeriod = 600000);
		void begin();

		void operator()();
};

#endif //__PLANT_MANAGER