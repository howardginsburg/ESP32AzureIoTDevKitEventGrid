# ESP32 Azure IoT DevKit Event Grid MQTT Sample

This sample demonstrates how to use the [ESP32 Azure IoT DevKit](https://www.espressif.com/products/devkits/esp32-azure-kit/overview) to send telemetry data to Azure Event Grid using MQTT.  It uses x509 certificates and the PubSubClient library to connect and send messages.

## Requirements

1. [ESP32 Azure IoT DevKit](https://www.espressif.com/products/devkits/esp32-azure-kit/overview).
1. [Visual Studio Code](https://code.visualstudio.com)
1. [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension for VSCode


## Setup Instructions

### Certificate Generation

We will create a root certificate, intermediate certificate, and a device certificate. The root and intermediate certificates will be used to sign the device certificate. The device certificate will be used to authenticate the ESP32 device with Azure Event Grid.

1. Follow the instructions in the [Certificate Generator Repo](https://github.com/howardginsburg/CertificateGenerator) to create the certificates.

### Event Grid Setup

1. Create an instance of Azure Event Grid.
1. Navigate to Settings -> Configuration.
1. Enable the "Enable MQTT" option.
1. Navigate to `Overview` and make note of the `MQTT hostname` and `MQTT Broker Port`.
1. Navigate to MQTT broker -> CA certificates.
1. Upload the `intermediateCAPublicKeyChain.pem` file you generated.
1. Navigate to MQTT broker -> Clients.
1. Create a new Client
    - Set the Client Name to `Device1`.
    - Set the Cl.ient Authentication Name to `Device1`.
    - Set the Client Certificate Authentication Validation Scheme to `Subject Matches Authentication Name`
1. Navidate to MQTT Broker -> Topic spaces.
1. Create a new Topic Space.
    - Set the Name to `TestSpace`'
    - Add a topic template `testtopics/topic1`.
1. Navigate to MQTT Brker -> Permission bindings.
1. Create a permission binding.
    - Set the Name to `publisher`.
    - Set the Client group name to `$all`.
    - Set the Topic space name to `TestSpace`.
    - Set the Permission to `Publisher`.
1. Create a permission binding.
    - Set the Name to `subscriber`.
    - Set the Client group name to `$all`.
    - Set the Topic space name to `TestSpace`.
    - Set the Permission to `Subscriber`.
1.

### ESP32 Setup

1. Clone this repository to your local machine.
1. Rename `src\iot_configs_sample.txt` to `src\iot_configs.h`.
1. Set the values for wifi, event grid, and certificate public/private key values.
