//
// Created by Braum on 27/12/23.
//

#ifndef CXX_NVS_H
#define CXX_NVS_H

namespace nvs {
    // NVS Class Wrapper over ESP-IDF C function calls
    class manager {
    public:
        manager();

        manager(const manager&other) = delete;

        manager(manager&&other) = delete;

        manager& operator=(const manager&other) = delete;

        manager& operator=(manager&&other) = delete;

        ~manager() noexcept;
    };
}

#endif //CXX_NVS_H
