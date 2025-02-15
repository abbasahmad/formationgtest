#include "MqttClient.h"
#include "RealMqttBroker.h"
#include <unistd.h>

int main() {
    RealMqttBroker broker("tcp://localhost:1883", "test_client");
    // Pass the broker's internal client to MqttClient
    MqttClient mqttClient(&broker, &broker.getClient());

    mqttClient.Connect();
    mqttClient.Subscribe("demolition/building");

    // Keep the client running to receive messages
    while (true) {
        sleep(2);
    }

    mqttClient.Disconnect();
    return 0;
}
