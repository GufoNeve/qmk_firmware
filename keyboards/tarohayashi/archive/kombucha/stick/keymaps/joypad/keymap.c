// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "analog.h"
#include "joystick.h"


// 軸ブレのを無視する値
#define OFFSET 80
typedef union {
    uint32_t raw;
    struct {
        uint8_t angle;
    };
} stickconfig_t;

// KEYCODES
enum stick_keycodes{
    BALL_SAFE_RANGE = SAFE_RANGE,
    ANG_I,
};

// LAYERS
enum layer_number {
    BASE = 0,
    LOWER,
    UPPER,
    LIGHT,
};

// LAYOUT SETTINGS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
        JS_0, JS_1,
        JS_2, JS_3, JS_4,
        JS_5, JS_6, JS_7,
        JS_8, MO(UPPER), MO(LIGHT),

            XXXXXXX,
        XXXXXXX, XXXXXXX,
            XXXXXXX
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
        XXXXXXX,XXXXXXX, XXXXXXX,
        XXXXXXX,ANG_I, XXXXXXX,
        XXXXXXX, MO(UPPER), XXXXXXX,

            XXXXXXX,
        XXXXXXX, XXXXXXX,
            XXXXXXX
    ),
  [LIGHT] = LAYOUT(
        RGB_TOG, ANG_I,
        RGB_SAI, RGB_VAI, RGB_SPI,
        RGB_SAD, RGB_VAD, RGB_SPD,
        RGB_MOD, RGB_RMOD, MO(LIGHT),

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

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

int16_t gp27_newt;
int16_t gp28_newt;
stickconfig_t stickconfig;

void keyboard_post_init_user(void) {
    stickconfig.raw = eeconfig_read_user();
}

void matrix_init_user(void) {
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
}

void eeconfig_init_user(void) {
    stickconfig.angle = 0;
    eeconfig_update_kb(stickconfig.raw);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == ANG_I && record->event.pressed) {
        stickconfig.angle = (stickconfig.angle + 1) % 8;
        eeconfig_update_user(stickconfig.raw);
    }
    return true;
}


void joystick_task(){
    int16_t gp27_val = analogReadPin(GP27);
    int16_t gp28_val = analogReadPin(GP28);
    float x_val = ( (float)gp27_val - (float)gp27_newt  ) * (float)511 / ((float)1023 - (float)gp27_newt);
    float y_val = ( (float)gp28_val - (float)gp28_newt ) * (float)511 / ((float)1023 - (float)gp28_newt);
    if(x_val < -511){
        x_val = -511;
    }
    if(y_val < -511){
        y_val = -511;
    }

    //軸ブレ補正
    if (x_val > (float)-1 * (float)OFFSET && x_val < (float)OFFSET){
        x_val = (float)0;
    }
    if (y_val > (float)-1 * (float)OFFSET && y_val < (float)OFFSET){
        y_val = (float)0;
    }

    if(stickconfig.angle == 0){
        joystick_set_axis(0, (int16_t)x_val);
        joystick_set_axis(1, (int16_t)y_val);
    }else if(stickconfig.angle == 1){
        joystick_set_axis(0, -1 * (int16_t)x_val);
        joystick_set_axis(1, (int16_t)y_val);
    }else if(stickconfig.angle == 2){
        joystick_set_axis(0, -1 * (int16_t)x_val);
        joystick_set_axis(1, -1 * (int16_t)y_val);
    }else if(stickconfig.angle == 3){
        joystick_set_axis(0, (int16_t)x_val);
        joystick_set_axis(1, -1 * (int16_t)y_val);
    }else if(stickconfig.angle == 4){
        joystick_set_axis(0, (int16_t)y_val);
        joystick_set_axis(1, (int16_t)x_val);
    }else if(stickconfig.angle == 5){
        joystick_set_axis(0, -1 * (int16_t)y_val);
        joystick_set_axis(1, (int16_t)x_val);
    }else if(stickconfig.angle == 6){
        joystick_set_axis(0, -1 * (int16_t)y_val);
        joystick_set_axis(1, -1 * (int16_t)x_val);
    }else if(stickconfig.angle == 7){
        joystick_set_axis(0, (int16_t)y_val);
        joystick_set_axis(1, -1 * (int16_t)x_val);
    }
    joystick_flush();
}
