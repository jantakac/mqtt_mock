#pragma once

#include "solar_panel.hpp"
#include <string>

namespace solar
{

    class ITelemetryListener
    {
    public:
        virtual ~ITelemetryListener() = default;
        virtual void onTelemetryReceived(const std::string &panelId, const Telemetry &telemetry) noexcept = 0;
    };

} // namespace solar