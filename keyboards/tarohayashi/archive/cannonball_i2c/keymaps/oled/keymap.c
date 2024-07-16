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
                    CAPTCHA, PASTE, COPY,  KC_BSPC,
        SC_RESET, SAVE,   KC_UP,   SAVEAS,
                    KC_LEFT,   KC_DOWN, KC_RGHT, LT(LIGHT, KC_ENT),
        // LEVER
        PREVTAB, CLOSETAB, NEXTTAB
  ),
  [LIGHT] = LAYOUT(
                 RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD,
        RGB_TOG, XXXXXXX, RGB_MOD, XXXXXXX,
                 RGB_HUD, RGB_SAD, RGB_VAD, LT(LIGHT, KC_ENT),
        // LEVER
        RGB_SPI, XXXXXXX, RGB_SPD
  )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   {
      ENCODER_CCW_CW(SC_UP, SC_DOWN), 
      ENCODER_CCW_CW(KC_WH_U, KC_WH_D), 
      ENCODER_CCW_CW(KC_WH_L, KC_WH_R)
      },
    [LIGHT] = { 
      ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), 
      ENCODER_CCW_CW(RGB_VAI, RGB_VAD), 
      ENCODER_CCW_CW(RGB_HUI, RGB_HUD)
      }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}

