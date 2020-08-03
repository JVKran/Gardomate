#include "MqttClient.hpp"

MqttClient::MqttClient(char* ssid, char* password, char* mqttServer, const char* topic, WiFiClient & espClient, const bool retainedMessages, const uint8_t qosLevel):
    ssid(ssid),
    password(password),
    mqttServer(mqttServer),
    topic(topic),
    client(espClient),
    retainedMessages(retainedMessages),
    qosLevel(qosLevel)
{
    WiFi.mode(WIFI_STA);
}

void MqttClient::addListener(MessageListener & listener){
    if(amountOfListeners++ <= 19){
        listeners[amountOfListeners] = &listener;
    }
}

void MqttClient::notifyListeners(const String & message, const char* topic){
	for (int i = 0; i < amountOfListeners; i++){
        listeners[i]->messageReceived(message, topic);
    }
}

void MqttClient::setupWifi() {
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void MqttClient::setupConnections(){
    client.setServer(mqttServer, 1883);
    client.setCallback(callback);
    client.subscribe(topic, qosLevel);
    reconnect();                //Establish a connection by signing in with credentials.
}

void MqttClient::reconnect() {
    while (!client.connected()) {
        if (client.connect("GreenhouseClient", "Greenhouse", "Snip238!")) {
            delay(500);
            client.subscribe(topic);
            for (int i = 0; i < amountOfListeners; i++){
                listeners[i]->messageReceived("CONNECTED");
            }
            delay(500);
            break;
        } else {
            delay(500);
        }
    }
}

void MqttClient::operator()(){
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}

void MqttClient::sendMessage(const char* topic, const char* messageToSend){
    client.publish(topic, messageToSend, retainedMessages);
}
