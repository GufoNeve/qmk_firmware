// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

 #include QMK_KEYBOARD_H
 #include <stdio.h>

 #include "paw3204.h"
 #include "pointing_device.h"

enum layer_names {
   BASE = 0,
   LOWER,
   UPPER,
   LIGHT = 3,
 };

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [BASE] = LAYOUT(
         LT(LIGHT, KC_ESC),  RCS(KC_TAB),          LCTL(KC_TAB),
         KC_WFWD,            KC_WBAK,     KC_WREF, KC_BTN2,
         RCS(KC_T) ,         LCTL(KC_W),           KC_BTN3,
         KC_BTN1, MO(LOWER),
         KC_WH_U, KC_WH_D
     ),
     [LOWER] = LAYOUT(
         XXXXXXX, KC_MPLY,          KC_MSTP,
         XXXXXXX, KC_MPRV, XXXXXXX, KC_MNXT,
         XXXXXXX, XXXXXXX,          XXXXXXX,
         XXXXXXX, XXXXXXX,
         KC_VOLU, KC_VOLD
     ),
     [LIGHT] = LAYOUT(
         XXXXXXX, RGB_HUD,          RGB_HUI,
         RGB_SPI, RGB_SAD, XXXXXXX, RGB_SAI,
         RGB_SPD, RGB_VAD,          RGB_VAI,
         RGB_MOD, RGB_RMOD,
         XXXXXXX, XXXXXXX
     )
 };

 void matrix_init_user(void) {
     init_paw3204();
 }

keyevent_t encoder1_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 3, .col = 3},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 3, .col = 2},
    .pressed = false
};

 void matrix_scan_user(void) {
     static int  cnt;
     static bool paw_ready;

     report_mouse_t mouse_rep = pointing_device_get_report();

     if (cnt++ % 50 == 0) {
         uint8_t pid = read_pid_paw3204();
         if (pid == 0x30) {
             dprint("paw3204 OK\n");
             paw_ready = true;
         } else {
             dprintf("paw3204 NG:%d\n", pid);
             paw_ready = false;
         }
     }

     if (paw_ready) {
         uint8_t stat;
         int8_t x, y;

         read_paw3204(&stat, &y, &x);

             mouse_rep.x = -y;
             mouse_rep.y = -x;

         if (cnt % 10 == 0) {
             dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
         }

         if (stat & 0x80) {
             pointing_device_set_report(mouse_rep);
         }
     }
     if (encoder1_ccw.pressed){
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (encoder1_cw.pressed){
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }
 }


 bool encoder_update_user(uint8_t index, bool clockwise) {
         if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
         return false;
       }
