// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <math.h>

void pointing_device_init_kb(void) {
#ifdef PMW3360_CPI
    pointing_device_set_cpi(PMW3360_CPI);
#endif
}

const rgblight_segment_t PROGMEM layer0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE} 
 );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {87, 14, HSV_YELLOW}                       
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_GREEN}                         
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_CYAN}              
);
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE}             
 );
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE}             
 );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0,
    layer1,
    layer2,
    layer3,
    layer4,
    layer5
);

// 初期化時にRGBレイヤーを設定
void keyboard_post_init_user(void) {
    rgblight_enable();  // RGBライトを有効化
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);  // モードを固定
    rgblight_layers = my_rgb_layers;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 1, 2, 3);
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}

void matrix_init_user(void) {
    dprintf("Matrix initialized\n");
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  {
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),  // たて
        ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)   // よこ 
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
    [4] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [5] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [0] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        MO(1), KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [1] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [2] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [3] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [4] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [5] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    )
};


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Hello, OLED!"), false);
    return false;
}
#endif
