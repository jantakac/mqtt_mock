#pragma once

#include <string>
#include <chrono>
#include <cstdint>

namespace solar
{
    enum class ErrorCode : int32_t
    {
        None = 0,
        Overheating = 101,
        UnderVoltage = 102,
        GridDisconnect = 103,
        HardwareFault = 500
    };

    struct Telemetry
    {
        double wattage{0.0};
        double voltage{0.0};
        double ambientTemperature{0.0};
        double efficiency{0.0};
        double cumulativeEnergyWh{0.0};
        ErrorCode errorCode{ErrorCode::None};
    };

    class SolarPanelSimulator
    {
    public:
        struct Config
        {
            std::string id;
            double maxPowerWatts{400.0};
            double nominalVoltage{40.0};
            double baseEfficiency{0.22};
        };

        explicit SolarPanelSimulator(Config config) noexcept;

        SolarPanelSimulator(const SolarPanelSimulator &) = delete;
        SolarPanelSimulator &operator=(const SolarPanelSimulator &) = delete;

        SolarPanelSimulator(SolarPanelSimulator &&) noexcept = default;
        SolarPanelSimulator &operator=(SolarPanelSimulator &&) noexcept = default;

        ~SolarPanelSimulator() = default;

        void tick(std::chrono::milliseconds deltaTime) noexcept;

        [[nodiscard]] std::string id() const noexcept;
        [[nodiscard]] Telemetry telemetry() const noexcept;
        [[nodiscard]] double simulatedTimeOfDayHours() const noexcept;

        void setAmbientTemperature(double tempCelsius) noexcept;
        void triggerFault(ErrorCode code) noexcept;
        void clearFault() noexcept;

    private:
        void updatePhysics(double dtHours) noexcept;
        [[nodiscard]] double calculateSunIntensity() const noexcept;

        Config m_config;
        Telemetry m_telemetry{};

        double m_simulatedTimeHours{8.0};
        double m_ambientTemperature{20.0};
        ErrorCode m_activeError{ErrorCode::None};
    };

} // namespace solar