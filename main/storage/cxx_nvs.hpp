//
// Created by Braum on 27/12/23.
//

#ifndef CXX_NVS_H
#define CXX_NVS_H

namespace NVS {
    // NVS Class Wrapper over ESP-IDF C function calls
    class Manager {
    public:
        // TODO: Estabilish Invariants for NVS initialization
        Manager();

        Manager(const Manager& other) = delete;

        Manager(Manager&& other) = delete;

        Manager& operator=(const Manager& other) = delete;

        Manager& operator=(Manager&& other) = delete;

        // TODO: Estabilish NVS de-initialization
        ~Manager() = default;
    };
}

#endif //CXX_NVS_H
