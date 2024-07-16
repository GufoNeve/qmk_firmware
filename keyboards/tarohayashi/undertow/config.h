// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define KEY_INPUT 0
#define CURSOR_MODE 1
#define SCROLL_MODE 2

/* ユーザー設定 */
// 入力モードデフォルト
#define TB_SIDE0_DEFAULT CURSOR_MODE
#define TB_SIDE1_DEFAULT CURSOR_MODE
#define JS_SIDE_DEFAULT 0 // 0: SIDE0, 1: SIDE1, 2: none

// CPI = 1000 + spd * 250 / AMP = 16.0 + (double)spd * 3.0
#define SPD_OPTION_MAX    7     // 最大値
#define SPD_DEFAULT_SIDE0 3
#define SPD_DEFAULT_SIDE1 3
// 角度 = angle * 12
#define ANGLE_OPTION_MAX    29  // 最大値 
#define ANGLE_DEFAULT_SIDE0 8
#define ANGLE_DEFAULT_SIDE1 7
#define SIDE0_INVERT true     // X軸の反転
#define SIDE1_INVERT true
#define SCROLL_INVERT false     // スクロールの反転

// スローモード時カーソル速度
#define CPI_SLOW 300 
#define AMP_SLOW 4.0 
// オートマウスの設定
#define AUTO_MOUSE_DEFAULT true
#define AUTO_MOUSE_DEFAULT_LAYER 1
#define AUTO_MOUSE_TIME 700
#define AUTO_MOUSE_DELAY 500
#define AUTO_MOUSE_DEBOUNCE 40
#define AUTO_MOUSE_THRESHOLD 60
// OLEDモードデフォルト
#define OLED_DEFAULT true //  true: show layer, false: show stats 



/* ハードウェア設定 */
// SPI
#define PMW33XX_CS_PINS  {GP1, GP5}
#define PMW33XX_CS_PINS_RIGHT  {GP1, GP5}
#define SPI_SCK_PIN GP2
#define SPI_MISO_PIN GP4
#define SPI_MOSI_PIN GP3
// I2C
#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN        GP9
#define I2C1_SDA_PIN        GP8
#define OLED_FONT_H "./lib/glcdfont.c"
// AUTO MOUSE
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// RGBLIGHT LAYERS
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 5