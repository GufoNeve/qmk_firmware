// Copyright 2022 Taro Hayashi (@w_vwbw)
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
      LT(LIGHT, KC_ESC),  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC,
      KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_MINS, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
      KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_SPC,KC_SPC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LT(LOWER, KC_LNG2), LT(UPPER, KC_LNG1),KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, RSFT_T(KC_F7)
    ),
    [LOWER] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, _______, KC_DEL,
      _______, _______, _______, _______, _______, _______, LSFT(KC_9), LSFT(KC_0), _______, _______, _______, _______, _______, _______, KC_QUOT,
      KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,
      KC_LALT, _______, _______, _______, _______, _______, LT(LOWER, KC_LNG2), XXXXXXX, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [UPPER] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
      _______, _______, _______, _______, _______, _______, LSFT(KC_9), LSFT(KC_0), _______, _______, _______, _______, _______, _______, KC_QUOT,
      KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
      KC_LALT, _______, _______, _______, _______, _______, XXXXXXX, LT(UPPER, KC_LNG1), _______, _______, _______, _______, _______, _______, _______
    ),
    [LIGHT] = LAYOUT(
      LT(LIGHT, KC_ESC), RGB_MOD, RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX, XXXXXXX,XXXXXXX,
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, XXXXXXX,XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =  {
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [LOWER] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [UPPER] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [LIGHT] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
};
