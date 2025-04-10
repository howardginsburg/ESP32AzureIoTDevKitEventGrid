#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

void initializeMQTT();
void sendMessageToMQTT(const char* topic, const char* message);

#endif // MQTTCLIENT_H