
#include "matrix.h"
#include "split_util.h"  // スプリット用
#include "config.h"
#include "gpio.h"  // RP2040ピン操作
#include "timer.h"  // wait_usのため

// あとは前のコードそのまま

// マトリクスサイズ: 全体で22行11列 (左11行 + 右11行)
#define MATRIX_ROWS 22
#define MATRIX_COLS 11

// ピン配列 (keyboard.jsonから、重複を共有)
static const pin_t matrix_pins[MATRIX_COLS] = {GP2, GP29, GP3, GP28, GP4, GP27, GP5, GP26, GP6, GP15, GP7};  // cols/rows兼用、11ピン

// 左右判定ピン (config.hから)
static const pin_t hand_pins[2] = {GP26, GP5};  // SPLIT_HAND_MATRIX_GRID

// 初期化
void matrix_init_custom(void) {
    // 全てのピンをInput Pulldownに
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputLow(matrix_pins[i]);
    }

    // 左右判定
    bool is_left = (readPin(hand_pins[0]) == 0 && readPin(hand_pins[1]) == 0);  // LOW_IS_LEFT
    set_keyboard_left(is_left);
    if (is_keyboard_master()) {
        // マスター側追加初期化もし必要
    }
}

// スキャン関数
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // 左右共通のスキャンロジック (serialで同期される)
    // 標準部分: Col→Rowスキャン
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        setPinOutput(matrix_pins[col]);
        writePinHigh(matrix_pins[col]);
        wait_us(30);  // デバウンス

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            uint8_t pin_idx = row % MATRIX_COLS;  // ピンインデックス (重複のためmod 11)
            if (pin_idx == col) continue;  // 重複回避

            matrix_row_t last = current_matrix[row];
            matrix_row_t curr = last;

            // Pulldownなので、押下でHigh検知 (回路確認して逆なら==0に)
            if (readPin(matrix_pins[pin_idx]) == 1) {
                curr |= (1 << col);
            } else {
                curr &= ~(1 << col);
            }

            if (last != curr) {
                current_matrix[row] = curr;
                changed = true;
            }
        }

        writePinLow(matrix_pins[col]);
        setPinInputLow(matrix_pins[col]);
    }

    // 倍マトリクス部分: Row→Colスキャン (追加モジュール用、左手R8~R10, 右手R19~R21など仮定)
    // 左手: row 8~10, 右手: row 19~21 (お兄ちゃんのインデックスから調整)
    uint8_t mod_rows[] = {8,9,10,19,20,21};  // 倍マトリクス対象行
    for (uint8_t i = 0; i < 6; i++) {
        uint8_t row = mod_rows[i];
        uint8_t pin_idx = row % MATRIX_COLS;

        setPinOutput(matrix_pins[pin_idx]);
        writePinLow(matrix_pins[pin_idx]);  // RowをLow駆動
        wait_us(30);

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (pin_idx == col) continue;

            matrix_row_t last = current_matrix[row];
            matrix_row_t curr = last;

            if (readPin(matrix_pins[col]) == 0) {  // Low検知で押下 (Pulldown)
                curr |= (1 << col);
            } else {
                curr &= ~(1 << col);
            }

            if (last != curr) {
                current_matrix[row] = curr;
                changed = true;
            }
        }

        writePinHigh(matrix_pins[pin_idx]);  // リセット
        setPinInputLow(matrix_pins[pin_idx]);
    }

    return changed;
}