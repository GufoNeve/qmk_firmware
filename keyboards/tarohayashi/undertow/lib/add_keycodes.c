// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

uint16_t startup_timer;
#include "lib/add_keycodes.h"
#include "os_detection.h"
#include "lib/common_undertow.h"
#include "lib/add_oled.h"


uint16_t startup_timer;

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPD_I_0:
            if (record->event.pressed) {
                ut_config.spd_0 = ut_config.spd_0 + 1;
                if(ut_config.spd_0 >= SPD_OPTION_MAX){
                    ut_config.spd_0 = SPD_OPTION_MAX-1;
                }
                eeconfig_update_kb(ut_config.raw);
                pmw33xx_set_cpi(0,  1000 + ut_config.spd_0 * 250);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SPD_I_1:
            if (record->event.pressed) {
                ut_config.spd_1 = ut_config.spd_1 + 1;
                if(ut_config.spd_1 >= SPD_OPTION_MAX){
                    ut_config.spd_1 = SPD_OPTION_MAX-1;
                }
                eeconfig_update_kb(ut_config.raw);
                pmw33xx_set_cpi(1,  1000 + ut_config.spd_1 * 250);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SPD_D_0:
            if (record->event.pressed) {
                if(ut_config.spd_0 > 0){
                    ut_config.spd_0 = ut_config.spd_0 - 1;
                }
                eeconfig_update_kb(ut_config.raw);
                pmw33xx_set_cpi(0,  1000 + ut_config.spd_0 * 250);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SPD_D_1:
            if (record->event.pressed) {
                if(ut_config.spd_1 > 0){
                    ut_config.spd_1 = ut_config.spd_1 - 1;
                }
                eeconfig_update_kb(ut_config.raw);
                pmw33xx_set_cpi(1,  1000 + ut_config.spd_1 * 250);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case ANG_I_0:
            if (record->event.pressed) {
                ut_config.angle_0 = (ut_config.angle_0 + 1) % ANGLE_OPTION_MAX;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case ANG_I_1:
            if (record->event.pressed) {
                ut_config.angle_1 = (ut_config.angle_1 + 1) % ANGLE_OPTION_MAX;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case ANG_D_0:
            if (record->event.pressed) {
                ut_config.angle_0 = (ANGLE_OPTION_MAX + ut_config.angle_0 - 1) % ANGLE_OPTION_MAX;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case ANG_D_1:
            if (record->event.pressed) {
                ut_config.angle_1 = (ANGLE_OPTION_MAX + ut_config.angle_1 - 1) % ANGLE_OPTION_MAX;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case INV_0:
            if (record->event.pressed) {
                ut_config.inv_0 = !ut_config.inv_0;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case INV_1:
            if (record->event.pressed) {
                ut_config.inv_1 = !ut_config.inv_1;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
         case CHMOD_0:
            if (record->event.pressed) {
                cycle_mode(0);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case CHMOD_1:
            if (record->event.pressed) {
                cycle_mode(1);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case INV_SCRL:
            if (record->event.pressed) {
                ut_config.inv_sc = !ut_config.inv_sc;
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case AUTO_MOUSE:
            if (record->event.pressed) {
                ut_config.auto_mouse = !ut_config.auto_mouse;
                set_auto_mouse_enable(ut_config.auto_mouse);
                eeconfig_update_kb(ut_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case OLED_MOD:
            if (record->event.pressed) {
                ut_config.oled_mode = !ut_config.oled_mode;
                oled_clear();
                oled_interrupt(keycode);
            }
            return false;
            break;
        case DPAD_MOD:
            if (record->event.pressed) {
                toggle_dpad_exclusion();
                oled_interrupt(keycode);
            }
            return false;
            break;
        case MOD_CUR:
            is_cursor_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        case MOD_SCRL:
            is_scroll_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        case MOD_KEY:
            is_key_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        case MOD_SLOW:
            is_slow_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
    }
    if (record->event.pressed) {
        oled_interrupt(keycode);
    }
    return true;
}