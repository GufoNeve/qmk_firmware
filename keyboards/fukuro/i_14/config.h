#pragma once

/* key matrix size */
#define MATRIX_COLS 8
#define MATRIX_ROWS 16

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define MATRIX_IO_DELAY 20

#ifdef RGB_MATRIX_ENABLE
#define DRIVER_LED_TOTAL 128
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 64 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_DEFAULT_HUE 125 // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL 64 // Sets the default brightness value, if none has been set

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 32
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16

#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP// Sets the default mode, if none has been set
#endif