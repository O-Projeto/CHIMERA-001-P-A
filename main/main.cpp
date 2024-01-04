//
// Created by Braum on 23/12/23.
//
extern "C" {
#include "esp_event.h"
#include "esp_console.h"
}

#include <cstdio>
#include <memory>

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
    // NVS Driver Initialization Block
    try {
        chimera::nvs::manager();
    }
    // NOTE: Keep this disabled until ReSharper is fixed
    // ReSharper disable once CppDFAUnreachableCode
    catch (const chimera::exception&ex) {
        print_exception(ex);
        abort();
    }

    const std::shared_ptr<esp_console_repl_t *> repl{new esp_console_repl_t *};

    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = "CHIMERA-001-P-A >";

    //Register help command
    if (const esp_err_t err{esp_console_register_help_command()}; err != ESP_OK) {
        fprintf(stderr, "Unable to register help command in the console");
    }

    // Register servo command
    constexpr esp_console_cmd_t servo_command{
        .command = "servo",
        .help = "Run servo controller",
        .hint = nullptr,
        .func = &servo_function,
        .argtable = nullptr,
    };

    if (const esp_err_t err{esp_console_cmd_register(&servo_command)}; err != ESP_OK) {
        fprintf(stderr, "Unable to register servo command in the console");
    }

    constexpr esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    if (const esp_err_t err{esp_console_new_repl_uart(&hw_config, &repl_config, repl.get())}; err != ESP_OK) {
        fprintf(stderr, "Unable to establish REPL environment");
    }

    if (const esp_err_t err{esp_console_start_repl(*repl)}; err != ESP_OK) {
        fprintf(stderr, "Unable to start REPL environment");
    }
}
