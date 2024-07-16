// Copyright 2022 Taro Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

RGB_MATRIX_EFFECT(BACKLIGHT_REACTIVE_SEPARATED)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

# define BACKLIGHT_NUM 6
static bool BACKLIGHT_REACTIVE_SEPARATED(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
  uint8_t i = led_min;
  // BACKLIGHT
  for (; i < BACKLIGHT_NUM; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    uint16_t tick = max_tick;
    for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
        if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
         tick = g_last_hit_tracker.tick[j];
         break;
        }
    }
    uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
    HSV hsv = rgb_matrix_config.hsv;
    hsv.v =  scale8(255 - offset, hsv.v);
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  // UNDERGLOW
  for (; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    HSV hsv = rgb_matrix_config.hsv;
    hsv.h += rgb_matrix_config.speed + (40 * get_highest_layer(layer_state));
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#    endif
#endif
