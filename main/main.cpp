//
// Created by Braum on 23/12/23.
//
extern "C" {
#include "esp_event.h"
#include "esp_console.h"
}

#include <cstdio>
#include <memory>

#include "console/cxx_console.hpp"
#include "esp_event_cxx.hpp"
#include "storage/cxx_nvs.hpp"
#include "exception/cxx_exception.hpp"

/*
 * This is the command entrypoint function, change the code below to make any modifications.
 * NOTE: The console component requires the function signature to be int (int argc, char** argv),
 * without this signature the console will be unable to register the function, and the code won't
 * compile.
 */
int servo_function(int argc, char** argv) {
    if (argv[1]) {
        auto value = std::stoi(argv[1]);
        value++;
        fprintf(stdout, "%d\n", value);
    }
    else {
        fprintf(stdout, "missing argument, command won't run\n");
    }
    return 0;
}

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
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

    // Register servo command
    constexpr esp_console_cmd_t servo_command{
        "servo",
        "Run servo controller",
        nullptr,
        &servo_function,
        nullptr,
    };

    chimera::console::register_command(servo_command);
}
