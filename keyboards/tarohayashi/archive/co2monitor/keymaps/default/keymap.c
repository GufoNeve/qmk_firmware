// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"


// CO2濃度警告の閾値
#define ALARTTHRESHOLD 2000
// 安全圏の色
#define SAFEHUE 150
// 更新間隔
#define SPAN 1000

// 定数
#define AD_VCC 4.850000
#define EMF_RANGE 0.045000
#define EMF_0_PPM 400.000000
#define EMF_1_PPM 4000.000000
#define EMF_MAX 0.220000
#define EMF_CHK_RANGE 0.002000
#define BOARD_GAIN 10.000000

// 変数
double emf_max = 0.200000;
double emf_chk = 0.200000;
double sum = 0.000000;

// キーボードの設定
enum co2_keycode{
    CO2_SAFE_RANGE = SAFE_RANGE,
    CHANGE_MODE,
};

enum led_mode{
    GRADATION = 0,
    THRESHOLD,
    OFF,
};
uint8_t mode = GRADATION;
uint8_t premode = GRADATION;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_1key(
    CHANGE_MODE
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == CHANGE_MODE && record->event.pressed) {
        mode = (mode + 1) % 3;
    }
    return true;
}


void matrix_scan_user(void) {
    
}

// OLEDの設定
uint8_t count;
uint16_t oled_timer;
#define SAMPLE 201
double val[SAMPLE];

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_timer = timer_read();
    count = 0;
    return OLED_ROTATION_180;
}

// フォントの定義
static const char PROGMEM numfont[][4][5] = {
    // 0
    {{0x23, 0x24, 0x25, 0x26, 0}, {0x27, 0x22, 0x22, 0x2A, 0}, {0x2B, 0x22, 0x22, 0x2E, 0}, {0x2F, 0x30, 0x31, 0x32, 0}},
    // 1
    {{0x22, 0x22, 0x22, 0x26, 0}, {0x22, 0x22, 0x22, 0x2A, 0}, {0x22, 0x22, 0x22, 0x2E, 0}, {0x22, 0x22, 0x22, 0x32, 0}},
    // 2
    {{0x22, 0x24, 0x25, 0x26, 0}, {0x22, 0x28, 0x29, 0x2A, 0}, {0x2B, 0x2C, 0x2D, 0x22, 0}, {0x2F, 0x30, 0x31, 0x22, 0}},
    // 3
    {{0x22, 0x24, 0x25, 0x26, 0}, {0x22, 0x28, 0x29, 0x2A, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x30, 0x31, 0x32, 0}},
    // 4
    {{0x23, 0x22, 0x22, 0x26, 0}, {0x27, 0x28, 0x29, 0x2A, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x22, 0x22, 0x32, 0}},
    // 5
    {{0x23, 0x24, 0x25, 0x22, 0}, {0x27, 0x28, 0x29, 0x22, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x30, 0x31, 0x32, 0}},
    // 6
    {{0x23, 0x24, 0x25, 0x22, 0}, {0x27, 0x28, 0x29, 0x22, 0}, {0x2B, 0x2C, 0x2D, 0x2E, 0}, {0x2F, 0x30, 0x31, 0x32, 0}},
    // 7
    {{0x22, 0x24, 0x25, 0x26, 0}, {0x22, 0x22, 0x22, 0x2A, 0}, {0x22, 0x22, 0x22, 0x2E, 0}, {0x22, 0x22, 0x22, 0x32, 0}},
    // 8
    {{0x23, 0x24, 0x25, 0x26, 0}, {0x27, 0x28, 0x29, 0x2A, 0}, {0x2B, 0x2C, 0x2D, 0x2E, 0}, {0x2F, 0x30, 0x31, 0x32, 0}},
    // 9
    {{0x23, 0x24, 0x25, 0x26, 0}, {0x27, 0x28, 0x29, 0x2A, 0}, {0x22, 0x2C, 0x2D, 0x2E, 0}, {0x22, 0x30, 0x31, 0x32, 0}},
    // NULL
    {{0x22, 0x22, 0x22, 0x22, 0}, {0x22, 0x22, 0x22, 0x22, 0}, {0x22, 0x22, 0x22, 0x22, 0}, {0x22, 0x22, 0x22, 0x22, 0}}
};
static const char PROGMEM ppmfont[] = {
    0x33, 0x34, 0x35, 0x36, 0x37, 0
};


