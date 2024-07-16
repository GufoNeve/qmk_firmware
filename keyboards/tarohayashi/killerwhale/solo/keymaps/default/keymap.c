// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, 
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J,
        KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
        KC_U, KC_V, KC_W, KC_X
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_C);
        } else {
            tap_code(KC_D);
        }
    } else if (index == 2) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_E);
        } else {
            tap_code(KC_F);
        }
    } else if (index == 3) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_G);
        } else {
            tap_code(KC_H);
        }
    }
    return false;
}