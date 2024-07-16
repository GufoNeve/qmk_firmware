// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "analog.h"

// LAYERS
enum layer_number {
    BASE = 0,
    LOWER,
    UPPER,
    LIGHT,
};

#define OFFSET 200

// LAYOUT SETTINGS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
        KC_A, KC_B,
        KC_C, KC_D, KC_E,
        KC_F, KC_G, KC_H,
        KC_I, KC_J, LT(LIGHT, KC_K),

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
        XXXXXXX,XXXXXXX, XXXXXXX,
        XXXXXXX,XXXXXXX, XXXXXXX,
        XXXXXXX, MO(UPPER), XXXXXXX,

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

int16_t gp27_newt;
int16_t gp28_newt;
keypos_t key_up;
keypos_t key_left;
keypos_t key_right;
keypos_t key_down;
bool pressed_up = false;
bool pressed_down = false;
bool pressed_left = false;
bool pressed_right = false;


void matrix_init_user(void) {
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
    key_up.row = 3;
    key_up.col = 0;
    key_left.row = 3;
    key_left.col = 1;
    key_right.row = 3;
    key_right.col = 2;
    key_down.row = 3;
    key_down.col = 3;
}

void matrix_scan_user(void) {
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

    int8_t layer = layer_switch_get_layer(key_up);
    int16_t keycode_up = keymap_key_to_keycode(layer, key_up);
    int16_t keycode_left = keymap_key_to_keycode(layer, key_left);
    int16_t keycode_right = keymap_key_to_keycode(layer, key_right);
    int16_t keycode_down = keymap_key_to_keycode(layer, key_down);

    if(pressed_left == false && x_val > (float)OFFSET){
        register_code(keycode_left);
        pressed_left = true;
        wait_ms(100);
    }else if(pressed_left == true && x_val <(float)OFFSET){
        unregister_code(keycode_left);
        pressed_left = false;
        wait_ms(100);
    }else if(pressed_right == false && x_val < (float)-1 * (float)OFFSET){
        register_code(keycode_right);
        pressed_right = true;
        wait_ms(100);
    }else if (pressed_right == true && x_val > (float)-1 * (float)OFFSET){
        unregister_code(keycode_right);
        pressed_right = false;
        wait_ms(100);
    }

    if(pressed_up == false && y_val > (float)OFFSET){
        register_code(keycode_up);
        pressed_up = true;
        wait_ms(100);
    }else if(pressed_up == true && y_val < (float)OFFSET){
        unregister_code(keycode_up);
        pressed_up = false;
        wait_ms(100);
    }else if(pressed_down == false && y_val < (float)-1 * (float)OFFSET){
        register_code(keycode_down);
        pressed_down = true;
        wait_ms(100);
    }else if(pressed_down == true && y_val > (float)-1 * (float)OFFSET){
        unregister_code(keycode_down);
        pressed_down = false;
        wait_ms(100);
    }
}


