#pragma once

#include "solar_panel.hpp"
#include "solar_panel_agent.hpp"
#include <vector>
#include <memory>
#include <string>

namespace solar
{

    class SolarArraySimulator
    {
    public:
        explicit SolarArraySimulator(std::string brokerUri);

        void addPanel(SolarPanelSimulator::Config config);
        void start();

    private:
        std::string m_brokerUri;
        std::vector<std::unique_ptr<SolarPanelAgent>> m_agents;
    };

} // namespace solar