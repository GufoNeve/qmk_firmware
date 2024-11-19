#pragma once

#define PMW33XX_CS_PIN B6 // SPI CS pin.
#define SPI_SCK_PIN B1
#define SPI_MISO_PIN B3
#define SPI_MOSI_PIN B2

/* Optional. */
#define PMW33XX_CPI 800      // The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
#define PMW33XX_CLOCK_SPEED 2000000 // Sets the clock speed that the sensor runs at. Defaults to 2000000
#define MOUSE_EXTENDED_REPORT // Use -32767 to 32767, instead of just -127 to 127.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 10

/* key matrix size */
#define MATRIX_COLS 4
#define MATRIX_ROWS 4

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define MATRIX_IO_DELAY 20

#ifdef RGB_MATRIX_ENABLE
#define DRIVER_LED_TOTAL 18
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