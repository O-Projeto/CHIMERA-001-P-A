//
// Created by Braum on 05/01/24.
//

#ifndef CXX_COMMAND_HPP
#define CXX_COMMAND_HPP

extern "C" {
#include <esp_console.h>
}

namespace chimera::command {
        esp_console_cmd_t servo_command();

        int servo_function(int argc, char** argv);
}

#endif //CXX_COMMAND_HPP
