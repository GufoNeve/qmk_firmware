// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_trackball.h"
#include "math.h"
#include "quantum.h"

// ファイル外参照変数
ballconfig_t ballconfig;
bool scrolling;
uint16_t cpi_array[] = CPI_OPTIONS;
uint16_t angle_array[] = ANGLE_OPTIONS;
// ファイル内のみ変数
float scroll_accumulated_h;
float scroll_accumulated_v;

// eeprom初期化
void eeconfig_init_user(void) {
    ballconfig.cpi_idx = CPI_DEFAULT;
    ballconfig.angle_idx = ANGLE_DEFAULT;
    ballconfig.inv = false;
    ballconfig.scmode = false;
    ballconfig.inv_sc = false;
    ballconfig.auto_mouse = false;
    eeconfig_update_user(ballconfig.raw);
}

// トラックボール初期化
void pointing_device_init_user(void) {
    scrolling = false;
    scroll_accumulated_h = 0;
    scroll_accumulated_v = 0;
    ballconfig.raw = eeconfig_read_user();
    pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
    set_auto_mouse_enable(ballconfig.auto_mouse);
}

// カーソル調整
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    double rad = angle_array[ballconfig.angle_idx] * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    if(ballconfig.inv){
            x_rev = -1 * x_rev;
    }
    if(scrolling || ballconfig.scmode){
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        mouse_report.h = x_rev;
        mouse_report.v = y_rev;
        if(!ballconfig.inv_sc ){

            mouse_report.h = -1 * mouse_report.h;
            mouse_report.v = -1 * mouse_report.v;
        }

        scroll_accumulated_h += (float)mouse_report.h / SCROLL_DIVISOR;
        scroll_accumulated_v += (float)mouse_report.v / SCROLL_DIVISOR;
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        mouse_report.x = 0;
        mouse_report.y = 0;
    }else{
        mouse_report.x = -1 * x_rev;
        mouse_report.y = y_rev;
    }
    return mouse_report;
}


