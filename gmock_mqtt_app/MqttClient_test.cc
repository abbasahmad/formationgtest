#include "../src/mqtt_app/MqttClient.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mqtt/async_client.h>

using ::testing::_;
using ::testing::NiceMock;

class MockIMqttBroker : public IMqttBroker {
public:
    MOCK_METHOD(void, Connect, (), (override));
    MOCK_METHOD(void, Disconnect, (), (override));
    MOCK_METHOD(void, Subscribe, (const std::string& topic), (override));
    MOCK_METHOD(void, Publish, (const std::string& topic, const std::string& message), (override));
};

TEST(MqttClientTest, ConnectAndSubscribe) {
    NiceMock<MockIMqttBroker> mockBroker;
    mqtt::async_client mockClient("tcp://localhost:1883", "test_client");
    MqttClient mqttClient(&mockBroker, &mockClient);

    EXPECT_CALL(mockBroker, Connect()).Times(1);
    EXPECT_CALL(mockBroker, Subscribe("test/topic")).Times(1);

    mqttClient.Connect();
    mqttClient.Subscribe("test/topic");
}

TEST(MqttClientTest, Disconnect) {
    NiceMock<MockIMqttBroker> mockBroker;
    mqtt::async_client mockClient("tcp://localhost:1883", "test_client");
    MqttClient mqttClient(&mockBroker, &mockClient);

    EXPECT_CALL(mockBroker, Connect()).Times(1);
    EXPECT_CALL(mockBroker, Disconnect()).Times(1);

    mqttClient.Connect();
    mqttClient.Disconnect();
}

TEST(MqttClientTest, SubscribeToMultipleTopics) {
    NiceMock<MockIMqttBroker> mockBroker;
    mqtt::async_client mockClient("tcp://localhost:1883", "test_client");
    MqttClient mqttClient(&mockBroker, &mockClient);

    EXPECT_CALL(mockBroker, Connect()).Times(1);
    EXPECT_CALL(mockBroker, Subscribe(_)).Times(3).RetiresOnSaturation();

    mqttClient.Connect();
    mqttClient.Subscribe("topic1");
    mqttClient.Subscribe("topic2");
    mqttClient.Subscribe("topic3");

}

TEST(MqttClientTest, MessageReceived) {
    NiceMock<MockIMqttBroker> mockBroker;
    mqtt::async_client mockClient("tcp://localhost:1883", "test_client");
    MqttClient mqttClient(&mockBroker, &mockClient);

    // Create a dummy message using mqtt::make_message.
    auto dummyMessage = mqtt::make_message("test/topic", "Hello, world!");

    // Capture stdout to verify output.
    testing::internal::CaptureStdout();
    mqttClient.onMessageArrived(dummyMessage);
    std::string output = testing::internal::GetCapturedStdout();

    // Check that the output contains the expected topic and payload.
    EXPECT_THAT(output, testing::HasSubstr("Message arrived. Topic: test/topic"));
    EXPECT_THAT(output, testing::HasSubstr("Payload: Hello, world!"));
}

/**
 * @brief Teste la méthode Subscribe de MqttClient sans connexion préalable.
 *
 * Ce test vérifie que lorsqu'une tentative de souscription est faite
 * sans que le client soit connecté, aucune souscription n'est envoyée
 * au broker et un message d'erreur approprié est affiché dans std::cerr.
 */

//...

/**
 * @brief Teste la méthode Disconnect de MqttClient sans connexion préalable.
 *
 * Ce test s'assure qu'aucune tentative de déconnexion n'est effectuée sur le broker
 * si le client n'a jamais été connecté.
 */

//...


/**
 * @brief Teste la gestion de la perte de connexion dans MqttClient.
 *
 * Ce test vérifie que la méthode onConnectionLost affiche correctement
 * un message d'erreur dans std::cerr lorsqu'une perte de connexion est simulée.
 */

 //...