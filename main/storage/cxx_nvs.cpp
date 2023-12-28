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
        spdlog::debug("Attempting to erase NVS partition");
        if (const int erase{nvs_flash_erase()}; erase != ESP_OK) {
            spdlog::error("Failed to erase NVS partition with code {}, exiting", esp_err_to_name(erase));
        }
        else {
            spdlog::debug("NVS partition has been erased");
            spdlog::debug("Attempting to re-initialize NVS after flashing NVS");
            err = nvs_flash_init();
        }
    }
    if (err != ESP_OK) {
        spdlog::error("Failed to initialize NVS, with code {}, exiting", esp_err_to_name(err));
    }
    spdlog::debug("NVS Initialized");
}

NVS::Manager::~Manager() {
    spdlog::debug("Attempting to de-initialize NVS");
    if (const esp_err_t err{nvs_flash_deinit()}; err != ESP_OK) {
        spdlog::error("Failed to de-initialize NVS, with code {}, retrying", esp_err_to_name(err));
        if (const esp_err_t retry_err{nvs_flash_deinit()}; retry_err != ESP_OK) {
            spdlog::error("Retry NVS initialization failed, with code {}, exiting", esp_err_to_name(retry_err));
        }
    }
    else if (err == ESP_OK) {
        spdlog::debug("NVS De-initialized");
    }
}

