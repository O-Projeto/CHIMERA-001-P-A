//
// Created by Braum on 31/12/23.
//

#include <iostream>

#include "exception/cxx_chimera_exception.hpp"

chimera_exception::exception::exception(const esp_err_t error, const char* message)
    : error{error}, message{message} {
}

const char* chimera_exception::exception::what() const noexcept {
    return esp_err_to_name(error);
}

esp_err_t chimera_exception::exception::code() const noexcept {
    return error;
}

const char* chimera_exception::exception::reason() const noexcept {
    return message;
}


void chimera_exception::print_exception(const exception&ex) noexcept {
    using namespace std;

    std::cerr <<
            "code:     [" << ex.code() << "]\n"
            "what:     [" << ex.what() << "]\n"
            "reason:   [" << ex.reason() << "]\n";
}
