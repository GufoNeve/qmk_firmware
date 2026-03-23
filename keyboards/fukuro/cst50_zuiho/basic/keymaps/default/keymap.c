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
    {0, 7, HSV_GREEN}, {7, 1, HSV_WHITE}, //本体左アンダー(0~7)
    {8, 25, HSV_WHITE},  //本体左側(8~28)
    //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_WHITE}, //本体右アンダー(33~40)
    {41, 25, HSV_WHITE},//本体右側(41~61)
    //本体右親指(62~65)
    {66, 1, HSV_BLACK}, {67, 1, HSV_ORANGE}, {68, 8, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
 );
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_GOLD}, //本体左アンダー(0~7)
    {8, 1, HSV_BLACK}, {9, 4, HSV_GOLD}, {13, 1, HSV_WHITE}, {14, 1, HSV_GREEN}, {15, 10, HSV_GOLD},
    {25, 2, HSV_WHITE}, {27, 1, HSV_BLACK}, {28, 1, HSV_WHITE}, //本体左側(8~28)
    {29, 1, HSV_CYAN}, {30, 1, HSV_GOLD}, {31, 1, HSV_MAGENTA}, {32, 1, HSV_CYAN}, //本体左親指(29~32) 
    {33, 7, HSV_GREEN}, {40, 1, HSV_GOLD}, //本体右アンダー(33~40)
    {41, 5, HSV_BLACK}, {46, 2, HSV_GREEN}, {48, 1, HSV_BLACK}, {49, 1, HSV_GOLD}, {50, 5, HSV_BLACK},
    {55, 3, HSV_GOLD}, {58, 2, HSV_WHITE}, {60, 1, HSV_BLACK}, {61, 1, HSV_WHITE}, //本体右側(41~61)
    {62, 2, HSV_GOLD}, {64, 1, HSV_MAGENTA}, {65, 1, HSV_BLACK}, //本体右親指(62~65)
    {66, 1, HSV_ORANGE}, {67, 9, HSV_BLACK} //レイヤーディスプレイ(66~76) 
                        
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_BLUE}, //本体左アンダー(0~7)
    {8, 5, HSV_BLACK}, {13, 1, HSV_WHITE}, {14, 1, HSV_GREEN}, {15, 3, HSV_CYAN}, {18, 1, HSV_BLACK}, {19, 6, HSV_CYAN}, {25, 2, HSV_WHITE},
    {27, 1, HSV_BLACK}, {28, 1, HSV_WHITE}, //本体左側(8~28)
    {29, 3, HSV_BLACK}, {32, 1, HSV_CYAN}, //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_BLUE}, //本体右アンダー(33~40)
    {41, 5, HSV_BLACK}, {46, 2, HSV_GOLD}, {48, 1, HSV_BLACK}, {49, 1, HSV_GOLD}, {50, 5, HSV_BLACK},
    {55, 3, HSV_GOLD}, {58, 2, HSV_WHITE}, {60, 1, HSV_BLACK}, {61, 1, HSV_WHITE}, //本体右側(41~61)
    {62, 4, HSV_BLACK}, //本体右親指(62~65)
    {66, 7, HSV_BLACK}, {73, 1, HSV_ORANGE}, {74, 2, HSV_BLACK} //レイヤーディスプレイ(66~76)       
                  
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_WHITE}, //本体左アンダー(0~7)
    {8, 25, HSV_BLACK},  //本体左側(8~28)
    //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_WHITE}, //本体右アンダー(33~40)
    {41, 8, HSV_BLACK}, {49, 3, HSV_WHITE}, {52, 2, HSV_BLACK}, {54, 3, HSV_WHITE}, {57, 1, HSV_BLACK}, {58, 1, HSV_WHITE},
    {59, 1, HSV_BLACK}, {60, 1, HSV_WHITE}, {61, 1, HSV_BLACK},//本体右側(41~61)
    {62, 4, HSV_BLACK}, //本体右親指(62~65)
    {66, 4, HSV_BLACK}, {70, 1, HSV_ORANGE}, {71, 5, HSV_BLACK}//レイヤーディスプレイ(66~76)
                
);
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_RED}, //本体左アンダー(0~7)
    {8, 25, HSV_BLACK},  //本体左側(8~28)
    {33, 7, HSV_GREEN}, {40, 1, HSV_WHITE}, //本体右アンダー(33~40)
    {41, 8, HSV_BLACK}, {49, 3, HSV_RED}, {52, 2, HSV_BLACK}, {54, 3, HSV_RED}, {57, 1, HSV_BLACK}, {58, 1, HSV_WHITE},
    {59, 1, HSV_BLACK}, {60, 1, HSV_RED}, {61, 1, HSV_BLACK}, //本体右側(41~61)
    {62, 1, HSV_RED}, {63, 3, HSV_BLACK}, //本体右親指(62~65)
    {66, 6, HSV_BLACK}, {72, 1, HSV_ORANGE}, {73, 3, HSV_BLACK} //レイヤーディスプレイ(66~76)
                
 );
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_RED}, //本体左アンダー(0~7)
    {8, 5, HSV_BLACK}, {13, 2, HSV_GREEN}, {15, 10, HSV_BLACK}, {25, 1, HSV_RED}, {26, 3, HSV_WHITE},//本体左側(8~28)   
    {29, 4, HSV_BLACK}, //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_RED}, //本体右アンダー(33~40)
    {41, 4, HSV_BLACK}, {45, 1, HSV_MAGENTA}, {46, 2, HSV_BLACK}, {48, 1, HSV_MAGENTA}, {49, 4, HSV_BLACK}, {53, 2, HSV_GREEN}, {55, 3, HSV_BLACK}, 
    {58, 1, HSV_RED}, {59, 1, HSV_WHITE}, {60, 1, HSV_BLACK}, {61, 1, HSV_WHITE}, //本体右側(41~61)
    {62, 1, HSV_GOLD}, {63, 3, HSV_BLACK}, //本体右親指(62~65)
    {66, 8, HSV_BLACK}, {74, 1, HSV_ORANGE}, {75, 1, HSV_BLACK} //レイヤーディスプレイ(66~76) 
              
 );
 const rgblight_segment_t PROGMEM layer6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_MAGENTA}, //本体左アンダー(0~7)
    {8, 3, HSV_BLACK}, {11, 2, HSV_GOLD}, {13, 1, HSV_WHITE}, {14, 1, HSV_GREEN}, {15, 3, HSV_GOLD}, 
    {18, 7, HSV_BLACK}, {25, 4, HSV_WHITE}, //本体左側(8~28)
    {29, 4, HSV_BLACK}, //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_MAGENTA},  //本体右アンダー(33~40)
    {41, 5, HSV_MAGENTA}, {46, 2, HSV_GREEN}, {48, 10, HSV_MAGENTA}, {58, 2, HSV_WHITE}, {60, 1, HSV_BLACK}, {61, 1, HSV_WHITE},//本体右側(41~61)
    {62, 2, HSV_BLACK}, {64, 1, HSV_MAGENTA}, {65, 1, HSV_BLACK}, //本体右親指(62~65)
    {66, 9, HSV_BLACK}, {75, 1, HSV_ORANGE} //レイヤーディスプレイ(66~76)
    
);
const rgblight_segment_t PROGMEM layer7[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_BLUE}, //本体左アンダー(0~7)
    {8, 1, HSV_MAGENTA}, {9, 2, HSV_BLACK},{11, 2, HSV_GOLD}, {13, 1, HSV_WHITE}, {14, 1, HSV_GREEN}, {15, 3, HSV_GOLD}, {18, 1, HSV_BLACK},
    {19, 2, HSV_MAGENTA}, {21, 4, HSV_BLACK}, {25, 4, HSV_WHITE}, //本体左側(8~28)
    {29, 1, HSV_CYAN}, {30, 3, HSV_BLACK}, //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_BLUE}, //本体右アンダー(33~40)
    {41, 4, HSV_CYAN}, {45, 1, HSV_BLACK}, {46, 2, HSV_GOLD}, {48, 1, HSV_BLACK}, {49, 8, HSV_CYAN},
    {57, 1, HSV_BLACK}, {58, 1, HSV_CYAN}, {59, 1, HSV_WHITE}, {60, 1, HSV_BLACK}, {61, 1, HSV_WHITE}, //本体右側(41~61)
    {62, 4, HSV_BLACK}, //本体右親指(62~65)
    {66, 2, HSV_BLACK}, {68, 1, HSV_ORANGE}, {69, 7, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
);
const rgblight_segment_t PROGMEM layer8[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_GREEN}, //本体左アンダー(0~7)
    {8, 6, HSV_GREEN}, {14, 1, HSV_WHITE}, {15, 2, HSV_BLACK}, {17, 6, HSV_GREEN}, {23, 2, HSV_BLACK}, {25, 4, HSV_WHITE},//本体左側(8~28)
    {29, 2, HSV_BLACK}, {31, 1, HSV_GREEN}, {32, 1, HSV_BLACK}, //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_GREEN}, //本体右アンダー(33~40)
    {41, 7, HSV_GREEN}, {48, 1, HSV_BLACK}, {49, 1, HSV_GOLD}, {50, 3, HSV_GREEN}, {53, 2, HSV_BLACK},
    {55, 3, HSV_GOLD}, {58, 1, HSV_GREEN}, {59, 3, HSV_WHITE}, //本体右側(41~61)
    {62, 3, HSV_BLACK}, {65, 1, HSV_GREEN}, //本体右親指(62~65)
    {66, 5, HSV_BLACK}, {71, 1, HSV_ORANGE}, {72, 4, HSV_BLACK} //レイヤーディスプレイ(66~76)
    
);
const rgblight_segment_t PROGMEM layer9[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}, {7, 1, HSV_MAGENTA}, //本体左アンダー(0~7)
    {8, 5, HSV_MAGENTA}, {13, 1, HSV_WHITE}, {14, 1, HSV_GREEN}, {15, 10, HSV_MAGENTA}, {25, 4, HSV_WHITE}, //本体左側(8~28)
    {29, 3, HSV_BLACK}, {32, 1, HSV_MAGENTA}, //本体左親指(29~32)
    {33, 7, HSV_GREEN}, {40, 1, HSV_MAGENTA}, //本体右アンダー(33~40)
    {41, 5, HSV_BLACK}, {46, 2, HSV_GREEN}, {48, 1, HSV_BLACK}, {49, 1, HSV_GOLD}, {50, 5, HSV_BLACK},
    {55, 3, HSV_GOLD}, {58, 2, HSV_WHITE}, {60, 1, HSV_BLACK}, {61, 1, HSV_WHITE}, //本体右側(41~61)
    {62, 4, HSV_BLACK}, //本体右親指(62~65)
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
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_P, KC_ENT,            
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LT(7, KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_RCTL, LT(3, KC_SLSH), KC_RSFT, 
                            LT(7,KC_INT5), TG(1),    TG(1), MO(5),
                        LT(9, KC_SPC), LT(8, KC_SPC), LT(6, KC_SPC), LT(8, KC_SPC)
    ),
    [1] = LAYOUT( //イラレショートカット
        A(KC_GRV), KC_ESC, LCA(KC_7), LCA(KC_8), LCA(KC_L), KC_T,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        KC_TAB, KC_A, KC_S, S(KC_O), LCS(KC_F), KC_G,                    XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, KC_BSPC,            
        KC_LSFT, KC_Z, C(KC_1), KC_BSLS, KC_V, KC_M,                           XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, LT(7, KC_ENT), 
        KC_LCTL, XXXXXXX, KC_LALT,                                                                        KC_RCTL, XXXXXXX, KC_RSFT, 
                                                XXXXXXX, TG(1),    TG(1), MO(5),
                                        LT(9, KC_SPC), LT(2, KC_SPC),    LT(6, KC_SPC), XXXXXXX
    ),
    [2] = LAYOUT( //イラレ裏ショートカット
        A(KC_GRV), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        KC_TAB, C(KC_A), LCS(KC_S), LCS(KC_O), XXXXXXX, LCS(KC_G),   XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, KC_BSPC,            
        KC_LSFT, LCS(KC_Z), C(KC_2), KC_C, KC_R, KC_L,                   XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT, 
        KC_LCTL, XXXXXXX, KC_LALT,                                                              KC_RCTL, XXXXXXX, KC_RSFT, 
                                          XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                          XXXXXXX, MO(2),      XXXXXXX, XXXXXXX
    ),                                       
    [3] = LAYOUT( //
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX, XXXXXXX,            
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX, KC_ENT, 
        XXXXXXX, XXXXXXX, XXXXXXX,                                                              XXXXXXX, MO(3), XXXXXXX, 
                                               XXXXXXX, XXXXXXX,   XXXXXXX, MO(4),
                                               XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX
    ),
    [4] = LAYOUT( //
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX, XXXXXXX,            
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX, KC_ENT, 
        XXXXXXX, XXXXXXX, XXXXXXX,                                                              XXXXXXX, MO(3), XXXXXXX, 
                                               XXXXXXX, XXXXXXX,   XXXXXXX, MO(4),
                                               XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX
    ),
    [5] = LAYOUT( //左Caps Lock　右Winコマンド
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN, XXXXXXX,
        KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_UP, XXXXXXX,            
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        LCS(KC_ESC), LGUI(KC_L), XXXXXXX, XXXXXXX, XXXXXXX, LCA(KC_DEL), 
        KC_LCTL, KC_LGUI, KC_LALT,                                                               KC_RCTL, XXXXXXX, KC_RSFT, 
                                               XXXXXXX, XXXXXXX,   XXXXXXX, MO(5),
                                               XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX
    ),
    [6] = LAYOUT( //右テンキー　左アロー
        A(KC_GRV), KC_ESC, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,      S(KC_QUOT), KC_7, KC_8, KC_9, KC_MINS, KC_DEL,
        KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,    KC_INT1, KC_4, KC_5, KC_6, S(KC_SCLN), KC_BSPC,            
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_0, KC_1, KC_2, KC_3, KC_DOT, KC_ENT, 
        KC_LCTL, KC_LGUI, KC_LALT,                                              KC_RCTL, XXXXXXX, KC_RSFT, 
                                         XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                         XXXXXXX, XXXXXXX,    MO(6), XXXXXXX
    ),
    [7] = LAYOUT( //Fnキー　左アロー
        A(KC_GRV), KC_ESC, KC_UP, XXXXXXX, XXXXXXX, KC_VOLD,         KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX, KC_DEL,
        KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, KC_VOLU,       KC_F5, KC_F6, KC_F7, KC_F8, XXXXXXX, KC_BSPC,            
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,         KC_F1, KC_F2, KC_F3, KC_F4, XXXXXXX, MO(7), 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_RCTL, XXXXXXX, KC_RSFT, 
                                        MO(7), XXXXXXX,    XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX
    ),
    [8] = LAYOUT( //記号キー　右アロー
        KC_ESC, S(KC_1), S(KC_2), S(KC_3), S(KC_5), S(KC_6),         S(KC_8), S(KC_9), KC_QUOT, KC_SCLN, KC_EQL, KC_DEL,
        KC_LSFT, XXXXXXX, XXXXXXX, S(KC_7), S(KC_4), KC_GRV,         KC_GRV, KC_RBRC, KC_BSLS, KC_UP, XXXXXXX, KC_BSPC,            
        KC_LSFT, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, KC_PSCR,        XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INT1, 
        KC_LCTL, KC_LGUI, KC_LALT,                                   KC_RCTL, KC_SLSH, KC_RSFT, 
                                XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                MO(8), XXXXXXX,      XXXXXXX, MO(8)
    ),
    [9] = LAYOUT( //左テンキー　右アロー
        A(KC_GRV), S(KC_QUOT), KC_7, KC_8, KC_9, KC_MINS,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
        KC_TAB, KC_BSLS, KC_4, KC_5, KC_6, S(KC_SCLN),        XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, KC_BSPC,            
        KC_LSFT, KC_0, KC_1, KC_2, KC_3, KC_DOT,                XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT, 
        KC_LCTL, KC_LGUI, KC_LALT,                                                   KC_RCTL, XXXXXXX, KC_RSFT, 
                                XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                XXXXXXX, MO(9),      XXXXXXX, XXXXXXX
    )
};

