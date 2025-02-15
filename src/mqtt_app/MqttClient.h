#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include "IMqttBroker.h"
#include <string>
#include <mqtt/async_client.h>

class MqttClient {
public:
    MqttClient(IMqttBroker* broker, mqtt::async_client* client);
    ~MqttClient();

    void Connect();
    void Subscribe(const std::string& topic);
    void Disconnect();
    void onConnectionLost(const std::string& cause);
    void onMessageArrived(mqtt::const_message_ptr msg);

private:
    

    IMqttBroker* broker_;
    mqtt::async_client* client_;
    mqtt::connect_options connOpts;
    bool connected;
};

#endif // MQTTCLIENT_H
