// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes{
    SEND_01 = SAFE_RANGE,
             SEND_02, SEND_03, SEND_04, SEND_05, SEND_06, SEND_07, SEND_08, SEND_09, SEND_10,
    SEND_11, SEND_12, SEND_13, SEND_14, SEND_15
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* NONE */
                 SEND_01, SEND_02, SEND_03, SEND_04,
        SEND_05, SEND_06, SEND_07, SEND_08,
                 SEND_09, SEND_10, SEND_11, SEND_12,
        SEND_13, SEND_14, SEND_15
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
                 _______, _______, _______,  _______,
        _______, _______, _______, _______,
                 _______, _______, _______, _______,
        // LEVER
        _______, _______, _______
  ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(KC_A, KC_B),       ENCODER_CCW_CW(KC_C, KC_D),       ENCODER_CCW_CW(KC_E, KC_F)  },
    [1] =  { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =  { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =  { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_01: if (record->event.pressed) SEND_STRING("01 "); break;
    case SEND_02: if (record->event.pressed) SEND_STRING("02 "); break;
    case SEND_03: if (record->event.pressed) SEND_STRING("03 "); break;
    case SEND_04: if (record->event.pressed) SEND_STRING("04 "); break;
    case SEND_05: if (record->event.pressed) SEND_STRING("05 "); break;
    case SEND_06: if (record->event.pressed) SEND_STRING("06 "); break;
    case SEND_07: if (record->event.pressed) SEND_STRING("07 "); break;
    case SEND_08: if (record->event.pressed) SEND_STRING("08 "); break;
    case SEND_09: if (record->event.pressed) SEND_STRING("09 "); break;
    case SEND_10: if (record->event.pressed) SEND_STRING("10 "); break;
    case SEND_11: if (record->event.pressed) SEND_STRING("11 "); break;
    case SEND_12: if (record->event.pressed) SEND_STRING("12 "); break;
    case SEND_13: if (record->event.pressed) SEND_STRING("13 "); break;
    case SEND_14: if (record->event.pressed) SEND_STRING("14 "); break;
    case SEND_15: if (record->event.pressed) SEND_STRING("15 "); break;
  }
  return true;
}
