// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

#define TERM_SCROLL 400
#define TERM_SLOW 400
#define CPI_SLOW 600

// 追加するキーコード
enum TH_keycodes{
    CMD_CTL = QK_KB_0,
    CAPTCHA,
    CPI_I,
    CPI_D,
    ANG_I,
    ANG_D,
    INV,
    CHMOD,
    INV_SCRL,
    MOD_SCRL,
    AUTO_MOUSE,
    ESC_SCRL,
    TAB_SCRL,
    LNG1_SCRL,
    LNG2_SCRL,
    MOD_SLOW,
    ESC_SLOW,
    TAB_SLOW,
    LNG1_SLOW,
    LNG2_SLOW,
    BTN1_SLOW,
    BTN2_SLOW,
    BTN3_SLOW
};

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record);