#pragma once

#include "i_telemetry_listener.hpp"

namespace solar
{

    class SolarDashboard final : public ITelemetryListener
    {
    public:
        SolarDashboard() = default;
        ~SolarDashboard() override = default;

        void onTelemetryReceived(const std::string &panelId, const Telemetry &telemetry) noexcept override;
    };

} // namespace solar