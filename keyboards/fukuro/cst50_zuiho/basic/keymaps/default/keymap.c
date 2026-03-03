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
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 1, HSV_BLACK}, {67, 1, HSV_ORANGE}, {68, 8, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
 );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 1, HSV_ORANGE}, {67, 9, HSV_BLACK} //レイヤーディスプレイ(66~76) 
                        
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 7, HSV_BLACK}, {73, 1, HSV_ORANGE}, {74, 2, HSV_BLACK} //レイヤーディスプレイ(66~76)       
                  
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 4, HSV_BLACK}, {70, 1, HSV_ORANGE}, {71, 5, HSV_BLACK}//レイヤーディスプレイ(66~76)
                
);
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 6, HSV_BLACK}, {72, 1, HSV_ORANGE}, {73, 3, HSV_BLACK} //レイヤーディスプレイ(66~76)
                
 );
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 8, HSV_BLACK}, {74, 1, HSV_ORANGE}, {75, 1, HSV_BLACK} //レイヤーディスプレイ(66~76) 
              
 );
 const rgblight_segment_t PROGMEM layer6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 9, HSV_BLACK}, {75, 1, HSV_ORANGE} //レイヤーディスプレイ(66~76)
    
);
const rgblight_segment_t PROGMEM layer7[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 2, HSV_BLACK}, {68, 1, HSV_ORANGE}, {69, 7, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
);
const rgblight_segment_t PROGMEM layer8[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 5, HSV_BLACK}, {71, 1, HSV_ORANGE}, {72, 4, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
);
const rgblight_segment_t PROGMEM layer9[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED}, {8, 25, HSV_BLUE},  //本体左側
    {33, 8, HSV_RED}, {41, 25, HSV_BLUE},//本体右側
    {66, 3, HSV_BLACK}, {69, 1, HSV_ORANGE}, {70, 6, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
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


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  {   ENCODER_CCW_CW(MS_WHLD, MS_WHLU) }, // 下　上 の順 
    [1] =  {   ENCODER_CCW_CW(_______, _______) },
    [2] =  {   ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [3] =  {   ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [4] =  {   ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [5] =  {   ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [6] =  {   ENCODER_CCW_CW(_______, _______) },
    [7] =  {   ENCODER_CCW_CW(_______, _______) },
    [8] =  {   ENCODER_CCW_CW(_______, _______) },
    [9] =  {   ENCODER_CCW_CW(KC_BSPC, KC_TAB)  }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [0] = LAYOUT( //ベースレイヤー
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [1] = LAYOUT( //ショートカット置き場
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [2] = LAYOUT( //裏ショートカット置き場
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [3] = LAYOUT( //
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [4] = LAYOUT( //
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [5] = LAYOUT( //
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [6] = LAYOUT( //
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [7] = LAYOUT( //
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [8] = LAYOUT( //記号キー置き場
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    ),
    [9] = LAYOUT( //テンキー&ファンクション
        A(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T,         KC_Y, KC_U, KC_I, KC_O, KC_MINS, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(3, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_GRV, KC_SLSH, LT(2, KC_BSLS), 
                                TG(1), LT(9,KC_INT5),   MO(9), TG(1),
                        LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC), LT(8, KC_SPC)
    )
};

