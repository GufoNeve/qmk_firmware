// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM layer0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLACK}, {1, 1, HSV_ORANGE}, {2, 8, HSV_BLACK} 
);
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_ORANGE}, {1, 9, HSV_BLACK}             
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_BLACK}, {7, 1, HSV_ORANGE}, {8, 2, HSV_BLACK}         
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_BLACK}, {4, 1, HSV_ORANGE}, {5, 5, HSV_BLACK}
);
const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_BLACK}, {6, 1, HSV_ORANGE}, {7, 3, HSV_BLACK}
);
const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_BLACK}, {8, 1, HSV_ORANGE}, {9, 1, HSV_BLACK}
);
const rgblight_segment_t PROGMEM layer6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 9, HSV_BLACK}, {9, 1, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM layer7[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_BLACK}, {2, 1, HSV_ORANGE}, {3, 7, HSV_BLACK}
);
const rgblight_segment_t PROGMEM layer8[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_BLACK}, {5, 1, HSV_ORANGE}, {6, 4, HSV_BLACK}
);
const rgblight_segment_t PROGMEM layer9[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_BLACK}, {3, 1, HSV_ORANGE}, {4, 6, HSV_BLACK}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0,
    layer1,
    layer2,
    layer3,
    layer4,
    layer5,
    layer6,
    layer7,
    layer8,
    layer9
);

// 初期化時にRGBレイヤーを設定
void keyboard_post_init_user(void) {
    rgblight_enable();  // RGBライトを有効化
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);  // モードを固定
    rgblight_layers = my_rgb_layers;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 1, 2, 3);
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));
    rgblight_set_layer_state(8, layer_state_cmp(state, 8));
    rgblight_set_layer_state(9, layer_state_cmp(state, 9));
    return state;
}
#endif // RGBLIGHT_LAYERS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [0] = LAYOUT_ortho_1x1(
        TG(1)
    ),
    [1] = LAYOUT_ortho_1x1(
        TG(2)
    ),
    [2] = LAYOUT_ortho_1x1(
        TG(3)
    ),
    [3] = LAYOUT_ortho_1x1(
        TG(4)
    ),
    [4] = LAYOUT_ortho_1x1(
        TG(5)
    ),
    [5] = LAYOUT_ortho_1x1(
        TG(6)
    ),
    [6] = LAYOUT_ortho_1x1(
        TG(7)
    ),
    [7] = LAYOUT_ortho_1x1(
        TG(8)
    ),
    [8] = LAYOUT_ortho_1x1(
        TG(9)
    ),
    [9] = LAYOUT_ortho_1x1(
        TG(0)
    )
};

