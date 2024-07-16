// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_keycodes.h"
#include "quantum.h"
#include "os_detection.h"
#include "add_trackball.h"

// スクロールボタンをマウスキー扱いに
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case MOD_SCRL:
            return true;
        case BTN1_SLOW:
            return true;
        case BTN2_SLOW:
            return true;
        case BTN3_SLOW:
            return true;
        default:
            return false;
    }
}

uint16_t startup_timer;

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case CMD_CTL:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CAPTCHA:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case CPI_I:
            if (record->event.pressed) {
                ballconfig.cpi_idx = ballconfig.cpi_idx + 1;
                if(ballconfig.cpi_idx >= CPI_OPTION_SIZE){
                    ballconfig.cpi_idx = CPI_OPTION_SIZE-1;
                }
                eeconfig_update_user(ballconfig.raw);
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
            }
            return false;
            break;
        case CPI_D:
            if (record->event.pressed) {
                if(ballconfig.cpi_idx > 0){
                    ballconfig.cpi_idx = ballconfig.cpi_idx - 1;
                }
                eeconfig_update_user(ballconfig.raw);
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
            }
            return false;
            break;
        case ANG_I:
            if (record->event.pressed) {
                ballconfig.angle_idx = (ballconfig.angle_idx + 1) % ANGLE_OPTION_SIZE;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case ANG_D:
            if (record->event.pressed) {
                ballconfig.angle_idx = (ANGLE_OPTION_SIZE + ballconfig.angle_idx - 1) % ANGLE_OPTION_SIZE;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case INV:
            if (record->event.pressed) {
                ballconfig.inv = !ballconfig.inv;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case CHMOD:
            if (record->event.pressed) {
                ballconfig.scmode = !ballconfig.scmode;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case INV_SCRL:
            if (record->event.pressed) {
                ballconfig.inv_sc = !ballconfig.inv_sc;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case MOD_SCRL:
            scrolling = record->event.pressed;
            return false;
            break;
        case AUTO_MOUSE:
            if (record->event.pressed) {
                ballconfig.auto_mouse = !ballconfig.auto_mouse;
                set_auto_mouse_enable(ballconfig.auto_mouse);
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case ESC_SCRL:
            if (record->event.pressed) {
                startup_timer = timer_read();
                scrolling = true;
            } else {
                scrolling = false;
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_ESC);  
                }
            }
            return false;
            break;
        case TAB_SCRL:
            if (record->event.pressed) {
                startup_timer = timer_read();
                scrolling = true;
            } else {
                scrolling = false;
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_TAB); 
                }
            }
            return false;
            break;
        case LNG1_SCRL:
            if (record->event.pressed) {
                startup_timer = timer_read();
                scrolling = true;
            } else {
                scrolling = false;
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_LNG1);  
                }
            }
            return false;
            break;
        case LNG2_SCRL:
          if (record->event.pressed) {
                startup_timer = timer_read();
                scrolling = true;
            } else {
                scrolling = false;
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_LNG2);  
                }
            }
            return false;
            break;
        case MOD_SLOW:
            if (record->event.pressed) {
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
            }
            return false;
            break;
        case ESC_SLOW:
            if (record->event.pressed) {
                startup_timer = timer_read();
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_ESC);  
                }
            }
            return false;
            break;
        case TAB_SLOW:
            if (record->event.pressed) {
                startup_timer = timer_read();
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_TAB); 
                }
            }
            return false;
            break;
        case LNG1_SLOW:
            if (record->event.pressed) {
                startup_timer = timer_read();
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_LNG1);  
                }
            }
            return false;
            break;
        case LNG2_SLOW:
          if (record->event.pressed) {
                startup_timer = timer_read();
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                if(timer_elapsed(startup_timer) < TERM_SCROLL){
                    tap_code(KC_LNG2);  
                }
            }
            return false;
            break;
        case BTN1_SLOW:
            if (record->event.pressed) {
                register_code(KC_BTN1);
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                unregister_code(KC_BTN1);
            }
            return false;
            break;
        case BTN2_SLOW:
            if (record->event.pressed) {
                register_code(KC_BTN2);
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                unregister_code(KC_BTN2);
            }
            return false;
            break;
        case BTN3_SLOW:
          if (record->event.pressed) {
                register_code(KC_BTN3);
                pointing_device_set_cpi(CPI_SLOW);
            } else {
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
                unregister_code(KC_BTN3);
            }
            return false;
            break;
    }
    return true;
}