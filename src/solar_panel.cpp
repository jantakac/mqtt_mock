#include "solar_panel.hpp"
#include <cmath>
#include <numbers>
#include <algorithm>

namespace solar
{

    SolarPanelSimulator::SolarPanelSimulator(Config config) noexcept
        : m_config{std::move(config)}
    {
    }

    void SolarPanelSimulator::tick(std::chrono::milliseconds deltaTime) noexcept
    {
        const double dtHours{static_cast<double>(deltaTime.count()) / 3'600'000.0};

        m_simulatedTimeHours += dtHours;
        if (m_simulatedTimeHours >= 24.0)
        {
            m_simulatedTimeHours = std::fmod(m_simulatedTimeHours, 24.0);
        }

        updatePhysics(dtHours);
    }

    std::string SolarPanelSimulator::id() const noexcept
    {
        return m_config.id;
    }

    Telemetry SolarPanelSimulator::telemetry() const noexcept
    {
        return m_telemetry;
    }

    double SolarPanelSimulator::simulatedTimeOfDayHours() const noexcept
    {
        return m_simulatedTimeHours;
    }

    void SolarPanelSimulator::setAmbientTemperature(double tempCelsius) noexcept
    {
        m_ambientTemperature = tempCelsius;
    }

    void SolarPanelSimulator::triggerFault(ErrorCode code) noexcept
    {
        m_activeError = code;
    }

    void SolarPanelSimulator::clearFault() noexcept
    {
        m_activeError = ErrorCode::None;
    }

    double SolarPanelSimulator::calculateSunIntensity() const noexcept
    {
        // Sun rises at 6:00 (6.0) and sets at 18:00 (18.0). Peak at 12:00 (12.0).
        if (m_simulatedTimeHours < 6.0 || m_simulatedTimeHours > 18.0)
        {
            return 0.0;
        }

        // Convert 6:00-18:00 window to a 0 to PI radian range
        const double angle{(m_simulatedTimeHours - 6.0) * (std::numbers::pi / 12.0)};
        return std::sin(angle);
    }

    void SolarPanelSimulator::updatePhysics(double dtHours) noexcept
    {
        if (m_activeError == ErrorCode::HardwareFault || m_activeError == ErrorCode::GridDisconnect)
        {
            m_telemetry = Telemetry{
                .wattage = 0.0,
                .voltage = 0.0,
                .ambientTemperature = m_ambientTemperature,
                .efficiency = 0.0,
                .cumulativeEnergyWh = m_telemetry.cumulativeEnergyWh,
                .errorCode = m_activeError};
            return;
        }

        const double sunIntensity{calculateSunIntensity()};

        // Thermal coefficient: panels lose efficiency as they heat up
        // Est. panel temperature increases up to 25C above ambient at max intensity
        const double panelHeating{sunIntensity * 25.0};
        const double cellTemperature{m_ambientTemperature + panelHeating};
        const double tempDelta{std::max(0.0, cellTemperature - 25.0)};
        const double tempEfficiencyLoss{tempDelta * 0.004}; // -0.4% per degree above 25C

        const double currentEfficiency{std::max(0.0, m_config.baseEfficiency - tempEfficiencyLoss)};

        // Calculate outputs
        double currentWattage{m_config.maxPowerWatts * sunIntensity * (currentEfficiency / m_config.baseEfficiency)};
        double currentVoltage{sunIntensity > 0.05 ? m_config.nominalVoltage * (0.8 + 0.2 * sunIntensity) : 0.0};

        // Handle specific simulated errors
        ErrorCode currentError{m_activeError};
        if (cellTemperature > 55.0)
        {
            currentError = ErrorCode::Overheating;
        }
        else if (sunIntensity > 0.05 && currentVoltage < (m_config.nominalVoltage * 0.5))
        {
            currentError = ErrorCode::UnderVoltage;
        }

        // Accumulate total generation
        const double generatedEnergyWh{currentWattage * dtHours};

        m_telemetry = Telemetry{
            .wattage = currentWattage,
            .voltage = currentVoltage,
            .ambientTemperature = cellTemperature,
            .efficiency = currentEfficiency,
            .cumulativeEnergyWh = m_telemetry.cumulativeEnergyWh + generatedEnergyWh,
            .errorCode = currentError};
    }

} // namespace solar