// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

typedef union {
    uint8_t reg[8];
} paw3204_all_reg;

uint8_t read_pid_paw3204(void);
void    init_paw3204(void);
int     read_paw3204(uint8_t *stat, int8_t *x, int8_t *y);
void    read_all_paw3204(paw3204_all_reg *dat);
