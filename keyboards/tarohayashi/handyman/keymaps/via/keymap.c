// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum custom_keycode {
  BASE = 0,
  LOWER,
  UPPER,
  LIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
        LCTL(KC_S), LCTL(KC_L), RCS(KC_N), LCTL(KC_U), KC_BSPC,
        LSFT(KC_F7), LCTL(KC_M), LCTL(KC_T), KC_M, LCTL(KC_D),
        KC_X, KC_F13, LCTL(KC_Z), KC_F14, LCTL(KC_0),
        KC_O, KC_S, KC_Y, KC_I, KC_F15,
        LCTL(KC_H), LT(LIGHT, KC_U), LALT_T(KC_E), LCTL_T(KC_B), LSFT_T(KC_P),
        // LEVER
        KC_T, KC_G, KC_J
  ),
  [LOWER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [UPPER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX
  ),
[LIGHT] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_MOD, RGB_TOG, RGB_RMOD,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(LCTL(KC_KP_PLUS),LCTL(KC_KP_MINUS)), ENCODER_CCW_CW(KC_RBRC, KC_LBRC), ENCODER_CCW_CW(KC_MINS, KC_QUOT)  },
    [1] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};