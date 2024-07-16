// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"

enum layer_names {
    BASE = 0,
    LOWER,
    UPPER,
    LIGHT = 5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_TAB, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7, KC_P8, KC_P9, KC_PPLS,
        KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_P1, KC_P2, KC_P3, KC_PENT,
        KC_P0, KC_PDOT, KC_PDOT, LT(LIGHT, KC_PENT)
    ),
    [LIGHT] = LAYOUT(
        XXXXXXX, RGB_SPI, RGB_SPD, RGB_TOG,
        XXXXXXX, RGB_VAI, RGB_VAD, XXXXXXX,
        XXXXXXX, RGB_SAI, RGB_SAD, XXXXXXX,
        XXXXXXX, RGB_HUI, RGB_HUD, XXXXXXX,
        XXXXXXX, RGB_MOD, RGB_RMOD, LT(LIGHT, KC_PENT)
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   { 
        ENCODER_CCW_CW(KC_A, KC_B), 
        ENCODER_CCW_CW(KC_C, KC_D), 
        ENCODER_CCW_CW(KC_E, KC_F), 
        ENCODER_CCW_CW(KC_G, KC_H), 
        ENCODER_CCW_CW(KC_I, KC_J)
        },
    [LIGHT] = { 
        ENCODER_CCW_CW(RGB_SPI, RGB_SPD),
        ENCODER_CCW_CW(RGB_VAI, RGB_VAD), 
        ENCODER_CCW_CW(RGB_SAI, RGB_SAD), 
        ENCODER_CCW_CW(RGB_HUI, RGB_HUD), 
        ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)
        }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}
