#pragma once

#define VENDOR_ID 0x1d50
#define PRODUCT_ID 0x9190
#define DEVICE_VER 0x0001
#define MANUFACTURER tetsup
#define PRODUCT JK44
#define RAW_USAGE_PAGE 0xFF80
#define RAW_USAGE_ID 0x68

#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define MATRIX_ROW_PINS { B2, B6, B3, B1 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define SOFT_SERIAL_PIN D2
#define SPLIT_HAND_PIN F4

#define DEBOUNCE 5

#define TAPPING_TERM 180
#define HOLD_ON_OTHER_KEY_PRESS

#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN D3
    #define RGBLED_NUM 44    // Number of LEDs
    #define RGBLED_SPLIT {22, 22}
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif // RGBLIGHT_ENABLE

#ifdef OLED_ENABLE
    #define OLED_FONT_H "keyboards/jk44/lib/glcdfont.c"
#endif

#ifdef JOYSTICK_ENABLE
//    #define SPLIT_JOYSTICK_ENABLE //暫定停止
    // Max 6: X, Y, Z, Rx, Ry, Rz
    #ifdef SPLIT_JOYSTICK_ENABLE
//        #define SERIAL_USE_MULTI_TRANSACTION
        #define SPLIT_TRANSACTION_IDS_KB GET_JOYSTICK_DATA
        #define JOYSTICK_AXES_COUNT 4
        #define JOYSTICK_BUTTON_COUNT 2
    #else
        #define JOYSTICK_AXES_COUNT 2
        #define JOYSTICK_BUTTON_COUNT 1
    #endif
    #define ANALOG_JOYSTICK_X_AXIS_PIN F6
    #define ANALOG_JOYSTICK_Y_AXIS_PIN F7
    #define ANALOG_JOYSTICK_CLICK_PIN F5
    #define ANALOG_JOYSTICK_AXIS_MIN 256
    #define ANALOG_JOYSTICK_AXIS_MAX 768
    #define ANALOG_JOYSTICK_READ_INTERVAL 30
    #define ANALOG_JOYSTICK_SPEED_REGULATOR 10
    #define ANALOG_JOYSTICK_SPEED_MAX 6
    #define POINTING_DEVICE_ROTATION_180
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
// Max 32
