//
// Created by Braum on 23/12/23.

//

extern "C" {
#include "esp_event.h"
#include "esp_console.h"
}

#include <cstdio>
#include <memory>

#include "command/cxx_command.hpp"
#include "console/cxx_console.hpp"
#include "esp_event_cxx.hpp"
#include "storage/cxx_nvs.hpp"
#include "exception/cxx_exception.hpp"

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
    /*
     * TODO: Implement Console Destructor
    */

    // CHIMERA subsystem initialization
    try {
        chimera::nvs subsystem_nvs{};
        chimera::console subsystem_console{};
    }
    // NOTE: Keep this disabled until ReSharper is fixed
    // ReSharper disable once CppDFAUnreachableCode
    catch (const chimera::exception&ex) {
        print_exception(ex);
        abort();
    }

    // CHIMERA command registration
    try {
        for (const std::array<const esp_console_cmd_t, 1> command_list{
                 chimera::command::servo_command()
             }; const auto&command: command_list) {
            chimera::console::register_command(command);
        }
    }
    catch (const chimera::exception&ex) {
        print_exception(ex);
        abort();
    }
}
