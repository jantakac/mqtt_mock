#include "mqtt_publisher.hpp"
#include <print>
#include <chrono>

namespace solar
{

    MqttPublisher::MqttPublisher(std::string brokerUri, std::string clientId)
        : m_brokerUri{std::move(brokerUri)}, m_clientId{std::move(clientId)}, m_client{m_brokerUri, m_clientId, mqtt::create_options(MQTTVERSION_5)}
    {
    }

    void MqttPublisher::connect()
    {
        mqtt::connect_options connOpts;
        connOpts.set_mqtt_version(MQTTVERSION_5);
        connOpts.set_clean_start(true);
        connOpts.set_connect_timeout(std::chrono::seconds(5));

        std::println("Publisher [{}] connecting to broker at {}...", m_clientId, m_brokerUri);
        m_client.connect(connOpts)->wait();
        std::println("Publisher [{}] successfully connected.", m_clientId);
    }

    void MqttPublisher::disconnect()
    {
        std::println("Publisher [{}] disconnecting...", m_clientId);
        m_client.disconnect()->wait();
        std::println("Publisher [{}] safely offline.", m_clientId);
    }

    void MqttPublisher::publish(const std::string &topic, const std::string &payload)
    {
        auto pubMsg = mqtt::make_message(topic, payload, 1, false);
        m_client.publish(pubMsg)->wait();
    }

} // namespace solar