// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes{
  SEND_01 = SAFE_RANGE,
           SEND_02, SEND_03, SEND_04, SEND_05, SEND_06, SEND_07, SEND_08, SEND_09, SEND_10,
  SEND_11, SEND_12, SEND_13, SEND_14, SEND_15, SEND_16, SEND_17, SEND_18, SEND_19, SEND_20,
  SEND_21, SEND_22, SEND_23, SEND_24, SEND_25, SEND_26, SEND_27, SEND_28
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* NONE */
        SEND_01, SEND_02, SEND_03, SEND_04, SEND_05,
        SEND_06, SEND_07, SEND_08, SEND_09, SEND_10,
        SEND_11, SEND_12, SEND_13, SEND_14, SEND_15,
        SEND_16, SEND_17, SEND_18, SEND_19, SEND_20,
        SEND_21, SEND_22, SEND_23, SEND_24, SEND_25,
        SEND_26, SEND_27, SEND_28
  )
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
    case SEND_16: if (record->event.pressed) SEND_STRING("16 "); break;
    case SEND_17: if (record->event.pressed) SEND_STRING("17 "); break;
    case SEND_18: if (record->event.pressed) SEND_STRING("18 "); break;
    case SEND_19: if (record->event.pressed) SEND_STRING("19 "); break;
    case SEND_20: if (record->event.pressed) SEND_STRING("20 "); break;
    case SEND_21: if (record->event.pressed) SEND_STRING("21 "); break;
    case SEND_22: if (record->event.pressed) SEND_STRING("22 "); break;
    case SEND_23: if (record->event.pressed) SEND_STRING("23 "); break;
    case SEND_24: if (record->event.pressed) SEND_STRING("24 "); break;
    case SEND_25: if (record->event.pressed) SEND_STRING("25 "); break;
    case SEND_26: if (record->event.pressed) SEND_STRING("26 "); break;
    case SEND_27: if (record->event.pressed) SEND_STRING("27 "); break;
    case SEND_28: if (record->event.pressed) SEND_STRING("28 "); break;
  }
  return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_C);
        } else {
            tap_code(KC_D);
        }
    } else if (index == 2) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_E);
        } else {
            tap_code(KC_F);
        }
    }
    return false;
}