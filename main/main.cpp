//
// Created by Braum on 23/12/23.
//

#include "storage/cxx_nvs.hpp"
#include "spdlog/spdlog.h"


// TODO:
// - Design Error Handling Subcomponent.
// - Design Telemetry Subcomponent.
// - Design Clock Synchronization Subcomponent.

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
    // Global Logging Level Initialization
    spdlog::set_level(spdlog::level::debug);

    // NVS Driver Initialization Block
    // NOTE: NVS Wrapper Class for the moment DOES NOT apply Error Handling, this will be implemented
    // after a suitable Error Handling Strategy is defined.
    NVS::Manager();
}
