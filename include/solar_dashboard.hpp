#pragma once

#include "telemetry_listener.hpp"

namespace solar
{

    class SolarDashboard final : public TelemetryListener
    {
    public:
        void onTelemetryReceived(const std::string &panelId, const Telemetry &telemetry) noexcept override;
    };

} // namespace solar