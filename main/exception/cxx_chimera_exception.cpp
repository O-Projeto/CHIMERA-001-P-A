//
// Created by Braum on 31/12/23.
//

#include <iostream>

#include "exception/cxx_chimera_exception.hpp"

chimera_exception::exception::exception(const esp_err_t error, const char* reason)
    : exception_error{error}, exception_reason{reason} {
}

const char* chimera_exception::exception::what() const noexcept {
    return esp_err_to_name(exception_error);
}

esp_err_t chimera_exception::exception::code() const noexcept {
    return exception_error;
}

const char* chimera_exception::exception::reason() const noexcept {
    return exception_reason;
}


void chimera_exception::print_exception(const exception&ex) noexcept {
    std::cerr <<
            "code:     [" << ex.code() << "]\n"
            "what:     [" << ex.what() << "]\n"
            "reason:   [" << ex.reason() << "]\n";
}
