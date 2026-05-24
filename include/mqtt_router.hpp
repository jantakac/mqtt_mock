#pragma once

#include "telemetry_listener.hpp"
#include <mqtt/callback.h>

namespace solar
{

    class MqttRouter final : public virtual mqtt::callback
    {
    public:
        explicit MqttRouter(TelemetryListener &listener) noexcept;

    private:
        void message_arrived(mqtt::const_message_ptr msg) override;

        TelemetryListener &m_listener;
    };

} // namespace solar