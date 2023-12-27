idf_component_register(
        SRCS "main.cpp" "storage/cxx_nvs.cpp" "storage/cxx_nvs.hpp"
        INCLUDE_DIRS ".")

# Allow all compiler warnings to be displayed
# and restrict all builds to fail in case of warnings
component_compile_options("-Wall")
component_compile_options("-Wextra")
component_compile_options("-Werror")