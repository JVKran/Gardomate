#ifndef __CLIMATE_MANAGER
#define __CLIMATE_MANAGER

#include <forcedClimate.h>
#include "MqttClient.hpp"

#define CLM_10MIN 600000

class ClimateManager {
	private:
		ForcedClimate & climateSensor;
		unsigned int updatePeriod;
		unsigned int lastUpdate = 0;

		MqttClient & client;
	public:
		ClimateManager(ForcedClimate & climateSensor, MqttClient & client, const unsigned int updatePeriod = CLM_10MIN);

		void operator()();

};

#endif //__CLIMATE_MANAGER