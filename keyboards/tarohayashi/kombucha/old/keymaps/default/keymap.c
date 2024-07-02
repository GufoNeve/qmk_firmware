// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

 #include QMK_KEYBOARD_H
 #include <stdio.h>

 #include "paw3204.h"
 #include "pointing_device.h"

 enum custom_keycodes{
   SEND_01 = SAFE_RANGE,
            SEND_02, SEND_03, SEND_04, SEND_05, SEND_06, SEND_07, SEND_08, SEND_09, SEND_10,
   SEND_11, SEND_12
 };

 enum layer_name {
   BASE = 0,
   LOWER,
   UPPER,
   LIGHT,
 };

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [BASE] = LAYOUT(
         SEND_01, SEND_02, SEND_03, SEND_04, SEND_05, SEND_06, SEND_07, SEND_08, SEND_09, SEND_10,
        SEND_11, SEND_12, KC_A, KC_B
     ),
     [LOWER] = LAYOUT(
       XXXXXXX, XXXXXXX,          XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX,          XXXXXXX,
       XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX
     ),
     [UPPER] = LAYOUT(
         XXXXXXX, XXXXXXX,          XXXXXXX,
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         XXXXXXX, XXXXXXX,          XXXXXXX,
         XXXXXXX, XXXXXXX,
         XXXXXXX, XXXXXXX
     ),
     [LIGHT] = LAYOUT(
       XXXXXXX, XXXXXXX,          XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX,          XXXXXXX,
       XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX
     )
 };

 void matrix_init_user(void) {
     init_paw3204();
 }

 keyevent_t encoder1_ccw = {
     .key = (keypos_t){.row = 3, .col = 3},
     .pressed = false
 };
 keyevent_t encoder1_cw = {
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
 }


bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
        return false;
      }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_01: if (record->event.pressed) SEND_STRING("01 "); break;
    case SEND_02: if (record->event.pressed) SEND_STRING("02 "); break;
    case SEND_03: if (record->event.pressed) SEND_STRING("03 "); break;
    case SEND_04: if (record->event.pressed) SEND_STRING("04 "); break;
    case SEND_05: if (record->event.pressed) SEND_STRING("05 "); break;
    case SEND_06: if (record->event.pressed) SEND_STRING("06 "); break;
    case SEND_07: if (record->event.pressed) SEND_STRING("07 "); break;
    case SEND_08: if (record->event.pressed) SEND_STRING("08 "); break;
    case SEND_09: if (record->event.pressed) SEND_STRING("09 "); break;
    case SEND_10: if (record->event.pressed) SEND_STRING("10 "); break;
    case SEND_11: if (record->event.pressed) SEND_STRING("11 "); break;
    case SEND_12: if (record->event.pressed) SEND_STRING("12 "); break;
  }
  return true;
}
