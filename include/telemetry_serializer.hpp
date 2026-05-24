#pragma once

#include "solar_panel.hpp"
#include <string>
#include <string_view>

namespace solar
{
    class TelemetrySerializer
    {
    public:
        [[nodiscard]] static std::string serialize(const Telemetry &telemetry);

    private:
        [[nodiscard]] static std::string_view toString(ErrorCode code) noexcept;
    };

} // namespace solar