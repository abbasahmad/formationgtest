// IMqttBroker.h
#ifndef IMQTTBROKER_H
#define IMQTTBROKER_H

#include <string>

class IMqttBroker {
public:
    virtual ~IMqttBroker() = default;
    virtual void Connect() = 0;
    virtual void Disconnect() = 0;
    virtual void Subscribe(const std::string& topic) = 0;
    virtual void Publish(const std::string& topic, const std::string& message) = 0;
};

#endif // IMQTTBROKER_H
