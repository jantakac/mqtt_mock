#pragma once

namespace solar
{

    class EnvironmentModel
    {
    public:
        [[nodiscard]] static double calculateAmbientTemperature(double simulatedTimeOfDayHours) noexcept;
    };

} // namespace solar