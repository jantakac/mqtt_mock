#include "solar_panel_agent.hpp"
#include "telemetry_serializer.hpp"
#include "environment_model.hpp"
#include <print>
#include <mutex>
#include <condition_variable>

namespace solar
{

    SolarPanelAgent::SolarPanelAgent(SolarPanelSimulator::Config config, std::string brokerUri)
        : m_simulator{std::move(config)}, m_publisher{std::move(brokerUri), "client_" + m_simulator.id()}, m_topic{"solar/panels/" + m_simulator.id() + "/telemetry"}
    {
    }

    void SolarPanelAgent::start()
    {
        m_worker = std::jthread{[this](std::stop_token token)
                                { run(std::move(token)); }};
    }

    void SolarPanelAgent::run(std::stop_token stopToken)
    {
        try
        {
            m_publisher.connect();

            constexpr std::chrono::milliseconds interval{1000};
            std::mutex mtx;

            while (!stopToken.stop_requested())
            {
                m_simulator.tick(interval);

                const std::string payload = TelemetrySerializer::serialize(m_simulator.telemetry());
                m_publisher.publish(m_topic, payload);

                const double newTemp = EnvironmentModel::calculateAmbientTemperature(
                    m_simulator.simulatedTimeOfDayHours());
                m_simulator.setAmbientTemperature(newTemp);

                std::unique_lock lock{mtx};
                std::condition_variable_any{}.wait_for(lock, stopToken, interval, []
                                                       { return false; });
            }

            m_publisher.disconnect();
        }
        catch (const mqtt::exception &exc)
        {
            std::println(stderr, "Agent [{}] critical network failure: {}", m_simulator.id(), exc.what());
        }
        catch (const std::exception &exc)
        {
            std::println(stderr, "Agent [{}] critical runtime failure: {}", m_simulator.id(), exc.what());
        }
    }

} // namespace solar