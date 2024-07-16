// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"

enum layer_names {
  BASE = 0,
  LOWER,
  LIGHT = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
       KC_F1, KC_F2, KC_F3, KC_F4, LT(LIGHT, KC_F5),
    KC_1,  KC_2,  KC_3,  KC_4,  KC_5, LT(LOWER, KC_GRAVE),
    KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_LSFT
  ),
  [LOWER] = LAYOUT(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,
    KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, LT(LOWER, KC_GRAVE),
    KC_F11, KC_F12,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX
  ),
  [LIGHT] = LAYOUT(
       RGB_RMOD,XXXXXXX,XXXXXXX,RGB_MOD,LT(LIGHT, KC_F5),
    XXXXXXX,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,XXXXXXX,
    RGB_TOG,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,XXXXXXX
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}