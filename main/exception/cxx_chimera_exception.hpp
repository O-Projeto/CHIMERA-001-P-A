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
         * @param error Chimera custom error code.
         * @param message Detailed error message.
         */
        exception(esp_err_t error, const char* message);

        /**
         * @return A textual representation of the contained error.
         */
        const char* what() const noexcept override;

        /**
         * \return The throwed error code.
         */
        esp_err_t code() const noexcept;

    private:
        esp_err_t error{};
        const char* message;
    };
}

#endif //CHIMERA_EXCEPTION_HPP
