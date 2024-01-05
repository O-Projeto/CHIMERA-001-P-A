//
// Created by Braum on 04/01/24.
//

#include "exception/cxx_exception.hpp"
#include "cxx_console.hpp"

chimera::console::console() : console_ptr{new esp_console_repl_t *} {
    constexpr esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    if (const esp_err_t err{esp_console_new_repl_uart(&hw_config, &console_config, console_ptr.get())}; err != ESP_OK) {
        throw exception(err, "Breach of REPL Environment UART Invariant");
    }
    if (const esp_err_t err{esp_console_start_repl(*console_ptr)}; err != ESP_OK) {
        throw exception(err, "Breach of REPL Environment Start Invariant");
    }

    if (const esp_err_t err{esp_console_register_help_command()}; err != ESP_OK) {
        throw exception(err, "Breach of REPL Environment Help Command Invariant");
    }
}

void chimera::console::register_command(const esp_console_cmd_t&command) {
    if (const esp_err_t err{esp_console_cmd_register(&command)}; err != ESP_OK) {
        throw exception(err, "Breach of REPL Register Invariant");
    }
}
