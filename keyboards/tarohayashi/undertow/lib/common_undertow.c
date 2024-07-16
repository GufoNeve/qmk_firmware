// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/common_undertow.h"
#include "analog.h"
#include "math.h"
#include "os_detection.h"
#include "lib/add_keycodes.h"
#include "lib/add_oled.h"

/* ポインティングデバイス用変数 */
ut_config_t ut_config;         // eeprom保存用
bool force_scrolling;          // 一時的モード変更用
bool force_cursoring; 
bool force_key_input;
bool slow_mode;      
uint8_t joystick_attached;     // ジョイスティックの有無
bool joystick_initialized;     // ジョイスティックの有無
float scroll_accumulated_h;  // スクロール端数保存用
float scroll_accumulated_v;
int16_t gp28_newt;              // ジョイスティックの初期値
int16_t gp29_newt; 


// 仮想十字キー設定用
keypos_t key_up_0;
keypos_t key_down_0;
keypos_t key_left_0;
keypos_t key_right_0;
keypos_t key_up_1;
keypos_t key_down_1;
keypos_t key_left_1;
keypos_t key_right_1;
bool pressed_up;
bool pressed_down;
bool pressed_left;
bool pressed_right;
int8_t layer;
int16_t keycode_up_0;
int16_t keycode_down_0;
int16_t keycode_left_0;
int16_t keycode_right_0;
int16_t keycode_up_1;
int16_t keycode_down_1;
int16_t keycode_left_1;
int16_t keycode_right_1;
int16_t keycode_up_js;
int16_t keycode_down_js;
int16_t keycode_left_js;
int16_t keycode_right_js;
int16_t key_timer_0;
int16_t key_timer_1;

// 斜め入力防止用
bool dpad_exclusion;
uint8_t dpad_pressed_0;
uint8_t dpad_pressed_1;


/* eeprom */
// 初期化
void eeconfig_init_kb(void) {
    ut_config.spd_0 = SPD_DEFAULT_SIDE0;
    ut_config.spd_1 = SPD_DEFAULT_SIDE1;
    ut_config.angle_0 = ANGLE_DEFAULT_SIDE0;
    ut_config.angle_1 = ANGLE_DEFAULT_SIDE1;
    ut_config.pd_mode_0 = TB_SIDE0_DEFAULT;
    ut_config.pd_mode_1 = TB_SIDE1_DEFAULT;
    ut_config.inv_0 = SIDE0_INVERT;
    ut_config.inv_1 = SIDE1_INVERT;
    ut_config.inv_sc = SCROLL_INVERT;
    ut_config.auto_mouse = AUTO_MOUSE_DEFAULT;
    ut_config.oled_mode = OLED_DEFAULT;
    ut_config.js_side = JS_SIDE_DEFAULT;
    eeconfig_update_kb(ut_config.raw);

    eeconfig_init_user();
}

/* キースキャン */
// マウスキー登録
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case MOD_CUR: // 一時的にカーソル移動
            return true;
        case MOD_SCRL: // 一時的にスクロール
            return true;
        case MOD_SLOW: // 一時的に減速
            return true;
        default:
            return false;
    }   

    return  is_mouse_record_user(keycode, record);
}
// 実タスク
bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // 追加キーコードタスク
    process_record_addedkeycodes(keycode, record);

    // D-Padの同時押しを防ぐ
    keypos_t key = record->event.key;
    if(key.col == 5 && dpad_exclusion){
        switch (key.row){
            case 0:
            case 1:
            case 2:
            case 3:
                if(dpad_pressed_0 == 0 && record->event.pressed){
                    if(record->event.pressed){
                        dpad_pressed_0  = key.row;
                    }
                }else if(dpad_pressed_0 == key.row && !record->event.pressed){
                    dpad_pressed_0  = 0;
                }else if(record->event.pressed){
                    return false;
                }
                break;
            case 6:
                if(!joystick_initialized){
                    joystick_attached = 0;
                    ut_config.js_side = 0;
                    eeconfig_update_kb(ut_config.raw);  
                }
        }
    }
    if(key.col == 7 && dpad_exclusion){
        switch (key.row){
            case 0:
            case 1:
            case 2:
            case 3:
                if(dpad_pressed_1 == 0 && record->event.pressed){
                    if(record->event.pressed){
                        dpad_pressed_1 = key.row;
                    }
                }else if(dpad_pressed_1 == key.row && !record->event.pressed){
                    dpad_pressed_1 = 0;
                }else if(record->event.pressed){
                    return false;
                }
                break;
            case 4:
                if(!joystick_initialized){
                    joystick_attached = 1;
                    ut_config.js_side = 1;
                    eeconfig_update_kb(ut_config.raw);
                }
        }
    }
    return process_record_user(keycode, record);
}

