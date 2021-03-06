// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string.h>
#include "unity.h"
#include "dsp_platform.h"
#include "esp_log.h"

#include "dsps_add.h"
#include "esp_attr.h"

static const char *TAG = "dsps_add";

TEST_CASE("dsps_add_s16_ansi functionality", "[dsps]")
{
    int n = 64;
    int16_t x[n];
    int16_t y[n];
    int32_t temp;
    int shift = 0;
    for (int i = 0 ; i < n ; i++) {
        x[i] = i<<4;
        temp = ((int32_t)x[i] + (int32_t)x[i])>>shift;
        y[i] = temp;
    }
    
    dsps_add_s16_ansi(x, x, x, n, 1, 1, 1, 0);
    for (int i = 0 ; i < n ; i++) {
        if (x[i] != y[i]) {
            TEST_ASSERT_EQUAL(x[i], y[i]);
        }
    }
}

TEST_CASE("dsps_add_s16_ansi benchmark", "[dsps]")
{
    const int n = 256;
    int16_t x[n];
    int16_t y[n];
    int32_t temp;
    int16_t test_const = 0x2000;
    for (int i = 0 ; i < n ; i++) {
        x[i] = i<<4;
        temp = (int32_t)x[i]*(int32_t)test_const;
        y[i] = temp >> 15;
    }

    int repeat_count = 1;

    unsigned int start_b = xthal_get_ccount();
    dsps_add_s16_ansi(x, x, x, n, 1, 1, 1, 0);
    unsigned int end_b = xthal_get_ccount();
    
    float cycles = end_b - start_b;
    ESP_LOGI(TAG, "dsps_add_s16_ansi - %f cycles per sample \n", cycles);
}
