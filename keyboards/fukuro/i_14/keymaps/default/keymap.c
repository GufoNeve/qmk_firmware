// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"
// ショートカット用キーコード
enum custom_keycodes{
    PIN_NYURYOKU = SAFE_RANGE,
    PIN1, PIN2, PIN3,
};

// トラックボール設定用のキーコード
enum ball_keycodes{
    BALL_SAFE_RANGE = SAFE_RANGE,
    CPI_I, CPI_D, L_ANG_I, L_ANG_D, L_INV, R_ANG_I, R_ANG_D, R_INV,
    L_CHMOD, R_CHMOD, INV_SCRL, MOD_SCRL
};

// トラックボールの定数、変数
#define CPI_OPTIONS {950}
#define CPI_DEFAULT 0
#define ANGLE_OPTIONS {215}
#define ANGLE_DEFAULT 0
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define ANGLE_OPTION_SIZE (sizeof(angle_array) / sizeof(uint16_t))

typedef union{
    uint32_t raw;
    struct{
        uint8_t cpi_idx         :4;
        uint8_t angle_idx       :5;
        bool inv                :1;
        bool scmode             :1;
        bool inv_sc             :1;
        bool auto_mouse         :1;
    };
} ballconfig_t;

ballconfig_t ballconfig;
uint16_t cpi_array[] = CPI_OPTIONS;
uint16_t angle_array[] = ANGLE_OPTIONS;
bool scrolling;
float scroll_accumulated_h;
float scroll_accumulated_v;
uint8_t pre_layer;
uint8_t cur_layer;
bool oled_mode;

void eeconfig_init_user(void) {
    ballconfig.cpi_idx = CPI_DEFAULT;
    ballconfig.angle_idx = ANGLE_DEFAULT;
    ballconfig.inv = false;
    ballconfig.scmode = false;
    ballconfig.inv_sc = false;
    ballconfig.auto_mouse = false;
    eeconfig_update_user(ballconfig.raw);
}
// カーソル調整
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    double rad = angle_array[ballconfig.angle_idx] * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    if(ballconfig.inv){
            x_rev = -1 * x_rev;
    }
    if(scrolling || ballconfig.scmode){
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        mouse_report.h = x_rev;
        mouse_report.v = y_rev;
        if(!ballconfig.inv_sc ){

            mouse_report.h = -1 * mouse_report.h;
            mouse_report.v = -1 * mouse_report.v;
        }

        scroll_accumulated_h += (float)mouse_report.h / SCROLL_DIVISOR;
        scroll_accumulated_v += (float)mouse_report.v / SCROLL_DIVISOR;
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        mouse_report.x = 0;
        mouse_report.y = 0;
    }else{
        mouse_report.x = -1 * x_rev;
        mouse_report.y = y_rev;
    }
    return mouse_report;
    }
// READ EEPROM
void eeconfig_init_user(void) {
    ballconfig.cpi_idx = CPI_DEFAULT;
    ballconfig.angle_idx = ANGLE_DEFAULT;
    eeconfig_update_user(ballconfig.raw);
}

// KEYHOOK
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == CPI_I && record->event.pressed) {
        ballconfig.cpi_idx = ballconfig.cpi_idx + 1;
        if(ballconfig.cpi_idx >= CPI_OPTION_SIZE){
            ballconfig.cpi_idx = CPI_OPTION_SIZE-1;
        }
        eeconfig_update_user(ballconfig.raw);
        pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
    }
    if (keycode == CPI_D && record->event.pressed) {
        if(ballconfig.cpi_idx > 0){
            ballconfig.cpi_idx = ballconfig.cpi_idx - 1;
        }
        eeconfig_update_user(ballconfig.raw);
        pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
    }
    if (keycode == L_ANG_I && record->event.pressed) {
        ballconfig.angle_idx = (ballconfig.angle_idx + 1) % ANGLE_OPTION_SIZE;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == L_ANG_D && record->event.pressed) {
        ballconfig.angle_idx = (ANGLE_OPTION_SIZE + ballconfig.angle_idx - 1) % ANGLE_OPTION_SIZE;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == R_ANG_I && record->event.pressed) {
        ballconfig.angle_idx = (ballconfig.angle_idx + 1) % ANGLE_OPTION_SIZE;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == R_ANG_D && record->event.pressed) {
        ballconfig.angle_idx = (ANGLE_OPTION_SIZE + ballconfig.angle_idx - 1) % ANGLE_OPTION_SIZE;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == R_INV && record->event.pressed) {
       ballconfig.inv = !ballconfig.inv;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == L_INV && record->event.pressed) {
       ballconfig.inv = !ballconfig.inv;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == L_CHMOD && record->event.pressed) {
       ballconfig.scmode = !ballconfig.scmode;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == R_CHMOD && record->event.pressed) {
       ballconfig.scmode = !ballconfig.scmode;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == INV_SCRL && record->event.pressed) {
       ballconfig.inv_sc = !ballconfig.inv_sc;
        eeconfig_update_user(ballconfig.raw);
    }
    if (keycode == MOD_SCRL) {
        scrolling = record->event.pressed;
    }
    if (keycode == PIN1 && record->event.pressed) {
       SEND_STRING("miserarenaiyo");

    }
    if (keycode == PIN2 && record->event.pressed) {
       SEND_STRING("miserarenaiyo");

    }
    if (keycode == PIN3 && record->event.pressed) {
       SEND_STRING("miserarenaiyo");

    }
    return true;
}

void keyboard_post_init_user(void) {
    ballconfig.raw = eeconfig_read_user();
    pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
    rgblight_layers = my_rgb_layers;
}

const rgblight_segment_t PROGMEM layer0[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 3, HSV_ORANGE}, { 4, 13, HSV_BLUE}, {18, 1, HSV_ORANGE}                                 );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
   { 0, 3, HSV_ORANGE}, { 4, 13, HSV_BLUE}, {18, 1, HSV_ORANGE}                       );
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 3, HSV_ORANGE}, { 4, 13, HSV_BLUE}, {18, 1, HSV_ORANGE}                         );
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 3, HSV_ORANGE}, { 4, 13, HSV_BLUE}, {18, 1, HSV_ORANGE}              );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0,
    layer1,
    layer2,
    layer3
);

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 1, 2, 3);
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [0] = LAYOUT(
        KC_A,           KC_B, KC_C,   
        KC_D,   
        KC_E,           KC_F, KC_G,
                  KC_H, KC_I, KC_J, 
                              KC_K, 
        KC_L,
        KC_O, KC_P
    )
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  {
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),  // 水平
        ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)   // ロープロ
    },
    [1] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [2] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [3] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },


static const char PROGMEM number[][512] = {
    // 0
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xcf, 0xcf, 0x8f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfe, 0xfc, 0xf8, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
        0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8,
        0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff,
        0xff, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
        0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf1, 0xf3,
        0xf3, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f
    },