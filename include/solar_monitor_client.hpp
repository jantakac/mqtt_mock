#pragma once

#include "i_telemetry_listener.hpp"
#include "mqtt_router.hpp"
#include <mqtt/async_client.h>
#include <string>

namespace solar
{

    class SolarMonitorClient final
    {
    public:
        SolarMonitorClient(std::string brokerUri, ITelemetryListener &listener);

        void start();
        void stop();

    private:
        std::string m_brokerUri;
        MqttRouter m_router;
        mqtt::async_client m_client;
    };

} // namespace solar