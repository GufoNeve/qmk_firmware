// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define CPI_OPTIONS { 950 }
#define CPI_DEFAULT 0
#define ANGLE_OPTIONS { 215 }
#define ANGLE_DEFAULT 0

typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi_idx;
        uint8_t angle_idx;
    };
} ballconfig_t;

// BALL SETTINGS
ballconfig_t ballconfig;
uint8_t cpi;
uint8_t angle;
uint16_t cpi_array[] = CPI_OPTIONS;
uint16_t angle_array[] = ANGLE_OPTIONS;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define ANGLE_OPTION_SIZE (sizeof(angle_array) / sizeof(uint16_t))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
    )
};
