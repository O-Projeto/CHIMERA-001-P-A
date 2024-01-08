//
// Created by Braum on 27/12/23.
//

extern "C" {
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#include "exception/cxx_exception.hpp"
#include "cxx_nvs.hpp"

chimera::nvs::nvs() {
    esp_err_t err{nvs_flash_init()};
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        if (const esp_err_t erase{nvs_flash_erase()}; erase != ESP_OK) {
            throw exception(erase, "Breach of NVS Flash Erase Invariant");
        }
        err = nvs_flash_init();
    }
    if (err != ESP_OK) {
        throw exception(err, "Breach of NVS Flash Invariant");
    }
}

chimera::nvs::~nvs() noexcept {
    if (const esp_err_t err{nvs_flash_deinit()}; err != ESP_OK) {
        fprintf(stderr, "Failed to de-initialize NVS with code %s, retrying", esp_err_to_name(err));
        if (const esp_err_t retry_err{nvs_flash_deinit()}; retry_err != ESP_OK) {
            fprintf(stderr, "Retry NVS de-initialization failed with code %s, exiting", esp_err_to_name(retry_err));
        }
    }
}
