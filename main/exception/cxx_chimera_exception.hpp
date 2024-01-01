//
// Created by Braum on 31/12/23.
//

#ifndef CHIMERA_EXCEPTION_HPP
#define CHIMERA_EXCEPTION_HPP

extern "C" {
#include "esp_err.h"
}

#include <exception>

namespace chimera_exception {
    class exception final : public std::exception {
    public:
        /**
         * @param error ESP-IDF error code.
         * @param message ESP-IDF error message.
         * @param reason CHIMERA exception message.
         */
        exception(esp_err_t error, const char* message, const char* reason);

        /**
         * @return The ESP-IDF error message.
         */
        const char* what() const noexcept override;

        /**
         * \return The ESP-IDF error code.
         */
        esp_err_t code() const noexcept;

        /**
        * \return The CHIMERA detailed message for the exception to be thrown.
        */
        const char* reason() const noexcept;

    private:
        esp_err_t esp_error{};
        const char* esp_message;
        const char* chimera_reason;
    };
}

#endif //CHIMERA_EXCEPTION_HPP
