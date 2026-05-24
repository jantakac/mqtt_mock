#include "solar_array_simulator.hpp"

namespace solar
{

    SolarArraySimulator::SolarArraySimulator(std::string brokerUri)
        : m_brokerUri{std::move(brokerUri)}
    {
    }

    void SolarArraySimulator::addPanel(SolarPanelSimulator::Config config)
    {
        m_agents.emplace_back(std::make_unique<SolarPanelAgent>(std::move(config), m_brokerUri));
    }

    void SolarArraySimulator::start()
    {
        for (const auto &agent : m_agents)
        {
            agent->start();
        }
    }

} // namespace solar