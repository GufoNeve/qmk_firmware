// Copyright 2024 Fukuro
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
/**/
#define PMW33XX_CS_PIN  GP0
#define PMW33XX_CPI 950
#define PMW33XX_CLOCK_SPEED 2000000
#define MOUSE_EXTENDED_REPORT
#define POINTING_DEVICE_INVERT_X
#define SPI_SCK_PIN GP10
#define SPI_MISO_PIN GP12
#define SPI_MOSI_PIN GP11
#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE

#define POINTING_DEVICE_RIGHT

#define OLED_DEFAULT true           // true: レイヤー表示, false: 数値表示
#define INTERRUPT_TIME 600

#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN        GP7
#define I2C1_SDA_PIN        GP8
#define OLED_FONT_H "./lib/glcdfont.c"

#define RGBLIGHT_LAYERS_RETAIN_VAL
#define SPLIT_LAYER_STATE_ENABLE
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_MAX_LAYERS 6

#define DYNAMIC_KEYMAP_LAYER_COUNT 6


