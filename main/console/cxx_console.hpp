//
// Created by Braum on 04/01/24.
//

#ifndef CXX_CONSOLE_HPP
#define CXX_CONSOLE_HPP

extern "C" {
#include "esp_console.h"
}

#include <memory>

namespace chimera {
    class console {
    public:
        explicit console();

        console(const console&other) = delete;

        console(console&&other) = delete;

        console& operator=(const console&other) = delete;

        console& operator=(console&&other) = delete;

        static void register_command(const esp_console_cmd_t& command);

    private:
        std::unique_ptr<esp_console_repl_t *> console_ptr;
        const esp_console_repl_config_t console_config{
            32,
            nullptr,
            4096,
            2,
            "CHIMERA-001-P-A >",
            0
        };
    };
}

#endif //CXX_CONSOLE_HPP
