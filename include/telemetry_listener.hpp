#pragma once

#include "solar_panel.hpp"
#include <string>

namespace solar
{

    class TelemetryListener
    {
    public:
        virtual ~TelemetryListener() = default;
        virtual void onTelemetryReceived(const std::string &panelId, const Telemetry &telemetry) noexcept = 0;
    };

} // namespace solar