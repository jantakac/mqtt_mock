#include "telemetry_parser.hpp"
#include <nlohmann/json.hpp>

namespace solar
{

    Telemetry TelemetryParser::parseJson(std::string_view jsonPayload)
    {
        const auto json = nlohmann::json::parse(jsonPayload);

        return Telemetry{
            .wattage = json.at("wattage").get<double>(),
            .voltage = json.at("voltage").get<double>(),
            .ambientTemperature = json.at("ambientTemperature").get<double>(),
            .efficiency = json.at("efficiency").get<double>(),
            .cumulativeEnergyWh = json.at("cumulativeEnergyWh").get<double>(),
            .errorCode = parseErrorCode(json.at("errorCode").get<std::string>())};
    }

    ErrorCode TelemetryParser::parseErrorCode(std::string_view statusStr) noexcept
    {
        if (statusStr == "Overheating")
            return ErrorCode::Overheating;
        if (statusStr == "UnderVoltage")
            return ErrorCode::UnderVoltage;
        if (statusStr == "GridDisconnect")
            return ErrorCode::GridDisconnect;
        if (statusStr == "HardwareFault")
            return ErrorCode::HardwareFault;
        return ErrorCode::None;
    }

    std::string_view TelemetryParser::statusToString(ErrorCode code) noexcept
    {
        switch (code)
        {
        case ErrorCode::None:
            return "Operational";
        case ErrorCode::Overheating:
            return "OVERHEATING FAULT";
        case ErrorCode::UnderVoltage:
            return "UNDERVOLTAGE FAULT";
        case ErrorCode::GridDisconnect:
            return "GRID DISCONNECT";
        case ErrorCode::HardwareFault:
            return "HARDWARE FAULT";
        }
        return "Unknown";
    }

} // namespace solar