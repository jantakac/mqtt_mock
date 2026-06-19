cmake_minimum_required(VERSION 3.24)
project(SolarMqttSimulation LANGUAGES C CXX)

# Configure C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable folder structures in IDEs like Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

# -----------------------------------------------------------------------------
# 1. Fetch nlohmann/json for data serialization
# -----------------------------------------------------------------------------
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

# -----------------------------------------------------------------------------
# 3. Fetch Eclipse Paho MQTT C++
# -----------------------------------------------------------------------------
set(PAHO_WITH_SSL ON CACHE BOOL "Build Paho C++ with SSL support" FORCE)

# Change these two lines to build SHARED:
set(PAHO_BUILD_SHARED ON CACHE BOOL "Build Paho C++ as a shared library" FORCE)
set(PAHO_BUILD_STATIC OFF CACHE BOOL "Build Paho C++ as a static library" FORCE)

set(PAHO_BUILD_SAMPLES OFF CACHE BOOL "Build Paho C++ samples" FORCE)
set(PAHO_BUILD_DOCUMENTATION OFF CACHE BOOL "Build Paho C++ documentation" FORCE)

FetchContent_Declare(
    paho.mqtt.cpp
    GIT_REPOSITORY https://github.com/eclipse/paho.mqtt.cpp.git
    GIT_TAG        v1.4.0
)
FetchContent_MakeAvailable(paho.mqtt.cpp)

# -----------------------------------------------------------------------------
# 4. Define Targets
# -----------------------------------------------------------------------------

# Common code, simulation models, and shared headers
add_library(solar_common STATIC src/solar_panel.cpp)
target_include_directories(solar_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(solar_common PUBLIC 
    nlohmann_json::nlohmann_json
    paho-mqttpp3
)

# Publisher executable
add_executable(solar_publisher 
    src/publisher.cpp
    src/telemetry_serializer.cpp
    src/mqtt_publisher.cpp
    src/environment_model.cpp
    src/solar_panel_agent.cpp
    src/solar_array_simulator.cpp
)
target_link_libraries(solar_publisher PRIVATE solar_common)

# Subscriber executable
add_executable(solar_subscriber 
    src/subscriber.cpp
    src/telemetry_parser.cpp
    src/mqtt_topic_parser.cpp
    src/mqtt_router.cpp
    src/solar_dashboard.cpp
    src/solar_monitor_client.cpp
    src/subscriber_config.cpp
)
target_link_libraries(solar_subscriber PRIVATE solar_common)

# -----------------------------------------------------------------------------
# 5. Compiler Specific Warning Flags
# -----------------------------------------------------------------------------
if(MSVC)
    target_compile_options(solar_publisher PRIVATE /W4 /WX)
    target_compile_options(solar_subscriber PRIVATE /W4 /WX)
else()
    target_compile_options(solar_publisher PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(solar_subscriber PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()