bool oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 3500){
        double temp;
        // 中央値を求める
        for(int i = 0; i < SAMPLE; i++){
            for(int j = 0; j < SAMPLE; j++){
                if (val[i] < val[j]){
                    temp = val[i];
                    val[i] = val[j];
                    val[j] = temp;
                }
            }
        }
        double median = val[(SAMPLE - 1) / 2];

        // ppm決定
        double e = median / 1024.000000 * AD_VCC / BOARD_GAIN;
        double k = (1.000000 / EMF_RANGE) * log10( EMF_1_PPM / EMF_0_PPM);
        double ppm = EMF_0_PPM * pow(10.000000, (k * (emf_max - e)));

        // 最大電圧更新
        if(ppm < EMF_0_PPM){
            emf_chk = emf_max + EMF_CHK_RANGE;
            if(e >= emf_chk){
                emf_max = e;
            }
        }

        // OLED処理
        uint8_t ppmindex[4];
        if(ppm > 8888){
            ppm = 8888;
        }
        ppmindex[0] = (uint16_t)ppm / 1000;
        ppmindex[1] = ((uint16_t)ppm % 1000) / 100;
        ppmindex[2] = ((uint16_t)ppm % 100) / 10;
        ppmindex[3] = (uint16_t)ppm % 10;
        if(ppmindex[0] == 0){
            ppmindex[0] = 10;
        }
        oled_set_cursor(0,0);
        oled_write_P(numfont[ppmindex[0]][0], false);
        oled_write_P(numfont[ppmindex[1]][0], false);

        oled_write_P(numfont[ppmindex[2]][0], false);
        oled_write_P(numfont[ppmindex[3]][0], false);
        oled_set_cursor(0,1);
        oled_write_P(numfont[ppmindex[0]][1], false);
        oled_write_P(numfont[ppmindex[1]][1], false);
        oled_write_P(numfont[ppmindex[2]][1], false);
        oled_write_P(numfont[ppmindex[3]][1], false);
        oled_set_cursor(0,2);
        oled_write_P(numfont[ppmindex[0]][2], false);
        oled_write_P(numfont[ppmindex[1]][2], false);
        oled_write_P(numfont[ppmindex[2]][2], false);
        oled_write_P(numfont[ppmindex[3]][2], false);
        oled_set_cursor(0,3);
        oled_write_P(numfont[ppmindex[0]][3], false);
        oled_write_P(numfont[ppmindex[1]][3], false);
        oled_write_P(numfont[ppmindex[2]][3], false);
        oled_write_P(numfont[ppmindex[3]][3], false);
        oled_write_P(ppmfont, false);

        // LED処理
        oled_set_cursor(0,3);
        if(mode == GRADATION){
            uint16_t hue;
            if(ppm >= ALARTTHRESHOLD){
                hue = 0;
            } else{
                hue= SAFEHUE - (SAFEHUE * (ppm - EMF_0_PPM) / (ALARTTHRESHOLD - EMF_0_PPM) );
            }
            rgblight_sethsv(hue, 255, 200);
            if(premode != mode){
                oled_write_ln("LIGHTING: GRADATION", false);
                premode = mode;
            }
        } else if(mode == THRESHOLD){
            if(ppm <= ALARTTHRESHOLD){
                rgblight_sethsv(255, 255, 0);
            } else{
                rgblight_sethsv(255, 255, 200);
            }
            if(premode != mode){
                oled_write_ln("LIGHTING: THRESHOLD", false);
                premode = mode;
            }
        } else{
            rgblight_sethsv(255, 255, 0);
            if(premode != mode){
                oled_write_ln("LIGHTING: OFF", false);
                premode = mode;
            }
        }

        timer_clear();
        oled_timer = timer_read();
    }else{
        val[count % SAMPLE] = (double)analogReadPin(F7);

        if(count > SAMPLE){
            count = 0;
        }
        count++;
    
    }

    return false;
}

