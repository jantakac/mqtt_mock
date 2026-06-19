#pragma once

#include "i_telemetry_listener.hpp"
#include "subscriber_config.hpp"
#include "mqtt_router.hpp"
#include <mqtt/async_client.h>
#include <string>

namespace solar
{

    class SolarMonitorClient final
    {
    public:
        SolarMonitorClient(SubscriberConfig config, ITelemetryListener &listener);
        SolarMonitorClient(const SolarMonitorClient &) = delete;
        SolarMonitorClient &operator=(const SolarMonitorClient &) = delete;
        SolarMonitorClient(SolarMonitorClient &&) noexcept = default;
        SolarMonitorClient &operator=(SolarMonitorClient &&) noexcept = default;

        ~SolarMonitorClient() = default;

        void start();
        void stop();

    private:
        solar::SubscriberConfig m_config;
        MqttRouter m_router;
        mqtt::async_client m_client;
    };

} // namespace solar