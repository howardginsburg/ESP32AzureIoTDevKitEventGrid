#include "MQTTClient.h"
#include "iot_configs.h"




WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

void initializeMQTT() {
    wifiClient.setCACert(ROOT_CA);
    wifiClient.setCertificate(DEVICE_PUBLIC_KEY);
    wifiClient.setPrivateKey(DEVICE_PRIVATE_KEY);

    client.setServer(MQTT_SERVER, MQTT_PORT);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect(MQTT_CLIENT, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void sendMessageToMQTT(const char* topic, const char* message) {
    if (!client.connected()) {
        initializeMQTT();
    }
    client.loop();
    client.publish(topic, message);
}