#ifndef __CONNECTIONS_HPP
#define __CONNECTIONS_HPP

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "array.hpp"

class MessageListener {
    public:
        virtual void messageReceived(const String & receivedMessage, const char* topic = "") = 0;
};

void callback(char* topic, byte* payload, unsigned int length);

class MqttClient {
    private:
        char* ssid;
        char* password;
        char* mqttServer;
        
        const char* topic;
        PubSubClient client;
        const bool retainedMessages;
        const uint8_t qosLevel;
        
        MessageListener * listeners[20] = {};
        uint8_t amountOfListeners = 0;
    public:

        MqttClient(char* ssid, char* password, char* mqttServer, const char* topic, WiFiClient & espClient, const bool retainedMessages = true, const uint8_t qosLevel = 1);

        void addListener(MessageListener & listener);
        void notifyListeners(const String & mesage, const char* topic);

        void setupWifi();
        void setupConnections();
        void reconnect();

        void operator()();
        void sendMessage(const char* topic, const char* messageToSend);
};

#endif //__CONNECTIONS_HPP