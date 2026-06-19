#pragma once

#include "i_telemetry_listener.hpp"
#include <mqtt/callback.h>

namespace solar
{

    class MqttRouter final : public virtual mqtt::callback
    {
    public:
        explicit MqttRouter(ITelemetryListener &listener) noexcept;

        MqttRouter(const MqttRouter &) = delete;
        MqttRouter &operator=(const MqttRouter &) = delete;
        MqttRouter(MqttRouter &&) = delete;
        MqttRouter &operator=(MqttRouter &&) = delete;

        ~MqttRouter() override = default;

    private:
        void message_arrived(mqtt::const_message_ptr msg) override;

        ITelemetryListener &m_listener;
    };

} // namespace solar