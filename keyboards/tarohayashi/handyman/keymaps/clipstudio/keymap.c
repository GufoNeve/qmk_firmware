// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum custom_keycode {
  CLIPSTUDIO = 0,
  PHOTOSHOP,
  KICAD,
  LIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CLIPSTUDIO] = LAYOUT(
          G(KC_S), G(KC_L), KC_H, G(KC_X), KC_BSPC,
        LSG(KC_I), G(KC_U), G(KC_T),  G(KC_D), LSG(KC_X),
        KC_O, G(KC_0), G(KC_Z), KC_9, LSG(KC_C),
        KC_U, KC_R, KC_Y, KC_I, LAG(KC_0),
        G(KC_4), LT(LIGHT, KC_M), LALT_T(KC_A), GUI_T(KC_B), LSFT_T(KC_P),
        // LEVER
        KC_T, KC_G, KC_J
  ),
  [PHOTOSHOP] = LAYOUT(
        G(KC_S), G(KC_C), G(KC_V), G(KC_X), KC_BSPC,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [KICAD] = LAYOUT(
        G(KC_S), G(KC_C), G(KC_V), G(KC_X), KC_BSPC,
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
  )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(LCTL(KC_KP_PLUS),LCTL(KC_KP_MINUS)), ENCODER_CCW_CW(KC_2,KC_1), ENCODER_CCW_CW(KC_MINS, KC_QUOT)  },
    [1] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =  { ENCODER_CCW_CW(_______, _______),                   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};

