//
// Created by Braum on 27/12/23.
//

extern "C" {
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#include <iostream>
#include "cxx_nvs.hpp"

NVS::Manager::Manager() {
    // Initialize NVS
    std::cout << "Debug: Initializing NVS\n";
    esp_err_t err{nvs_flash_init()};
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        std::cout << "Warning: NVS partition was truncated with code " << esp_err_to_name(err) << ", retrying\n";
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        if (const int erase{nvs_flash_erase()}; erase != ESP_OK) {
            std::cout << "Error: Failed to erase NVS partition with code " << esp_err_to_name(erase) << "\n";
        }
    }
    if (err = nvs_flash_init(); err != ESP_OK) {
        std::cout << "Error: Failed to initialize NVS, with code " << esp_err_to_name(err) << "\n";
    }
    std::cout << "Debug: NVS Initialized\n";
}
