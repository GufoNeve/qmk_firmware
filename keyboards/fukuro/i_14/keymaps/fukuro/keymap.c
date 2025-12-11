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
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE},  //本体
     {21, 1, HSV_BLACK}, {22, 1, HSV_ORANGE}, {23, 8, HSV_BLACK} //ディスプレイ
 );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_MAGENTA},  //本体
    {21, 1, HSV_ORANGE}, {22, 9, HSV_BLACK}//ディスプレイ                     
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_GOLD},   //本体
    {21, 7, HSV_BLACK}, {28, 1, HSV_ORANGE}, {29, 2, HSV_BLACK}//ディスプレイ                     
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_CYAN},  //本体
    {21, 4, HSV_BLACK}, {25, 1, HSV_ORANGE}, {26, 5, HSV_BLACK}//ディスプレイ            
);
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE}, //本体
    {21, 6, HSV_BLACK}, {27, 1, HSV_ORANGE}, {28, 3, HSV_BLACK}//ディスプレイ            
 );
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE},  //本体
    {21, 8, HSV_BLACK}, {29, 1, HSV_ORANGE}, {30, 1, HSV_BLACK}//ディスプレイ           
 );
 const rgblight_segment_t PROGMEM layer6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE},  //本体
    {21, 9, HSV_BLACK}, {30, 1, HSV_ORANGE}//ディスプレイ
);
const rgblight_segment_t PROGMEM layer7[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE},  //本体
     {21, 2, HSV_BLACK}, {23, 1, HSV_ORANGE}, {24, 7, HSV_BLACK}//ディスプレイ
);
const rgblight_segment_t PROGMEM layer8[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE},  //本体
     {21, 5, HSV_BLACK}, {26, 1, HSV_ORANGE}, {27, 4, HSV_BLACK}//ディスプレイ
);
const rgblight_segment_t PROGMEM layer9[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 7, HSV_ORANGE}, {7, 14, HSV_BLUE},  //本体
     {21, 3, HSV_BLACK}, {24, 1, HSV_ORANGE}, {25, 6, HSV_BLACK}//ディスプレイ
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0,
    layer1,
    layer2,
    layer3,
    layer4,
    layer5,
    layer6,
    layer7,
    layer8,
    layer9
);

// 初期化時にRGBレイヤーを設定
void keyboard_post_init_user(void) {
    rgblight_enable();  // RGBライトを有効化
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);  // モードを固定
    rgblight_layers = my_rgb_layers;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));
    rgblight_set_layer_state(8, layer_state_cmp(state, 8));
    rgblight_set_layer_state(9, layer_state_cmp(state, 9));
    return state;
}


void matrix_init_user(void) {
    dprintf("Matrix initialized\n");
}

// カスタムキーコード
enum custom_keycodes{
    PIN = SAFE_RANGE,
    PIN1, PIN2, PIN3, PIN4, PIN5
};

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
    if (keycode == PIN4 && record->event.pressed) {
       SEND_STRING("ka0rieila");
    }
    if (keycode == PIN5 && record->event.pressed) {
       SEND_STRING("Zu1h0");
    }
    return true;
}


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  {
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)  // たて
    },
    [1] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [2] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [3] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [4] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [5] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [6] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [7] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [8] =  {
        ENCODER_CCW_CW(_______, _______)
    },
    [9] =  {
        ENCODER_CCW_CW(_______, _______)
    }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [0] = LAYOUT(
        LALT(KC_LEFT),           MS_BTN2, KC_BACKSPACE,   
        LALT(KC_RIGHT), KC_F5, KC_PSCR, MO(1), KC_ENT,
        MS_BTN3, MS_BTN1, TG(5), LWIN(KC_TAB), 
        MO(2), KC_SPC
    ),
    [1] = LAYOUT(
        C(KC_PGUP),             KC_B, KC_DEL,   
        C(KC_PGDN), A(KC_W), A(KC_N), MO(1), KC_ENT,
        C(KC_V), C(KC_C), KC_K, KC_L, 
        MO(4), C(KC_X)
    ),
    [2] = LAYOUT(  
        LCS(KC_N),             C(KC_S), C(KC_W),   
        KC_D, KC_E, KC_F, LCS(KC_S), KC_H,
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
        PIN1,             XXXXXXX, XXXXXXX,   
        PIN2, PIN3, PIN4, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, PIN5, XXXXXXX, 
        MO(4), XXXXXXX
    ),
    [5] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, TG(5), KC_L, 
        KC_O, KC_P
    ),
    [6] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [7] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [8] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    ),
    [9] = LAYOUT(
        KC_A,             KC_B, KC_C,   
        KC_D, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L, 
        KC_O, KC_P
    )
};

