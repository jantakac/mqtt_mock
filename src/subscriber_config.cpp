#include "subscriber_config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

namespace solar
{

    SubscriberConfig loadConfig(const std::string &filepath)
    {
        std::ifstream file{filepath};
        if (!file.is_open())
        {
            throw std::runtime_error{"Failed to open config file: " + filepath};
        }

        const auto jsonConfig{nlohmann::json::parse(file)};

        // Check if the root is an array, and use the first element if so
        const auto &configObj = jsonConfig.is_array() ? jsonConfig.at(0) : jsonConfig;

        return SubscriberConfig{
            .brokerUri = configObj.value("broker_uri", "tcp://localhost:1883"),
            .targetPanels = configObj.at("allowed_devices").get<std::vector<std::string>>()};
    }
} // namespace solar