#pragma once

#include <string>
#include <vector>

namespace solar
{

    struct SubscriberConfig
    {
        std::string brokerUri;
        std::vector<std::string> targetPanels;
    };

    [[nodiscard]] SubscriberConfig loadConfig(const std::string &filepath);

} // namespace solar