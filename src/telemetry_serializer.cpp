#include "telemetry_serializer.hpp"
#include <nlohmann/json.hpp>

namespace solar
{

    std::string_view TelemetrySerializer::toString(ErrorCode code) noexcept
    {
        switch (code)
        {
        case ErrorCode::None:
            return "None";
        case ErrorCode::Overheating:
            return "Overheating";
        case ErrorCode::UnderVoltage:
            return "UnderVoltage";
        case ErrorCode::GridDisconnect:
            return "GridDisconnect";
        case ErrorCode::HardwareFault:
            return "HardwareFault";
        }
        return "Unknown";
    }

    std::string TelemetrySerializer::serialize(const Telemetry &telemetry)
    {
        const nlohmann::json jsonPayload = {
            {"wattage", telemetry.wattage},
            {"voltage", telemetry.voltage},
            {"ambientTemperature", telemetry.ambientTemperature},
            {"efficiency", telemetry.efficiency},
            {"cumulativeEnergyWh", telemetry.cumulativeEnergyWh},
            {"errorCode", toString(telemetry.errorCode)}};
        return jsonPayload.dump();
    }

} // namespace solar