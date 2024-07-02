// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                    LSG(KC_S), KC_HOME, KC_END,  KC_BSPC,
        LCTL(KC_0), KC_BTN1,   KC_UP,   KC_BTN2,
                    KC_LEFT,   KC_DOWN, KC_RGHT, LT(5, KC_ENT),
        // LEVER
        RCS(KC_TAB), _______, LCTL(KC_TAB)
  ),
  [1] = LAYOUT(
                 _______, _______, _______,  _______,
        _______, _______, _______, _______,
                 _______, _______, _______, _______,
        // LEVER
        _______, _______, _______

  ),
  [2] = LAYOUT(
                 _______, _______, _______,  _______,
        _______, _______, _______, _______,
                 _______, _______, _______, _______,
        // LEVER
        _______, _______, _______
  ),
  [3] = LAYOUT(
                 RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD,
        RGB_TOG, _______, RGB_MOD, _______,
                 RGB_HUD, RGB_SAD, RGB_VAD, LT(5, KC_ENT),
        RGB_SPI, _______, RGB_SPD
  ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(LCTL(KC_KP_PLUS),LCTL(KC_KP_MINUS)), ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(KC_WH_L, KC_WH_R)  },
    [1] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
};
