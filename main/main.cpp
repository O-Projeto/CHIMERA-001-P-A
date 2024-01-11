//
// Created by Braum on 23/12/23.
//


extern "C" {
#include "esp_event.h"
#include "esp_console.h"
}

#include <cstdio>
#include <memory>
#include <algorithm>

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
     * TODO: Implement Argument Parser
     * TODO: Create servo_controller command with 4 arguments: x, y, z, leg_idx
     *
    */

    try {
        const chimera::nvs subsystem_nvs{};
        const chimera::console subsystem_console{};

        const std::array<const esp_console_cmd_t, 1> command_list{
            chimera::command::servo_command()
        };

        std::ranges::for_each(command_list, [](const esp_console_cmd_t&command) {
            chimera::console::register_command(command);
        });
    }
    catch (const chimera::exception&ex) {
        print_exception(ex);
        abort();
    }
}
