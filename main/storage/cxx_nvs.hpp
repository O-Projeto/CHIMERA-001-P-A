//
// Created by Braum on 27/12/23.
//

#ifndef CXX_NVS_H
#define CXX_NVS_H

namespace chimera {
    // NVS Class Wrapper over ESP-IDF C function calls
    class nvs {
    public:
        explicit nvs();

        nvs(const nvs&other) = delete;

        nvs(nvs&&other) = delete;

        nvs& operator=(const nvs&other) = delete;

        nvs& operator=(nvs&&other) = delete;

        ~nvs() noexcept;
    };
}
#endif //CXX_NVS_H
