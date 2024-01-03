//
// Created by Braum on 31/12/23.
//

#include <iostream>

#include "exception/cxx_exception.hpp"

chimera::exception::exception(const esp_err_t error, const char* reason)
    : exception_error{error}, exception_reason{reason} {
}

[[nodiscard]] const char* chimera::exception::what() const noexcept {
    return esp_err_to_name(exception_error);
}

[[nodiscard]] esp_err_t chimera::exception::code() const noexcept {
    return exception_error;
}

[[nodiscard]] const char* chimera::exception::reason() const noexcept {
    return exception_reason;
}


void chimera::print_exception(const exception&ex) noexcept {
    std::cerr <<
            "code:     [" << ex.code() << "]\n"
            "what:     [" << ex.what() << "]\n"
            "reason:   [" << ex.reason() << "]\n";
}
