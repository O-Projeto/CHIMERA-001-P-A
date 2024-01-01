//
// Created by Braum on 31/12/23.
//

#include "exception/cxx_chimera_exception.hpp"

chimera_exception::exception::exception(const esp_err_t error, const char* message) : error{error}, message{message} {
}

const char* chimera_exception::exception::what() const noexcept {
    return message;
}

esp_err_t chimera_exception::exception::code() const noexcept {
    return error;
}
