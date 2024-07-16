// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"
#include "config.h"

// 定数          
#define NO_JOYSTICK_VAL 100         // JSの有無判定閾値
#define KEY_OFFSET 7                // キー入力閾値
#define TIMEOUT_KEY 80              // キー入力間隔
#define JOYSTICK_MOVE_OFFSET 100    // ジョイスティック移動閾値
#define SCROLL_DIVISOR 50.0        // スクロール用数値調整
#define JOYSTICK_DIVISOR 40.0       // ジョイスティック用調整用
#define TERM_TEMP 100               // 一時的モード変更タップ判定ms
#define INTERRUPT_TIME 600          // OLED切り替え時間

// 保存される設定の定義
typedef union{
    uint32_t raw;
    struct{
        uint8_t spd_0     :3; // ポインター速度 最大値7
        uint8_t angle_0   :5; // ポインター角度 最大値29
        uint8_t pd_mode_0 :2; // カーソル移動/スクロールモード/キー入力モード
        bool inv_0        :1; // トラックボール / ジョイスティック左右反転ON/OFF
        
        uint8_t spd_1     :3; // ポインター速度 最大値7
        uint8_t angle_1   :5; // ポインター角度 最大値59 
        uint8_t pd_mode_1 :2; // カーソル移動/スクロールモード/キー入力モード
        bool inv_1        :1; // トラックボール / ジョイスティック左右反転
        
        bool inv_sc     :1; // スクロールの反転ON/OFF
        bool auto_mouse :1; // オートマウスON/OFF
        bool oled_mode  :1; // oled表示
        bool js_side    :1;
    };
} ut_config_t;

// 外部参照用
extern ut_config_t ut_config;

// インターフェース
uint8_t get_joystick_attached(void);             // ジョイスティックの有無
void cycle_mode(bool side);                        // モード変更
void is_scroll_mode(bool is_force_scrolling); // 一時的モード変更
void is_cursor_mode(bool is_force_scrolling);
void is_key_mode(bool is_force_key_input);
void is_slow_mode(bool is_slow_mode);
bool get_dpad_exclusion(void);
void toggle_dpad_exclusion(void);