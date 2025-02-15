#include "MqttClient.h"
#include <iostream>

MqttClient::MqttClient(IMqttBroker* broker, mqtt::async_client* client)
    : broker_(broker), client_(client), connected(false) {
    // You may still configure connection options if needed,
    // but they will be used by the broker in a real scenario.
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);
}

MqttClient::~MqttClient() {
    if (connected) {
        Disconnect();
    }
}

void MqttClient::Connect() {
    // Set up client callbacks regardless of who manages the connection.
    client_->set_connection_lost_handler(
        [this](const std::string& cause) { this->onConnectionLost(cause); });

    client_->set_message_callback(
        [this](mqtt::const_message_ptr msg) { this->onMessageArrived(msg); });

    try {
        // Delegate connection to the broker.
        broker_->Connect();
        connected = true;
        std::cout << "Connected to MQTT broker." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}

void MqttClient::Subscribe(const std::string& topic) {
    if (connected) {
        // Delegate subscription to the broker.
        broker_->Subscribe(topic);
        std::cout << "Subscribed to topic: " << topic << std::endl;
    } else {
        std::cerr << "Client not connected. Cannot subscribe." << std::endl;
    }
}

void MqttClient::Disconnect() {
    if (connected) {
        // Delegate disconnection to the broker.
        broker_->Disconnect();
        connected = false;
        std::cout << "Disconnected from MQTT broker." << std::endl;
    }
}

void MqttClient::onConnectionLost(const std::string& cause) {
    std::cerr << "Connection lost: " << cause << std::endl;
    connected = false;
}

void MqttClient::onMessageArrived(mqtt::const_message_ptr msg) {
    std::cout << "Message arrived. Topic: " << msg->get_topic()
              << ". Payload: " << msg->to_string() << std::endl;
}
