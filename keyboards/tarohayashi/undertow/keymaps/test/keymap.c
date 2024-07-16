// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

// キーマップ
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        // Side0
        KC_5, KC_4, 
        KC_0, KC_1, KC_2, KC_3, 
        KC_6, 
        // Side1
        KC_7, KC_6, 
        KC_0, KC_1, KC_2, KC_3, 
        KC_4        
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
};
