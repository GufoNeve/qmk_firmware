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
    {0, 7, HSV_GOLD}, //ボトム(0~6)
    {7, 14, HSV_WHITE},  //本体(7~16)
    //親指(17~20)
     {21, 1, HSV_BLACK}, {22, 1, HSV_ORANGE}, {23, 8, HSV_BLACK} //ディスプレイ
 );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GOLD}, //ボトム(0~6)
    {7, 5, HSV_MAGENTA}, {12, 1, HSV_BLACK}, {13, 2, HSV_MAGENTA}, 
    {15, 2, HSV_BLACK}, //本体(7~16)
    {17, 3, HSV_MAGENTA}, {20, 1, HSV_BLACK}, //親指(17~20)
    {21, 1, HSV_ORANGE}, {22, 9, HSV_BLACK}//ディスプレイ                     
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GOLD}, //ボトム(0~6)
    {7, 10, HSV_GOLD},  //本体(7~16)
    {17, 3, HSV_BLACK}, {20, 1, HSV_GOLD}, //親指(17~20)
    {21, 7, HSV_BLACK}, {28, 1, HSV_ORANGE}, {29, 2, HSV_BLACK}//ディスプレイ                     
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GOLD}, //ボトム(0~6)
    {7, 3, HSV_GREEN}, {10, 1, HSV_BLACK}, {11, 2, HSV_GREEN}, 
    {13, 2, HSV_RED}, {15, 2, HSV_WHITE},  //本体(7~16)
    {17, 1, HSV_GREEN}, {18, 3, HSV_BLACK}, //親指(17~20)
    {21, 4, HSV_BLACK}, {25, 1, HSV_ORANGE}, {26, 5, HSV_BLACK}//ディスプレイ            
);
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GOLD}, //ボトム(0~6)
    {7, 4, HSV_RED}, {11, 6, HSV_BLACK}, {16, 1, HSV_RED}, //本体(7~16)
    {17, 4, HSV_BLACK}, //親指(17~20)
    {21, 6, HSV_BLACK}, {27, 1, HSV_ORANGE}, {28, 3, HSV_BLACK}//ディスプレイ            
 );
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_BLUE}, //ボトム(0~6)
    {7, 5, HSV_SPRINGGREEN}, {12, 3, HSV_BLUE}, {15, 1, HSV_SPRINGGREEN}, {16, 1, HSV_BLUE}, //本体(7~16)
    {17, 3, HSV_BLUE}, {20, 1, HSV_SPRINGGREEN}, //親指(17~20)
    {21, 8, HSV_BLACK}, {29, 1, HSV_ORANGE}, {30, 1, HSV_BLACK}//ディスプレイ           
 );
 const rgblight_segment_t PROGMEM layer6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_WHITE}, //ボトム(0~6)
    {7, 5, HSV_MAGENTA}, {12, 1, HSV_BLACK}, {13, 2, HSV_MAGENTA}, 
    {15, 2, HSV_BLACK},  //本体(7~16)
    {17, 4, HSV_MAGENTA}, //親指(17~20)
    {21, 9, HSV_BLACK}, {30, 1, HSV_ORANGE}//ディスプレイ
);
const rgblight_segment_t PROGMEM layer7[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_WHITE}, //ボトム(0~6)
    {7, 10, HSV_GOLD},  //本体(7~16)
    {17, 3, HSV_BLACK}, {20, 1, HSV_GOLD}, //親指(17~20)
    {21, 2, HSV_BLACK}, {23, 1, HSV_ORANGE}, {24, 7, HSV_BLACK}//ディスプレイ
);
const rgblight_segment_t PROGMEM layer8[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_WHITE}, //ボトム(0~6)
    {7, 5, HSV_GREEN}, {12, 2, HSV_WHITE}, {14, 3, HSV_BLACK}, //本体(7~16)
    {17, 1, HSV_GREEN}, {18, 3, HSV_BLACK}, //親指(17~20)
    {21, 5, HSV_BLACK}, {26, 1, HSV_ORANGE}, {27, 4, HSV_BLACK}//ディスプレイ
);
const rgblight_segment_t PROGMEM layer9[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_WHITE}, //ボトム(0~6)
    {7, 4, HSV_RED}, {11, 6, HSV_BLACK}, {16, 1, HSV_RED}, //本体(7~16)
    {17, 4, HSV_BLACK}, //親指(17~20)
    {21, 6, HSV_BLACK}, {27, 1, HSV_ORANGE}, {28, 3, HSV_BLACK}//ディスプレイ            
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
   
    [0] = LAYOUT( //マウスとしての機能
        LALT(KC_RIGHT),           MS_BTN2, KC_BSPC,   
        LALT(KC_LEFT), KC_LEFT, KC_RIGHT, LT(1, KC_UP), KC_ENT,
        LT(3, MS_BTN1), MS_BTN1, TG(5), KC_DOWN, 
        LT(2, KC_SPC), MS_BTN3
    ),
    [1] = LAYOUT( //コピペなどの頻出ショートカット
        C(KC_F),             XXXXXXX, KC_DEL,   
        KC_PSCR, C(KC_Z), C(KC_Y), MO(1), KC_ENT,
        C(KC_C), C(KC_V), XXXXXXX, XXXXXXX, 
        MO(4), C(KC_X)
    ),
    [2] = LAYOUT( //画面操作系ショートカット
        KC_F5,             C(KC_S), C(KC_W),   
        LWIN(KC_TAB), C(KC_T), C(KC_PGUP), C(KC_PGDN), LCS(KC_S),
        XXXXXXX, XXXXXXX, C(KC_A), KC_TAB, 
        MO(2), XXXXXXX
    ),
    [3] = LAYOUT( //電源&WIN系ショートカット
        A(KC_GRV),             LCS(KC_ESC), LWIN(KC_L),   
        KC_ESC, LCS(KC_N), XXXXXXX, LWIN(KC_E), KC_LWIN,
        MO(3), XXXXXXX, LCG(KC_V), LWIN(KC_I), 
        XXXXXXX, XXXXXXX
    ),
    [4] = LAYOUT( //PIN
        PIN1,             XXXXXXX, XXXXXXX,   
        PIN2, PIN3, PIN4, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, PIN5, XXXXXXX, 
        MO(4), XXXXXXX
    ),
    [5] = LAYOUT( //イラレ用1
        KC_V,             MS_BTN2, KC_BSPC,   
        LALT(KC_LEFT), C(KC_Z), LCS(KC_Z), LT(6, KC_M), KC_ENT,
        LT(8, MS_BTN1), MS_BTN1, TG(5), KC_TAB, 
        LT(7, KC_SPC), MS_BTN3
    ),
    [6] = LAYOUT( //イラレ用2
        KC_A,             KC_C, KC_DEL,   
        KC_C, C(KC_2), KC_L, MO(6), KC_ENT,
        C(KC_C), C(KC_V), XXXXXXX, XXXXXXX, 
        LT(9, KC_SPC), C(KC_X)
    ),
    [7] = LAYOUT( //イラレ用3
        KC_R,             C(KC_S), C(KC_W),   
        LWIN(KC_TAB), LCA(KC_L), C(KC_PGUP), C(KC_PGDN), LCS(KC_S),
        XXXXXXX, XXXXXXX, C(KC_A), KC_TAB, 
        MO(7), XXXXXXX
    ),
    [8] = LAYOUT( //イラレ用4
        A(KC_GRV),             A(KC_F), A(KC_O),   
        KC_ESC, C(KC_N), S(KC_O), LCA(KC_L), KC_ENT,
        MO(8), XXXXXXX, LCA(KC_7), LCA(KC_8), 
        XXXXXXX, XXXXXXX
    ),
    [9] = LAYOUT( //イラレ用5
        KC_G,             XXXXXXX, XXXXXXX,   
        LCS(KC_G), C(KC_1), C(KC_2), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        MO(6), XXXXXXX
    )
};

