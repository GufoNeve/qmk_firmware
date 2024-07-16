// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"

enum layer_names {
  BASE = 0,
  LIGHT = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
          LT(LIGHT, KC_F5), KC_F7, KC_F8, KC_F10, KC_BSPC,
        KC_1,  KC_2,  KC_3,  KC_4,  KC_5, KC_GRV,
        KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_LSFT
    ),
  [LIGHT] = LAYOUT(
        LT(LIGHT, KC_F5),RGB_RMOD,XXXXXXX,XXXXXXX,RGB_MOD,
    XXXXXXX,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,XXXXXXX,
    RGB_TOG,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,XXXXXXX
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}