#include "mqtt_topic_parser.hpp"

namespace solar
{

    std::string MqttTopicParser::extractPanelId(std::string_view topic) noexcept
    {
        constexpr std::string_view prefix{"solar/panels/"};
        constexpr std::string_view suffix{"/telemetry"};

        if (topic.starts_with(prefix) && topic.ends_with(suffix))
        {
            const auto startPos = prefix.length();
            const auto length = topic.length() - prefix.length() - suffix.length();
            return std::string{topic.substr(startPos, length)};
        }
        return "unknown";
    }

} // namespace solar