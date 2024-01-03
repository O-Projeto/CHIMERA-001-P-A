//
// Created by Braum on 23/12/23.
//
#include "esp_event_cxx.hpp"

extern "C" {
#include "esp_event.h"
#include "esp_console.h"
}

#include <cstdio>

#include "storage/cxx_nvs.hpp"
#include "exception/cxx_exception.hpp"
#include "spdlog/spdlog.h"

/*
 * This is the command entrypoint function, change the code below to make any modifications.
 * NOTE: The console component requires the function signature to be int (int argc, char** argv),
 * without this signature the console will be unable to register the function, and the code won't
 * compile.
 */
int servo_function(int argc, char** argv) {
    auto value = std::stoi(argv[1]);
    value++;

    fprintf(stdout, "%d\n", value);
    return 0;
}

// Main task called by FreeRTOS Scheduler after Application Startup
// https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-guides/startup.html
extern "C" void app_main(void) {
    // Global Logging Level Initialization
    spdlog::set_level(spdlog::level::err);

    // NVS Driver Initialization Block
    try {
        chimera::nvs::manager();
    }
    // NOTE: Keep this disabled until ReSharper is fixed
    // ReSharper disable once CppDFAUnreachableCode
    catch (const chimera::exception&ex) {
        print_exception(ex);
    }

    esp_console_repl_t* repl{nullptr};
    constexpr esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();

    /* Register commands */
    esp_console_register_help_command();

    // Register servo command
    constexpr esp_console_cmd_t servo_command{
        .command = "servo",
        .help = "Run the servo with required value.",
        .hint = nullptr,
        .func = &servo_function,
        .argtable = nullptr,
    };
    esp_console_cmd_register(&servo_command);

    constexpr esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    if (const esp_err_t err{esp_console_new_repl_uart(&hw_config, &repl_config, &repl)}; err != ESP_OK) {
        spdlog::error("Unable to establish the REPL environment");
    }

    esp_console_start_repl(repl);
}