/* マトリクス走査 */
// 初期化
void matrix_init_kb(void) {
    key_up_0.row = 3;
    key_up_0.col = 5;
    key_down_0.row = 1;
    key_down_0.col = 5;
    key_left_0.row = 2;
    key_left_0.col = 5;
    key_right_0.row = 0;
    key_right_0.col = 5;
    key_up_1.row = 3;
    key_up_1.col = 7;
    key_down_1.row = 1;
    key_down_1.col = 7;
    key_left_1.row = 2;
    key_left_1.col = 7;
    key_right_1.row = 0;
    key_right_1.col = 7;
    dpad_pressed_0 = 0;
    dpad_pressed_1 = 0;
    force_scrolling = false;
    force_cursoring = false;
    force_key_input = false;
    pressed_up = false;
    pressed_down = false;
    pressed_left = false;
    pressed_right = false;
    slow_mode = false;
    gp28_newt = analogReadPin(GP28);
    gp29_newt = analogReadPin(GP29);
    if(gp28_newt < NO_JOYSTICK_VAL ||  gp29_newt < NO_JOYSTICK_VAL ){
        joystick_attached = 2;
    }else{
        joystick_attached = JS_SIDE_DEFAULT;
    }
    joystick_initialized = false;
    key_timer_0 = timer_read();
    key_timer_1 = timer_read();
    dpad_exclusion = true;

    matrix_init_user();
}


