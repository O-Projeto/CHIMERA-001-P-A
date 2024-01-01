//
// Created by Braum on 27/12/23.
//

extern "C" {
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#include "exception/cxx_chimera_exception.hpp"
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
            throw chimera_exception::exception(erase, esp_err_to_name(erase),
                                               "Breach of NVS Flash Erase Invariant");
        }
        spdlog::debug("NVS partition has been erased");
        spdlog::debug("Attempting to re-initialize NVS after flashing NVS");
        err = nvs_flash_init();
    }
    if (err != ESP_OK) {
        throw chimera_exception::exception(err, esp_err_to_name(err), "Breach of NVS Flash Invariant");
    }
    spdlog::debug("NVS Initialized");
}

NVS::Manager::~Manager() noexcept {
    spdlog::debug("Attempting to de-initialize NVS");
    if (const esp_err_t err{nvs_flash_deinit()}; err != ESP_OK) {
        spdlog::error("Failed to de-initialize NVS, with code {}, retrying", esp_err_to_name(err));
        if (const esp_err_t retry_err{nvs_flash_deinit()}; retry_err != ESP_OK) {
            spdlog::error("Retry NVS initialization failed, with code {}, exiting", esp_err_to_name(retry_err));
        }
    }
    else {
        spdlog::debug("NVS De-initialized");
    }
}
