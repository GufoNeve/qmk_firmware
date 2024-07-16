// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// 追加するキーコード
enum TH_keycodes{
    SPD_I_0 = QK_KB_0,
    SPD_D_0,
    ANG_I_0,
    ANG_D_0,
    INV_0,
    CHMOD_0,
    SPD_I_1,
    SPD_D_1,
    ANG_I_1,
    ANG_D_1,
    INV_1,
    CHMOD_1,
    INV_SCRL,
    AUTO_MOUSE,
    OLED_MOD,
    DPAD_MOD,
    MOD_CUR,
    MOD_SCRL,
    MOD_KEY,
    MOD_SLOW,
};

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record);