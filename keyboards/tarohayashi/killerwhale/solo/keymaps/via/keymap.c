// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"

// レイヤー名
enum layer_number {
    // 左手用
    LEFT_BASE = 0, LEFT_LOWER,  LEFT_UPPER,            
    // 右手用
    RIGHT_BASE, RIGHT_LOWER, RIGHT_UPPER,
    // 自動マウスレイヤー切り替えや設定用のレイヤー
    UTIL, MOUSE , BALL_SETTINGS, LIGHT_SETTINGS    
};

// キーマップ
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LEFT_BASE] = LAYOUT(
        // 天面スイッチ
        KC_ESC,  KC_1, KC_2,                 KC_3, LT(BALL_SETTINGS, KC_4), LT(LIGHT_SETTINGS, KC_5),
        KC_TAB,  KC_Q, KC_W,                 KC_E, KC_R,                    KC_T,
        CMD_CTL, KC_A, KC_S, KC_D, KC_F,                    KC_G,
                 LSFT_T(KC_Z), KC_X,                 KC_C, KC_V,                    KC_B,
                       MOD_SCRL,
        // 側面スイッチ
        KC_LNG2, KC_SPACE,                             
        // 十字キーorジョイスティック                // ジョイスティックスイッチ
        KC_W, KC_S, KC_A, KC_D,                  L_CHMOD,                 
        KC_MS_BTN2, KC_MS_BTN1,                  MO(RIGHT_BASE)
    ),    
    [RIGHT_BASE] = LAYOUT(
        KC_BSPC,    KC_0,       KC_9,            KC_8,            LT(BALL_SETTINGS, KC_7), LT(LIGHT_SETTINGS, KC_6),
        KC_ENT,     KC_P,       KC_O,            KC_I,            KC_U,                 KC_Y,
        KC_RSFT,    KC_SCLN,    LT(MOUSE, KC_L), KC_K,            KC_J,                 KC_H,
                    KC_SLSH,    KC_DOT,          KC_COMM,         KC_M,                 KC_N,
                                MOD_SCRL,
        KC_SPACE, KC_LNG1,
        KC_LEFT, KC_RIGHT, KC_DOWN, KC_UP,        L_CHMOD,
        KC_MS_BTN2, KC_MS_BTN1,                  _______      
    ),
    [MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______,    _______,
        _______, _______, _______, _______, _______,    _______,
        _______, _______, _______, KC_MS_BTN2, KC_MS_BTN1, MOD_SCRL,
                 QK_USER_4, _______, _______, _______, _______,
                          MOD_SCRL,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______
    ),
    [BALL_SETTINGS] = LAYOUT(
        XXXXXXX,    XXXXXXX, XXXXXXX, QK_USER_14, _______,  L_CHMOD,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, L_SPD_I,    XXXXXXX,
        AUTO_MOUSE, XXXXXXX, XXXXXXX, L_ANG_D,  L_INV, L_ANG_I,
                    TG(RIGHT_BASE), XXXXXXX, XXXXXXX, L_SPD_D,    XXXXXXX,
                          INV_SCRL,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    ),
    [LIGHT_SETTINGS] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_MOD, _______,
        XXXXXXX, RGB_SPI, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG,
        OLED_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 RGB_SPD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX,
                          QK_USER_15,
        RGB_MOD, RGB_MOD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [LEFT_BASE] =   { 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(REDO, UNDO), 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)
    },
    [RIGHT_BASE] =   { 
        ENCODER_CCW_CW(KC_DEL, KC_BSPC), 
        ENCODER_CCW_CW(KC_UP, KC_DOWN), 
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)
    },
    [LIGHT_SETTINGS] = { 
        ENCODER_CCW_CW(RGB_SPI, RGB_SPD), 
        ENCODER_CCW_CW(RGB_VAI, RGB_VAD), 
        ENCODER_CCW_CW(RGB_SAI, RGB_SAD), 
        ENCODER_CCW_CW(RGB_HUI, RGB_HUD),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)
    }
};




