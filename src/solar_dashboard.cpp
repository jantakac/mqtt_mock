#include "solar_dashboard.hpp"
#include "telemetry_parser.hpp"
#include <print>

namespace solar
{

    void SolarDashboard::onTelemetryReceived(const std::string &panelId, const Telemetry &telemetry) noexcept
    {
        std::println("\n┌──────────────────────────────────────────┐");
        std::println("│ SOLAR TELEMETRY INGESTION                                 │");
        std::println("├──────────────────────────────────────────┤");
        std::println("│ Panel ID:       {:<24}                  │", panelId);
        std::println("│ Output Power:   {:>7.2f} W                                 │", telemetry.wattage);
        std::println("│ Output Voltage: {:>7.2f} V                                 │", telemetry.voltage);
        std::println("│ Cell Temp:      {:>7.2f} °C                                │", telemetry.ambientTemperature);
        std::println("│ Current Eff:    {:>7.2f} %                                 │", telemetry.efficiency * 100.0);
        std::println("│ Total Yield:    {:>7.2f} Wh                                │", telemetry.cumulativeEnergyWh);
        std::println("│ Array Status:   {:<24}                  │", TelemetryParser::statusToString(telemetry.errorCode));
        std::println("└──────────────────────────────────────────┘");
    }

} // namespace solar