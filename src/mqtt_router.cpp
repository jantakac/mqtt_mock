#include "mqtt_router.hpp"
#include "mqtt_topic_parser.hpp"
#include "telemetry_parser.hpp"
#include <nlohmann/json.hpp>
#include <print>

namespace solar
{
    MqttRouter::MqttRouter(ITelemetryListener &listener) noexcept
        : m_listener{listener} {}

    void MqttRouter::message_arrived(mqtt::const_message_ptr msg)
    {
        if (!msg)
            return;

        try
        {
            const std::string panelId = MqttTopicParser::extractPanelId(msg->get_topic());
            const Telemetry telemetry = TelemetryParser::parseJson(msg->to_string());

            m_listener.onTelemetryReceived(panelId, telemetry);
        }
        catch (const nlohmann::json::exception &exc)
        {
            std::println(stderr, "Routing Error: Failed to parse JSON payload. Details: {}", exc.what());
        }
        catch (const std::exception &exc)
        {
            std::println(stderr, "Routing Error: Unexpected system exception. Details: {}", exc.what());
        }
    }

} // namespace solar