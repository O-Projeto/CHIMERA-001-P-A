//
// Created by Braum on 23/12/23.
//

#include "storage/cxx_nvs.hpp"
#include "exception/cxx_chimera_exception.hpp"
#include "spdlog/spdlog.h"

// TODO:
// - Design Telemetry Subcomponent.
// - Design Clock Synchronization Subcomponent.

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
    // Global Logging Level Initialization
    spdlog::set_level(spdlog::level::err);

    // NVS Driver Initialization Block
    try {
        nvs::manager();
        // NOTE: Keep this disable until ReSharper is fixed
        // ReSharper disable once CppDFAUnreachableCode
    } catch (const chimera_exception::exception&ex) {
        print_exception(ex);
    }
}
