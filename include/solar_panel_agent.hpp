#pragma once

#include "solar_panel.hpp"
#include "mqtt_publisher.hpp"
#include <thread>
#include <string>

namespace solar
{

    class SolarPanelAgent
    {
    public:
        static constexpr std::chrono::milliseconds interval{1000};
        SolarPanelAgent(SolarPanelSimulator::Config config, std::string brokerUri);

        void start();

    private:
        void run(std::stop_token stopToken);

        SolarPanelSimulator m_simulator;
        MqttPublisher m_publisher;
        std::string m_topic;
        std::jthread m_worker;
    };

} // namespace solar