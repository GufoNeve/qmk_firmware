// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    BASE = 0,
    LOWER,
    UPPER,
    LIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_TAB,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        LT(LIGHT, KC_P0), KC_0,   KC_DOT,KC_PENT
    ),
    [LOWER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [UPPER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [LIGHT] = LAYOUT(
        XXXXXXX, RGB_HUI, RGB_HUD, RGB_TOG,
        XXXXXXX, RGB_SAI, RGB_SAD, XXXXXXX,
        XXXXXXX, RGB_VAI, RGB_VAD, XXXXXXX,
        XXXXXXX, RGB_SPI, RGB_SPD, XXXXXXX,
        LT(LIGHT, KC_P0), RGB_MOD, RGB_RMOD, QK_BOOT
    )
};


const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =  {
        ENCODER_CCW_CW(KC_A, KC_B), 
        ENCODER_CCW_CW(KC_C, KC_D),  
        ENCODER_CCW_CW(KC_E, KC_F), 
        ENCODER_CCW_CW(KC_G, KC_H),   
        ENCODER_CCW_CW(KC_I, KC_J)
    },
    [LOWER] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [UPPER] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [LIGHT] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
};