/* カーソル操作 */
// 初期化
void pointing_device_init_kb(void){
    ut_config.raw = eeconfig_read_kb();
    scroll_accumulated_h = 0;
    scroll_accumulated_v = 0;
    pmw33xx_init(1);
    pmw33xx_set_cpi(0, 1000 + ut_config.spd_0 * 250); // SIDE0
    pmw33xx_set_cpi(1, 1000 + ut_config.spd_1 * 250); // SIDE1

    if(joystick_attached != 2){
        joystick_attached = ut_config.js_side;
    }
    set_auto_mouse_enable(ut_config.auto_mouse);

    pointing_device_init_user();
}
// 実タスク
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    /* SIDE0 */
    // 数値取得、角度、反転処理
    double rad = (double)ut_config.angle_0 * 12.0 * (M_PI / 180.0) * -1.0;
    double x_rev_0 =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    double y_rev_0 =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);
    double h_rev_0 = 0.0;
    double v_rev_0 = 0.0;
    if(ut_config.inv_0){ x_rev_0 = -1.0 * x_rev_0; }
    // モード決定
    uint8_t cur_mode = ut_config.pd_mode_0;
    if(force_cursoring){
        cur_mode = CURSOR_MODE;
    }else if(force_scrolling){
        cur_mode = SCROLL_MODE;
    }else if(force_key_input){
        cur_mode = KEY_INPUT;
    }
    // スクロール処理
    if(cur_mode == SCROLL_MODE){
        // 斜め成分を消す
        if (abs(x_rev_0) > abs(y_rev_0)) {
            y_rev_0 = 0.0;
        } else {
            x_rev_0 = 0.0;
        }
        // スクロール反転処理
        if(!ut_config.inv_sc ){
            x_rev_0 = -1.0 * x_rev_0;
            y_rev_0 = -1.0 * y_rev_0;
        }
        h_rev_0 = x_rev_0;
        v_rev_0 = y_rev_0;
        x_rev_0 = 0.0;
        y_rev_0 = 0.0;
    // キー入力処理
    }else if(cur_mode == KEY_INPUT){
        layer = layer_switch_get_layer(key_up_0);
        keycode_up_0 = keymap_key_to_keycode(layer, key_up_0);
        keycode_left_0 = keymap_key_to_keycode(layer, key_left_0);
        keycode_right_0 = keymap_key_to_keycode(layer, key_right_0);
        keycode_down_0 = keymap_key_to_keycode(layer, key_down_0); 
        // 斜め成分を消す
        if (abs(x_rev_0) > abs(y_rev_0)) {
            y_rev_0 = 0.0;
        } else {
            x_rev_0 = 0.0;
        }
        if(timer_elapsed(key_timer_0) > TIMEOUT_KEY){
            if((int16_t)x_rev_0 > KEY_OFFSET){
                tap_code16(keycode_right_0);
            }else if((int16_t)x_rev_0  < -KEY_OFFSET){
                tap_code16(keycode_left_0);
            }
            if((int16_t)y_rev_0 > KEY_OFFSET){
                tap_code16(keycode_down_0);
            }else if((int16_t)y_rev_0 < -KEY_OFFSET){
                tap_code16(keycode_up_0);
            }
            key_timer_0 = timer_read();
        }
        x_rev_0 = 0.0;
        y_rev_0 = 0.0;
    }
    
    /* SIDE1 */
    // 数値取得、角度、反転処理
    pmw33xx_report_t report = pmw33xx_read_burst(1);
    rad = (double)ut_config.angle_1 * 12.0 * (M_PI / 180.0) * -1.0;
    double x_rev_1 =  + report.delta_x * cos(rad) - report.delta_y * sin(rad);
    double y_rev_1 =  + report.delta_x * sin(rad) + report.delta_y * cos(rad);
    double h_rev_1 = 0.0;
    double v_rev_1 = 0.0;
    if(ut_config.inv_1){ x_rev_1 = -1.0 * x_rev_1; }
    // モード決定
    cur_mode = ut_config.pd_mode_1;
    if(force_cursoring){
        cur_mode = CURSOR_MODE;
    }else if(force_scrolling){
        cur_mode = SCROLL_MODE;
    }else if(force_key_input){
        cur_mode = KEY_INPUT;
    }
    // スクロール処理
    if(cur_mode == SCROLL_MODE){
        // 斜め成分を消す
        if (abs(x_rev_1) > abs(y_rev_1)) {
            y_rev_1 = 0.0;
        } else {
            x_rev_1 = 0.0;
        }
        // スクロール反転処理
        if(!ut_config.inv_sc ){
            x_rev_1 = -1.0 * x_rev_1;
            y_rev_1 = -1.0 * y_rev_1;
        }
        h_rev_1 = x_rev_1;
        v_rev_1 = y_rev_1;
        x_rev_1 = 0.0;
        y_rev_1 = 0.0;
    // キー入力処理
    }else if(cur_mode == KEY_INPUT){
        layer = layer_switch_get_layer(key_up_1);
        keycode_up_1 = keymap_key_to_keycode(layer, key_up_1);
        keycode_left_1 = keymap_key_to_keycode(layer, key_left_1);
        keycode_right_1 = keymap_key_to_keycode(layer, key_right_1);
        keycode_down_1 = keymap_key_to_keycode(layer, key_down_1); 
        // 斜め成分を消す
        if (abs(x_rev_1) > abs(y_rev_1)) {
            y_rev_1 = 0.0;
        } else {
            x_rev_1 = 0.0;
        }
        if(timer_elapsed(key_timer_1) > TIMEOUT_KEY){
            if((int16_t)x_rev_1 > KEY_OFFSET){
                tap_code16(keycode_right_1);
            }else if((int16_t)x_rev_1  < -KEY_OFFSET){
                tap_code16(keycode_left_1);
            }
            if((int16_t)y_rev_1 > KEY_OFFSET){
                tap_code16(keycode_down_1);
            }else if((int16_t)y_rev_1 < -KEY_OFFSET){
                tap_code16(keycode_up_1);
            }
            key_timer_1 = timer_read();
        }
        x_rev_1 = 0.0;
        y_rev_1 = 0.0;
    }

    /* JOYSTICK */        
    double x_rev_js = 0.0;
    double y_rev_js = 0.0;
    double h_rev_js = 0.0;
    double v_rev_js = 0.0;
    if(joystick_attached != 2){
        // モード決定
        double amp_temp;
        bool inv_js;
        if(joystick_attached == 0){
            cur_mode = ut_config.pd_mode_0;
            rad = (double)ut_config.angle_0 * 12.0 * (M_PI / 180.0) * -1.0;
            layer = layer_switch_get_layer(key_up_0);
            keycode_up_js = keymap_key_to_keycode(layer, key_up_0);
            keycode_left_js = keymap_key_to_keycode(layer, key_left_0);
            keycode_right_js = keymap_key_to_keycode(layer, key_right_0);
            keycode_down_js = keymap_key_to_keycode(layer, key_down_0); 
            amp_temp = 16.0 + (double)ut_config.spd_0 * 3.0;
            inv_js = ut_config.inv_0;
        }else{
            cur_mode = ut_config.pd_mode_1;
            rad = (double)ut_config.angle_1 * 12.0 * (M_PI / 180.0) * -1.0;
            layer = layer_switch_get_layer(key_up_1);
            keycode_up_js = keymap_key_to_keycode(layer, key_up_1);
            keycode_left_js = keymap_key_to_keycode(layer, key_left_1);
            keycode_right_js = keymap_key_to_keycode(layer, key_right_1);
            keycode_down_js = keymap_key_to_keycode(layer, key_down_1); 
            amp_temp = 16.0 + (double)ut_config.spd_1 * 3.0;
            inv_js = ut_config.inv_1;
        }
        if(force_cursoring){
            cur_mode = CURSOR_MODE;
        }else if(force_scrolling){
            cur_mode = SCROLL_MODE;
        }else if(force_key_input){
            cur_mode = KEY_INPUT;
        }
        // amprifier値決定
        if(slow_mode){
            amp_temp = AMP_SLOW;
        }
        if(cur_mode == CURSOR_MODE){
            amp_temp = amp_temp / 20;
        }else if(cur_mode == SCROLL_MODE){
            amp_temp = amp_temp / 30;
        }else{
            amp_temp = amp_temp / 10;
        }
        // 数値の取得と補正
        int16_t gp29val = analogReadPin(GP29) - gp29_newt;
        int16_t gp28val = analogReadPin(GP28) - gp28_newt;

        if(abs(gp29val)<JOYSTICK_MOVE_OFFSET){
            gp29val = 0;
        }
        if(abs(gp28val)<JOYSTICK_MOVE_OFFSET){
            gp28val = 0;
        }
        double x_val_js = ( (double)gp29val / JOYSTICK_DIVISOR ) * amp_temp;
        double y_val_js = ( (double)gp28val / JOYSTICK_DIVISOR ) * amp_temp;
        // 角度補正
        x_rev_js =  + x_val_js * cos(rad) - y_val_js * sin(rad);
        y_rev_js =  + x_val_js * sin(rad) + y_val_js * cos(rad);
        // x軸反転処理
        if(inv_js){ x_rev_js = -1.0 * x_rev_js; }
        // スクロール処理
        if(cur_mode == SCROLL_MODE){
            // 斜め成分を消す
            if (abs(x_rev_js) > abs(y_rev_js)) {
                y_rev_js = 0.0;
            } else {
                x_rev_js = 0.0;
            }
            // スクロール反転処理
            if(!ut_config.inv_sc ){
                x_rev_js = -1.0 * x_rev_js;
                y_rev_js = -1.0 * y_rev_js;
            }
            h_rev_js = x_rev_js;
            v_rev_js = y_rev_js;
            x_rev_js = 0.0;
            y_rev_js = 0.0;
        // キー入力処理
        }else if(cur_mode == KEY_INPUT){
            // 斜め成分を消す
            if (abs(x_rev_js) > abs(y_rev_js)) {
                y_rev_js = 0;
            } else {
                x_rev_js = 0;
            }
            if(!pressed_left && (int16_t)x_rev_js > KEY_OFFSET){
                pressed_left = true;
                register_code(keycode_right_js);
            }else if(pressed_left && (int16_t)x_rev_js  < KEY_OFFSET){
                pressed_left = false;
                unregister_code(keycode_right_js);
            }else if(!pressed_right && (int16_t)x_rev_js  < -KEY_OFFSET){
                pressed_right = true;
                register_code(keycode_left_js);
            }else if (pressed_right && (int16_t)x_rev_js  > -KEY_OFFSET){
                pressed_right = false;
                unregister_code(keycode_left_js);
            }

            if(!pressed_up && (int16_t)y_rev_js > KEY_OFFSET){
                pressed_up = true;
                register_code(keycode_down_js);
            }else if(pressed_up && (int16_t)y_rev_js < KEY_OFFSET){
                pressed_up = false;
                unregister_code(keycode_down_js);
            }else if(!pressed_down && (int16_t)y_rev_js < -KEY_OFFSET){
                pressed_down = true;
                register_code(keycode_up_js);
            }else if(pressed_down && (int16_t)y_rev_js > -KEY_OFFSET){
                pressed_down = false;
                unregister_code(keycode_up_js);
            }
            x_rev_js = 0.0;
            y_rev_js = 0.0;
        }
    }

    // SUM
    mouse_report.x = (int8_t)constrain_hid(x_rev_0 + x_rev_1 + x_rev_js);
    mouse_report.y = (int8_t)constrain_hid(y_rev_0 + y_rev_1 + y_rev_js);

    scroll_accumulated_h += constrain_hid((float)(h_rev_0 + h_rev_1 + h_rev_js) / SCROLL_DIVISOR);
    scroll_accumulated_v += constrain_hid((float)(v_rev_0 + v_rev_1 + v_rev_js) / SCROLL_DIVISOR);
    mouse_report.h = (int8_t)scroll_accumulated_h;
    mouse_report.v = (int8_t)scroll_accumulated_v;
    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
    
    return pointing_device_task_user(mouse_report);
}

