// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include <math.h>


// KEYCODES
enum custom_keycodes{
    PIN_NYURYOKU = SAFE_RANGE,
    PIN1, PIN2, PIN3
};


#define CPI_OPTIONS { 950 }
#define CPI_DEFAULT 0
#define ANGLE_OPTIONS { 215 }
#define ANGLE_DEFAULT 0

// UNION FOR EEPROM
typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi_idx;
        uint8_t angle_idx;
    };
} ballconfig_t;

// BALL SETTINGS
ballconfig_t ballconfig;
uint8_t cpi;
uint8_t angle;
uint16_t cpi_array[] = CPI_OPTIONS;
uint16_t angle_array[] = ANGLE_OPTIONS;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define ANGLE_OPTION_SIZE (sizeof(angle_array) / sizeof(uint16_t))


const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 9, HSV_BLUE}                                 );
const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 1, HSV_MAGENTA}, {1, 1, HSV_BLACK}, {2, 7, HSV_MAGENTA}                      );
const rgblight_segment_t PROGMEM upper_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 9, HSV_GOLD}                         );
const rgblight_segment_t PROGMEM light_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 1, HSV_RED}, { 1, 4, HSV_BLACK}, {5, 2, HSV_RED}, {7, 2, HSV_BLACK}              );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    lower_layer,
    upper_layer,
    light_layer
);

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 1, 2, 3);
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}


// LAYOUT SETTINGS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
        XXXXXXX, XXXXXXX,
        LALT(KC_RIGHT), KC_MS_BTN2, KC_BACKSPACE,
        LALT(KC_LEFT), MO(1), LT(2, KC_ENT),
        KC_MS_BTN1, KC_MS_BTN3, LT(3, KC_SPC)
    ),
  [1] = LAYOUT(
        XXXXXXX, XXXXXXX,
        LCTL(LWIN(KC_LEFT)), XXXXXXX, KC_DELETE,
        LCTL(LWIN(KC_RIGHT)), _______, KC_ENT,
        LCTL(KC_C),LCTL(KC_V),LCTL(KC_X)
    ),
  [2] = LAYOUT(
        XXXXXXX, XXXXXXX,
        KC_F5, C(KC_S), C(KC_F4),
        LCTL(LALT(KC_PSCR)), C(S(KC_S)), _______,
        C(KC_PGUP), C(KC_PGDN), LGUI(KC_TAB)
    ),
  [3] = LAYOUT(
        XXXXXXX, XXXXXXX,
        PIN1, XXXXXXX, XXXXXXX,
        PIN2, XXXXXXX, XXXXXXX,
        PIN3, XXXXXXX, XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)},
    [1] =  { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)},
    [2] =  { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)},
    [3] = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD)},
};

// KEYHOOK
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == PIN1 && record->event.pressed) {
       SEND_STRING("1716");

    }
    if (keycode == PIN2 && record->event.pressed) {
       SEND_STRING("9061");

    }
    if (keycode == PIN3 && record->event.pressed) {
       SEND_STRING("1ang1ay14chang");

    }
    return true;
}

void keyboard_post_init_user(void) {
    ballconfig.raw = eeconfig_read_user();
    pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
    rgblight_layers = my_rgb_layers;
}
// CURSOR ANGLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    double rad = angle_array[ballconfig.angle_idx] * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);
    mouse_report.x = x_rev;
    mouse_report.y = y_rev;
    return mouse_report;
}

// READ EEPROM
void eeconfig_init_user(void) {
    ballconfig.cpi_idx = CPI_DEFAULT;
    ballconfig.angle_idx = ANGLE_DEFAULT;
    eeconfig_update_user(ballconfig.raw);
}
