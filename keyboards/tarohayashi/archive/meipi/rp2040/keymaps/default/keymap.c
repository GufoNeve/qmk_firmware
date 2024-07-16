// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "joystick.h"
#include "analog.h"

enum custom_keycode {
  BASE = 0,
  LOWER,
  UPPER,
  LIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
        KC_CAPS, KC_NUM, MO(LIGHT),
        KC_C, KC_V, KC_S
  ),
  [LOWER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX

  ),
  [UPPER] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [LIGHT] = LAYOUT(
        RGB_HUI, RGB_MOD, MO(LIGHT),
        RGB_HUD, XXXXXXX, XXXXXXX
  )
};

const char* pressedkey = " ";

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode){
        case KC_CAPS:
            if (record->event.pressed) {
                pressedkey = "CAPSLOCK";
            }
            break;
        case KC_NUM:
            if (record->event.pressed) {
                pressedkey = "NUMLOCK";
            }
            break;
        case MO(LIGHT):
            if (record->event.pressed) {
                pressedkey = "FN";
            }
            break;
        case KC_C:
            if (record->event.pressed) {
                pressedkey = "CUSTOMER";
            }
            break;
        case KC_V:
            if (record->event.pressed) {
                pressedkey = "VALUE";
            }
            break;
        case KC_S:
            if (record->event.pressed) {
                pressedkey = "SERVICE";
            }
            break;
        case RGB_HUI:
            if (record->event.pressed) {
                pressedkey = "INCREASE HUE";
            }
            break;
        case RGB_HUD:
            if (record->event.pressed) {
                pressedkey = "DECREASE HUE";
            }
            break;
        case RGB_MOD:
            if (record->event.pressed) {
                pressedkey = "CHANGE RGB MODE";
            }
            break;
    }
    return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            tap_code16(KC_WH_U);
            pressedkey = "CLOCKWISE";
        } else {
            tap_code16(KC_WH_D);
            pressedkey = "COUNTER CLOCKWISE";
        }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    oled_write_P(PSTR("meipi"), false);
    oled_set_cursor(0,3);
    oled_write_ln(pressedkey, false);
    return false;
}

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL,
    [2] = JOYSTICK_AXIS_VIRTUAL,
    [3] = JOYSTICK_AXIS_VIRTUAL
};


void joystick_task(){
    if(analogReadPin(GP28) - 350 > 175){
        register_code16(KC_WH_R);
        pressedkey = "J1 RIGHT";
    }else if(analogReadPin(GP28) - 350 < 175){
        unregister_code16(KC_WH_R);
    }
    if(analogReadPin(GP28) - 350 < -175){
        register_code16(KC_WH_L);
        pressedkey = "J1 LEFT";
    }else if(analogReadPin(GP28) - 350 > -175){
        unregister_code16(KC_WH_L);
    }
     if(analogReadPin(GP29) - 350 > 175){
        register_code16(KC_WH_U);
        pressedkey = "J1 UP";
    }else if(analogReadPin(GP29) - 350 < 175){
        unregister_code16(KC_WH_U);
    }
    if(analogReadPin(GP29) - 350 < -175){
        register_code16(KC_WH_D);
        pressedkey = "J1 DOWN";
    }else if(analogReadPin(GP29) - 350 > -175){
        unregister_code16(KC_WH_D);
    }
     if(analogReadPin(GP26) - 350 > 175){
        register_code16(KC_RGHT);
        pressedkey = "J0 RIGHT";
    }else if(analogReadPin(GP26) - 350 < 175){
        unregister_code16(KC_RGHT);
    }
    if(analogReadPin(GP26) - 350 < -175){
        register_code16(KC_LEFT);
        pressedkey = "J0 LEFT";
    }else if(analogReadPin(GP26) - 350 > -175){
        unregister_code16(KC_LEFT);
    }
     if(analogReadPin(GP27) - 350 > 175){
        register_code16(KC_UP);
        pressedkey = "J0 UP";
    }else if(analogReadPin(GP27) - 350 < 175){
        unregister_code16(KC_UP);
    }
    if(analogReadPin(GP27) - 350 < -175){
        register_code16(KC_DOWN);
        pressedkey = "J0 DOWN";
    }else if(analogReadPin(GP27) - 350 > -175){
        unregister_code16(KC_DOWN);
    }
}

