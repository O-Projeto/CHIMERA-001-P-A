//
// Created by Braum on 31/12/23.
//

#include <iostream>

#include "exception/cxx_chimera_exception.hpp"

chimera_exception::exception::exception(const esp_err_t error, const char* message, const char* reason)
    : esp_error{error}, esp_message{message}, chimera_reason{reason} {
}

const char* chimera_exception::exception::what() const noexcept {
    return esp_message;
}

esp_err_t chimera_exception::exception::code() const noexcept {
    return esp_error;
}

const char* chimera_exception::exception::reason() const noexcept {
    return chimera_reason;
}


void chimera_exception::print_exception(const exception&ex) noexcept {
    using namespace std;

    std::cerr <<
            "code:     [" << ex.code() << "]\n"
            "what:     [" << ex.what() << "]\n"
            "reason:   [" << ex.reason() << "]\n";
}