/* OLED */
// 初期化
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // 追加OLED初期化
    oled_init_addedoled();

    return oled_init_user(rotation);
}
// 実タスク
bool oled_task_kb(void) {
    // 追加OLEDタスク
    oled_task_addedoled();

    return oled_task_user();
}


/* 諸関数 */
// モードチェンジ時端数削除
void clear_keyinput(void){
    unregister_code(keycode_up_0);
    unregister_code(keycode_down_0);
    unregister_code(keycode_left_0);
    unregister_code(keycode_right_0);
    unregister_code(keycode_up_1);
    unregister_code(keycode_down_1);
    unregister_code(keycode_left_1);
    unregister_code(keycode_right_1);
    scroll_accumulated_v = 0;
    scroll_accumulated_h = 0;
}
/* インターフェース */
// ジョイスティックの有無
uint8_t get_joystick_attached(void){ return joystick_attached; }
// モード変更
void cycle_mode(bool side){
    if(side){
        ut_config.pd_mode_1 = (ut_config.pd_mode_1 + 1) % 3;
        eeconfig_update_kb(ut_config.raw);
        clear_keyinput();
    }else{
        ut_config.pd_mode_0 = (ut_config.pd_mode_0 + 1) % 3;
        eeconfig_update_kb(ut_config.raw);
        clear_keyinput();
    }
}
// 一時的モード変更
void is_scroll_mode(bool is_force_scrolling){
    force_scrolling = is_force_scrolling; 
    clear_keyinput();
}
void is_cursor_mode(bool is_force_cursoring){
    force_cursoring = is_force_cursoring;
    clear_keyinput();
}
void is_key_mode(bool is_force_key_input){
    force_key_input = is_force_key_input;
    clear_keyinput();
}
void is_slow_mode(bool is_slow_mode){
    slow_mode = is_slow_mode;
    if(is_slow_mode){
        pmw33xx_set_cpi(0, CPI_SLOW);
        pmw33xx_set_cpi(1, CPI_SLOW);
    }else{
        pmw33xx_set_cpi(0, 1000 + ut_config.spd_0 * 250);
        pmw33xx_set_cpi(1, 1000 + ut_config.spd_1 * 250);
    }
    clear_keyinput();
}
bool get_dpad_exclusion(void){
    return dpad_exclusion;
}
void toggle_dpad_exclusion(void){
    dpad_exclusion = !dpad_exclusion;
}
