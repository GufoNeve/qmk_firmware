// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"

enum layer_names {
  BASE = 0,
  LOWER,
  UPPER,
  LIGHT = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_KP_SLASH,     KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_BSPC,
    KC_KP_ASTERISK,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_TAB,
    KC_KP_MINUS,     KC_KP_1,  KC_KP_2,  KC_KP_3,  LT(UPPER, KC_KP_ENTER),
    LT(LOWER, KC_KP_PLUS),    KC_KP_0,            KC_KP_DOT
  ),
  [LOWER] = LAYOUT(
    XXXXXXX,  KC_HOME, KC_UP,    KC_PGUP,  XXXXXXX,
    XXXXXXX,  KC_LEFT, XXXXXXX,  KC_RGHT,  XXXXXXX,
    XXXXXXX,  KC_END , KC_DOWN,  KC_PGDN,  MO(LIGHT),
    XXXXXXX,  KC_INS ,           KC_DEL
  ),
  [UPPER] = LAYOUT(
    XXXXXXX,  LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),  XXXXXXX,
    XXXXXXX,  LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),  XXXXXXX,
    XXXXXXX,  LSFT(KC_1),LSFT(KC_2),LSFT(KC_3),  XXXXXXX,
    MO(LIGHT),    LSFT(KC_0),              XXXXXXX
  ),
  [LIGHT] = LAYOUT(
    RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  RGB_TOG,
    RGB_RMOD, XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_MOD,
    RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  XXXXXXX,
    XXXXXXX,      XXXXXXX,        XXXXXXX
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}