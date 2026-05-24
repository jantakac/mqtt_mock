#include "solar_dashboard.hpp"
#include "solar_monitor_client.hpp"
#include <print>
#include <cstdlib>
#include <tuple>
#include <mqtt/exception.h>

int main()
{
    const char *envUri = std::getenv("MQTT_BROKER_URI");
    const std::string brokerUri = envUri ? envUri : "tcp://localhost:1883";

    solar::SolarDashboard dashboard;
    solar::SolarMonitorClient client{brokerUri, dashboard};

    try
    {
        client.start();

        std::println("Press Enter to close monitoring console...");
        std::ignore = std::getchar();

        client.stop();
    }
    catch (const mqtt::exception &exc)
    {
        std::println(stderr, "Fatal Client Execution Error: {}", exc.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}