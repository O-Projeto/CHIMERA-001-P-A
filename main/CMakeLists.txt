idf_component_register(
        SRCS
        "main.cpp"
        "storage/cxx_nvs.hpp"
        "storage/cxx_nvs.cpp"
        "exception/cxx_exception.hpp"
        "exception/cxx_exception.cpp"
        "servo_controller/ik.hpp"
        "servo_controller/ik.cpp"
        "servo_controller/servo_drive.hpp"
        "servo_controller/servo_drive.cpp"
        "servo_controller/servo_controller.cpp"
        "console/cxx_console.hpp"
        "console/cxx_console.cpp"
        "command/cxx_command.hpp"
        "command/cxx_command.cpp"
        INCLUDE_DIRS ".")

# Allow all compiler warnings to be displayed
# and restrict all builds to fail in case of warnings
component_compile_options("-Wall")
component_compile_options("-Wextra")
component_compile_options("-Werror")