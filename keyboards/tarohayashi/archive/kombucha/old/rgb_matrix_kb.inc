// Copyright 2022 Taro Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

RGB_MATRIX_EFFECT(SEPARATED)
RGB_MATRIX_EFFECT(BACKLIGHT_REACTIVE)
RGB_MATRIX_EFFECT(BACKLIGHT_REACTIVE_SEPARATED)
RGB_MATRIX_EFFECT(UNDERGLOW_REACTIVE)
RGB_MATRIX_EFFECT(UNDERGLOW_REACTIVE_SEPARATED)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

# define BACKLIGHT_NUM 11

static bool SEPARATED(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  uint8_t i = led_min;
  // BACKLIGHT
  for (; i < BACKLIGHT_NUM; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    HSV hsv = rgb_matrix_config.hsv;
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

static bool BACKLIGHT_REACTIVE(effect_params_t* params) {
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
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

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

static bool UNDERGLOW_REACTIVE(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t i = led_min;
    // BACKLIGHT
    for (; i < BACKLIGHT_NUM; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    // UNDERGLOW
    uint8_t count = g_last_hit_tracker.count;
    for (; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        hsv.v   = 0;
        for (uint8_t j = 0; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            uint16_t effect = tick + dist * 5;
            if (effect > 255) effect = 255;
            hsv.v = qadd8(hsv.v, 255 - effect);
        }
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool UNDERGLOW_REACTIVE_SEPARATED(effect_params_t* params) {
      RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t i = led_min;
    // BACKLIGHT
    for (; i < BACKLIGHT_NUM; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        hsv.h += rgb_matrix_config.speed + (40 * get_highest_layer(layer_state));
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    // UNDERGLOW
    uint8_t count = g_last_hit_tracker.count;
    for (; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        hsv.v   = 0;
        for (uint8_t j = 0; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            uint16_t effect = tick + dist * 5;
            if (effect > 255) effect = 255;
            hsv.v = qadd8(hsv.v, 255 - effect);
        }
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif
#endif
