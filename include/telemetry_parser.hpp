#pragma once

#include "solar_panel.hpp"
#include <string_view>

namespace solar
{

    class TelemetryParser
    {
    public:
        static Telemetry parseJson(std::string_view jsonPayload);
        static ErrorCode parseErrorCode(std::string_view statusStr) noexcept;
        static std::string_view statusToString(ErrorCode code) noexcept;
    };

} // namespace solar