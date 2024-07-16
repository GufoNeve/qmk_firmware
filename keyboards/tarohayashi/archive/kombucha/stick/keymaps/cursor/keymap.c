// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"

// LAYERS
enum layer_number {
    BASE = 0,
    LOWER,
    UPPER,
    LIGHT,
};

// KEYCODES
enum cursor_keycodes{
    BALL_SAFE_RANGE = SAFE_RANGE,
    REV_X,
    REV_Y,
    CHAN_XY,
};

typedef union {
    uint32_t raw;
    struct {
        bool reverse_x;
        bool reverse_y;
        bool x_y;
    };
} cursorconfig_t;

cursorconfig_t cursorconfig;

// LAYOUT SETTINGS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
        KC_A, KC_B,
        KC_C, KC_D, KC_E,
        KC_F, KC_G, KC_H,
        KC_I, LT(UPPER, KC_J), LT(LIGHT, KC_K),

            KC_W,
        KC_A,   KC_D,
            KC_S
    ),
  [LOWER] = LAYOUT(
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

            XXXXXXX,
        XXXXXXX, XXXXXXX,
            XXXXXXX
    ),
  [UPPER] = LAYOUT(
        XXXXXXX, XXXXXXX,
        REV_X,XXXXXXX, XXXXXXX,
        REV_Y, CHAN_XY, XXXXXXX,
        XXXXXXX, LT(UPPER, KC_J), XXXXXXX,

            XXXXXXX,
        XXXXXXX, XXXXXXX,
            XXXXXXX
    ),
  [LIGHT] = LAYOUT(
        RGB_TOG, XXXXXXX,
        RGB_SAI, RGB_VAI, RGB_SPI,
        RGB_SAD, RGB_VAD, RGB_SPD,
        RGB_MOD, RGB_RMOD, LT(LIGHT, KC_K),

            XXXXXXX,
        XXXXXXX, XXXXXXX,
            XXXXXXX
    )
};
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [LOWER] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [UPPER] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [LIGHT] = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD)},
};


void keyboard_post_init_user(void) {
    cursorconfig.raw = eeconfig_read_user();
}


void eeconfig_init_user(void) {
    cursorconfig.reverse_x = false;
    cursorconfig.reverse_y = false;
    cursorconfig.x_y = false;
    eeconfig_update_kb(cursorconfig.raw);
}



bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == REV_X && record->event.pressed) {
        cursorconfig.reverse_x = !cursorconfig.reverse_x;
        eeconfig_update_user(cursorconfig.raw);
    }
    if (keycode == REV_Y && record->event.pressed) {
        cursorconfig.reverse_y = !cursorconfig.reverse_y;
        eeconfig_update_user(cursorconfig.raw);
    }
    if (keycode == CHAN_XY && record->event.pressed) {
        cursorconfig.x_y = !cursorconfig.x_y;
        eeconfig_update_user(cursorconfig.raw);
    }
    return true;
}


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int8_t x_rev = mouse_report.x;
    int8_t y_rev = mouse_report.y;
    if(cursorconfig.reverse_x){
        x_rev = -1 * x_rev;
    }
    if(cursorconfig.reverse_y){
        y_rev = -1 * y_rev;
    }
    if(cursorconfig.x_y){
        mouse_report.x = y_rev;
        mouse_report.y = x_rev;
    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
    }
    return mouse_report;
}
