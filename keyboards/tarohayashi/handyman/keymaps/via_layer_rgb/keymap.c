// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"
#include "add_rgblayers.h"

enum custom_keycode {
  BASE = 0,
  LIGHT = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        SAVE, LCTL(KC_L), RCS(KC_N), LCTL(KC_U), KC_BSPC,
        LSFT(KC_F7), LCTL(KC_M), LCTL(KC_T), KC_M, LCTL(KC_D),
        KC_X, KC_F13, UNDO, KC_F14, SC_RESET,
        KC_O, KC_S, KC_Y, KC_I, KC_F15,
        LCTL(KC_H), LT(LIGHT, KC_U), LALT_T(KC_E), LCTL_T(KC_B), LSFT_T(KC_P),
        // LEVER
        KC_T, KC_G, KC_J
    ),
    [LIGHT] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,
        XXXXXXX, LT(LIGHT, KC_U), RGB_MOD, RGB_TOG, RGB_RMOD,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   {
      ENCODER_CCW_CW(SC_UP, SC_DOWN), 
      ENCODER_CCW_CW(KC_RBRC, KC_LBRC), 
      ENCODER_CCW_CW(KC_MINS, KC_QUOT)
      },
    [LIGHT] = { 
      ENCODER_CCW_CW(RGB_HUI, RGB_HUD), 
      ENCODER_CCW_CW(RGB_VAI, RGB_VAD), 
      ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)
      }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}


void keyboard_post_init_user(void) {
    keyboard_post_init_rgblayers();
}