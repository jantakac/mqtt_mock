#pragma once

#include "i_telemetry_listener.hpp"

namespace solar
{

    class SolarDashboard final : public ITelemetryListener
    {
    public:
        void onTelemetryReceived(const std::string &panelId, const Telemetry &telemetry) noexcept override;
    };

} // namespace solar