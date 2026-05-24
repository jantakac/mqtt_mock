#include "environment_model.hpp"

namespace solar
{

    double EnvironmentModel::calculateAmbientTemperature(double simulatedTimeOfDayHours) noexcept
    {
        // Hot midday peak between 11 AM and 1 PM
        if (simulatedTimeOfDayHours > 11.0 && simulatedTimeOfDayHours < 13.0)
        {
            return 35.0;
        }
        // Moderate day/night
        return 20.0;
    }

} // namespace solar