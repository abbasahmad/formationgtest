#ifndef REALMQTTBROKER_H
#define REALMQTTBROKER_H

#include "IMqttBroker.h"
#include <mqtt/async_client.h>
#include <string>

class RealMqttBroker : public IMqttBroker {
public:
    RealMqttBroker(const std::string& serverURI, const std::string& clientId)
        : serverURI(serverURI), clientId(clientId), client(serverURI, clientId), connOpts() {
        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);
    }

    std::string getServerURI() const { return serverURI; }
    std::string getClientId() const { return clientId; }
    mqtt::async_client& getClient() { return client; }

    void Connect() override {
        client.connect(connOpts)->wait();
    }

    void Disconnect() override {
        client.disconnect()->wait();
    }

    void Subscribe(const std::string& topic) override {
        client.subscribe(topic, 1)->wait();
    }

    void Publish(const std::string& topic, const std::string& message) override {
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
        pubmsg->set_qos(1);
        client.publish(pubmsg)->wait();
    }

private:
    std::string serverURI;
    std::string clientId;
    mqtt::async_client client;
    mqtt::connect_options connOpts;
};

#endif // REALMQTTBROKER_H
