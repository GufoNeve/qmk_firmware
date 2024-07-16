// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

// キーマップ
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        // Side0
        MO(4), MO(6), 
        KC_A, KC_B, KC_C, KC_D, 
        KC_X, 
        // Side1
        MO(5), MO(7), 
        KC_E, KC_F, KC_G, KC_H, 
        KC_Y        
    ),
    // AUTO MOUSE
    [1] = LAYOUT(
        // Side0
        KC_MS_BTN1, KC_MS_BTN2, 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        KC_MS_BTN2, KC_MS_BTN1, 
        _______, _______, _______, _______, 
        _______        
    ),
    [2] = LAYOUT(
        // Side0
        _______,  _______,  
        _______, _______, _______, _______, 
        _______, 
        // Side1
        _______,  _______,  
        _______, _______, _______, _______, 
        _______        
    ),
    [3] = LAYOUT(
        // Side0
        _______, _______,  
        _______, _______, _______, _______, 
        _______, 
        // Side1
        _______,  _______,  
        _______, _______, _______, _______, 
        _______        
    ),
    [4] = LAYOUT(
        // Side0
        _______, MO(8), 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        SPD_I_1, SPD_D_1, 
        _______, _______, _______, _______, 
        _______        
    ),
    [5] = LAYOUT(
        // Side0
        SPD_I_0, SPD_D_0, 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        _______, MO(9), 
        _______, _______, _______, _______, 
        _______        
    ),
    [6] = LAYOUT(
        // Side0
        MO(8), _______, 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        ANG_I_1, ANG_D_1, 
        _______, _______, _______, _______, 
        _______        
    ),
    [7] = LAYOUT(
        // Side0
        ANG_I_0, ANG_D_0, 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        MO(9),    _______, 
        _______, _______, _______, _______, 
        _______        
    ),
    [8] = LAYOUT(
        // Side0
        _______, _______, 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        CHMOD_1, INV_1, 
        _______, _______, _______, _______, 
        _______        
    ),
    [9] = LAYOUT(
        // Side0
        CHMOD_0, INV_0, 
        _______, _______, _______, _______, 
        _______, 
        // Side1
        _______, _______, 
        _______, _______, _______, _______, 
        _______        
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [1] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [2] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [3] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [4] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [5] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [6] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [7] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [8] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [9] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    }
};
