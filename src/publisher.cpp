#include "solar_array_simulator.hpp"
#include <print>
#include <cstdlib>
#include <tuple>

int main()
{
    const char *envUri = std::getenv("MQTT_BROKER_URI");
    const std::string brokerUri = envUri ? envUri : "tcp://localhost:1883";

    std::println("Starting Solar Array Publisher Simulation on {}...", brokerUri);

    solar::SolarArraySimulator arraySimulator{brokerUri};

    arraySimulator.addPanel(solar::SolarPanelSimulator::Config{
        .id = "panel_east_01",
        .maxPowerWatts = 380.0,
        .nominalVoltage = 38.5,
        .baseEfficiency = 0.21});

    arraySimulator.addPanel(solar::SolarPanelSimulator::Config{
        .id = "panel_roof_02",
        .maxPowerWatts = 420.0,
        .nominalVoltage = 42.0,
        .baseEfficiency = 0.23});

    arraySimulator.addPanel(solar::SolarPanelSimulator::Config{
        .id = "panel_west_03",
        .maxPowerWatts = 350.0,
        .nominalVoltage = 36.0,
        .baseEfficiency = 0.19});

    arraySimulator.start();

    std::println("Simulation active. Press Enter to shutdown safely...");
    std::ignore = std::getchar();

    std::println("Shutting down agents...");

    return EXIT_SUCCESS;
}