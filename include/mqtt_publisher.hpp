#pragma once

#include <string>
#include <string_view>
#include <mqtt/async_client.h>

namespace solar
{

    class MqttPublisher
    {
    public:
        MqttPublisher(std::string brokerUri, std::string clientId);

        void connect();
        void disconnect();
        void publish(const std::string &topic, const std::string &payload);

    private:
        std::string m_brokerUri;
        std::string m_clientId;
        mqtt::async_client m_client;
    };

} // namespace solar