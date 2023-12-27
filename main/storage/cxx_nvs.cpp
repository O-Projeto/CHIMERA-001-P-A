//
// Created by Braum on 27/12/23.
//

extern "C" {
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#include "spdlog/spdlog.h"
#include "cxx_nvs.hpp"

NVS::Manager::Manager() {
    // Initialize NVS
    spdlog::debug("Attempting to initialize NVS");
    esp_err_t err{nvs_flash_init()};
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        spdlog::warn("NVS partition was truncated with code {}, retrying", esp_err_to_name(err));
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        if (const int erase{nvs_flash_erase()}; erase != ESP_OK) {
            spdlog::error("Failed to erase NVS partition with code {}, exiting", esp_err_to_name(erase));
        }
    }
    if (err = nvs_flash_init(); err != ESP_OK) {
        spdlog::error("Failed to initialize NVS, with code {}, exiting", esp_err_to_name(err));
    }
    spdlog::debug("NVS Initialized");
}
