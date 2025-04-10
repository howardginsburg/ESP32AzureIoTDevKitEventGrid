#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>
#include <WiFi.h>
#include "esp_err.h"
#include "nvs_flash.h"
#include "MQTTClient.h"
#include "iot_configs.h"
#include "esp32_azureiotkit_sensors.h"

// Macro to help obtain the length of a string define discounting the byte used for null-terminator (\0).
#define lengthof(x)                      (sizeof(x) - 1)

int last_sensor_read_time =              0;
const int sensor_read_frequency_millis = 5000;
bool led1_on = false;
bool led2_on = true;

void setup() {
    Serial.begin(115200);
    esp32_azureiotkit_initialize_sensors();

    esp32_azureiotkit_oled_clean_screen();
    
    // Connect to WiFi
    WiFi.begin(IOT_CONFIG_WIFI_SSID, IOT_CONFIG_WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // Display the ip address on the oled
    esp32_azureiotkit_oled_show_message((uint8_t*)WiFi.localIP().toString().c_str(), WiFi.localIP().toString().length());

    initializeMQTT();
}

void loop() {
  if ((millis() - last_sensor_read_time) >= sensor_read_frequency_millis)
  {
      printf("temperature=%f C\r\n", esp32_azureiotkit_get_temperature());
      printf("humidity=%f %\r\n", esp32_azureiotkit_get_humidity());
      printf("light=%f lux\r\n", esp32_azureiotkit_get_ambientLight());

      float pressure, altitude;
      esp32_azureiotkit_get_pressure_altitude(&pressure, &altitude);
      printf("pressure=%f Pa\r\n", pressure);
      printf("altitude=%f m\r\n", altitude);

      int pitch, roll, accelX, accelY, accelZ;
      esp32_azureiotkit_get_pitch_roll_accel(&pitch, &roll, &accelX, &accelY, &accelZ);
      printf("pitch=%d\r\n", pitch);
      printf("roll=%d\r\n", roll);
      printf("acceleration X=%d\r\n", accelX);
      printf("acceleration Y=%d\r\n", accelY);
      printf("acceleration Z=%d\r\n", accelZ);

      int magnetometerX, magnetometerY, magnetometerZ;
      esp32_azureiotkit_get_magnetometer(&magnetometerX, &magnetometerY, &magnetometerZ);
      printf("magnetometer X=%d T\r\n", magnetometerX);
      printf("magnetometer Y=%d T\r\n", magnetometerY);
      printf("magnetometer Z=%d T\r\n", magnetometerZ);

      esp32_azureiotkit_led1_set_state(led1_on ? LED_STATE_ON : LED_STATE_OFF);
      esp32_azureiotkit_led2_set_state(led2_on ? LED_STATE_ON : LED_STATE_OFF);

      led1_on = !led1_on;
      led2_on = !led2_on;

      // Send a message to the MQTT broker
      float temperature = esp32_azureiotkit_get_temperature();
      float humidity = esp32_azureiotkit_get_humidity();
      char message[128];
      snprintf(message, sizeof(message), "{\"temperature\": %.2f, \"humidity\": %.2f}", temperature, humidity);
      sendMessageToMQTT("testtopics/topic1", message);

      last_sensor_read_time = millis();
  }
}