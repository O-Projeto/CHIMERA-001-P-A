//
// Created by Braum on 23/12/23.
//

#include "storage/cxx_nvs.hpp"


// TODO:
// - Design Error Handling Subcomponent.
// - Design Logging Subcomponent.
// - Create Temperature Sensor Monitor, for checking the current operating temperature.

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
    // NVS Driver Initialization Block
    NVS::Manager();
}
