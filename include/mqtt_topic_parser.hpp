#pragma once

#include <string>
#include <string_view>

namespace solar
{

    class MqttTopicParser
    {
    public:
        static std::string extractPanelId(std::string_view topic) noexcept;
    };

} // namespace solar