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
        KC_BSPC,  LT(LOWER, KC_T),   KC_SPC,  KC_ENT,
        G(KC_V),   KC_R,   KC_F,   KC_V,
        G(KC_C),   KC_E,   KC_D,   KC_C,
        KC_TAB,   KC_W,   KC_S,   KC_X,
        LT(LIGHT, KC_ESC), KC_Q, LGUI_T(KC_A), LSFT_T(KC_Z)
    ),
    [LOWER] = LAYOUT(
        KC_F9, LT(LOWER, KC_T), XXXXXXX, XXXXXXX,
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
        LT(LIGHT, KC_ESC), RGB_MOD, RGB_RMOD, QK_BOOT
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