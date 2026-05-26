#include "solar_monitor_client.hpp"
#include <print>

namespace solar
{

    SolarMonitorClient::SolarMonitorClient(std::string brokerUri, ITelemetryListener &listener)
        : m_brokerUri{std::move(brokerUri)}, m_router{listener}, m_client{m_brokerUri, "solar_monitor_dashboard", mqtt::create_options(MQTTVERSION_5)}
    {
        m_client.set_callback(m_router);
    }

    void SolarMonitorClient::start()
    {
        mqtt::connect_options connOpts;
        connOpts.set_mqtt_version(MQTTVERSION_5);
        connOpts.set_clean_start(true);

        std::println("Connecting to network: {}...", m_brokerUri);
        m_client.connect(connOpts)->wait();
        std::println("Connected.");

        constexpr auto subscriptionTopic{"solar/panels/+/telemetry"};
        std::println("Subscribing to feed: {}", subscriptionTopic);
        m_client.subscribe(subscriptionTopic, 1)->wait();
        std::println("Dashboard listening for feeds.");
    }

    void SolarMonitorClient::stop()
    {
        std::println("Shutting down Dashboard...");
        m_client.disconnect()->wait();
        std::println("Dashboard disconnected cleanly.");
    }

} // namespace solar