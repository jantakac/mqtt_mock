#pragma once

#include "i_telemetry_listener.hpp"
#include <mqtt/callback.h>

namespace solar
{

    class MqttRouter final : public virtual mqtt::callback
    {
    public:
        explicit MqttRouter(ITelemetryListener &listener) noexcept;

    private:
        void message_arrived(mqtt::const_message_ptr msg) override;

        ITelemetryListener &m_listener;
    };

} // namespace solar