//
// Created by Braum on 05/01/24.
//
#include <string>

#include "cxx_command.hpp"

esp_console_cmd_t chimera::command::servo_command() {
    constexpr esp_console_cmd_t servo_configuration{
        "servo",
        "Run servo controller",
        nullptr,
        &servo_function,
        nullptr,
    };
    return servo_configuration;
}

int chimera::command::servo_function(int argc, char** argv) {
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
