 /* Copyright 2022 Tetsup
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include <stdio.h>

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define OVR_TGL KEY_OVERRIDE_TOGGLE
#define JOY_MD TOGGLE_JOYSTICK_MODE
#define JOY_DIV TOGGLE_JOYMOUSE_DIVISION
#define JOY_CAL CALIBRATE_JOYSTICK
#define OLED_LG TOGGLE_OLED_LOG

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum my_keycodes {
  TOGGLE_JOYSTICK_MODE = SAFE_RANGE,
  TOGGLE_JOYMOUSE_DIVISION,
  CALIBRATE_JOYSTICK,
  TOGGLE_OLED_LOG
};

const key_override_t at_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT);
const key_override_t circ_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC);
const key_override_t ampr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR);
const key_override_t astr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR);
const key_override_t lprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN);
const key_override_t rprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN);
const key_override_t at2_key_override = ko_make_basic(0, KC_AT, JP_AT);
const key_override_t circ2_key_override = ko_make_basic(0, KC_CIRC, JP_CIRC);
const key_override_t ampr2_key_override = ko_make_basic(0, KC_AMPR, JP_AMPR);
const key_override_t astr2_key_override = ko_make_basic(0, KC_ASTR, JP_ASTR);
const key_override_t lprn2_key_override = ko_make_basic(0, KC_LPRN, JP_LPRN);
const key_override_t rprn2_key_override = ko_make_basic(0, KC_RPRN, JP_RPRN);
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, JP_UNDS);
const key_override_t eql_key_override = ko_make_with_layers_and_negmods(0, KC_EQL, JP_EQL, ~0, (uint8_t) MOD_MASK_SHIFT);
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, JP_PLUS);
const key_override_t lbrc_key_override = ko_make_with_layers_and_negmods(0, KC_LBRC, JP_LBRC, ~0, (uint8_t) MOD_MASK_SHIFT);
const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, JP_LCBR);
const key_override_t rbrc_key_override = ko_make_with_layers_and_negmods(0, KC_RBRC, JP_RBRC, ~0, (uint8_t) MOD_MASK_SHIFT);
const key_override_t rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, JP_RCBR);
const key_override_t bsls_key_override = ko_make_with_layers_and_negmods(0, KC_BSLS, JP_BSLS, ~0, (uint8_t) MOD_MASK_SHIFT);
const key_override_t pipe_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE);
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, JP_COLN);
const key_override_t quot_key_override = ko_make_with_layers_and_negmods(0, KC_QUOT, JP_QUOT, ~0, (uint8_t) MOD_MASK_SHIFT);
const key_override_t dquo_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO);
const key_override_t grv_key_override = ko_make_with_layers_and_negmods(0, KC_GRV, JP_GRV, ~0, (uint8_t) MOD_MASK_SHIFT);
const key_override_t tild_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_GRV, JP_TILD);
const key_override_t zkhk_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, A(JP_ZKHK));


const key_override_t **key_overrides = (const key_override_t *[]){
    &at_key_override,
    &circ_key_override,
    &ampr_key_override,
    &astr_key_override,
    &lprn_key_override,
    &rprn_key_override,
    &at2_key_override,
    &circ2_key_override,
    &ampr2_key_override,
    &astr2_key_override,
    &lprn2_key_override,
    &rprn2_key_override,
    &unds_key_override,
    &eql_key_override,
    &plus_key_override,
    &lbrc_key_override,
    &lcbr_key_override,
    &rbrc_key_override,
    &rcbr_key_override,
    &bsls_key_override,
    &pipe_key_override,
    &coln_key_override,
    &quot_key_override,
    &dquo_key_override,
    &grv_key_override,
    &tild_key_override,
    &zkhk_key_override,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |--------,    ,------|   N  |   M  |   ,  |   .  |   /  |  =   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Alt  | LGUI |  ZH  | /Space  /       \Enter \  |BackSP|  Del | ESC  |
 *                   |      |      |      |/ Fn1   /         \  Fn2 \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_EQL,
                  KC_LALT, KC_LGUI, A(KC_GRV),  LT(1,KC_SPC),   LT(2,KC_ENT),  KC_BSPC,  KC_DEL,  KC_ESC
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------,    ,------|   |  |   \  |   `  |   [  |   ]  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Alt  | LGUI |  ZH  | /Space  /       \Enter \  |BackSP|  Del | ESC  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______,                     KC_PIPE, KC_BSLS, KC_GRAVE, KC_LBRC, KC_RBRC, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | F11  | F12  |      |      |      |                    | Left | Down |  Up  |Right |MsWhUp| Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------,    ,------| MsLt | MsDn | MsUp | MsRt |MsWhDn| Esc  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Alt  | LGUI |  ZH  | /Space  /       \Enter \  |MsBt1 |MsBt2 |MsBt3 |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_DEL,
  _______, KC_F11,  KC_F12,  _______, _______, _______,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_BSPC,
  _______, _______, _______, _______, _______, _______,                     KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_MS_BTN1, KC_MS_BTN2,
                             _______, _______, _______,  _______, _______, KC_MS_BTN1, KC_MS_BTN2,  KC_MS_BTN3
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |JP/EN |      |      |      |      |      |                    |      |PrtSC |      |      |OLEDLG|LEDTGL|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | Home | PgDN | PgUP | End  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------,    ,------|      |      |      |      |JOYDIV|JOYTGL|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Alt  | LGUI |  ZH  | /Space  /       \Enter \  |MsBt1 |MsBt2 |MsBt3 |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  OVR_TGL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, OLED_LG, RGB_TOG,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, JOY_CAL,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, JOY_DIV, JOY_MD,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x20, 0x20, 0x20, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0x20, 0x52, 0x65, 0x76, 0x2E, 0x31,
        0x20, 0x20, 0x20, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0x00
    };

    oled_write_P(logo, false);
}
char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
//new

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
    case _QWERTY:
        oled_write_ln_P(PSTR("Default"), false);
        break;
    case _RAISE:
        oled_write_ln_P(PSTR("Raise"), false);
        break;
    case _LOWER:
        oled_write_ln_P(PSTR("Lower"), false);
        break;
    case _ADJUST:
        oled_write_ln_P(PSTR("Adjust"), false);
        break;
    default:
      break;
        oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
  #ifdef JOYSTICK_ENABLE
    oled_write_P(PSTR("Joy Mode: "), false);
    char mode_chars[2] = {(char)get_joystick_mode() + 0x30};
    oled_write_ln(mode_chars, false);
  #endif // JOYSTICK_ENABLE
  } else {
      render_logo();
  }
    return false;
}
#endif // OLED_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
#   ifdef JOYSTICK_ENABLE
      case TOGGLE_JOYSTICK_MODE:
        if(record->event.pressed) {
          toggle_joystick_mode();
        }
        break;
      case CALIBRATE_JOYSTICK:
        if(record->event.pressed) {
          reset_joystick_calibrate();
        }
        break;
#   endif // JOYSTICK_ENABLE
  }

  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, 6, 200, 255, 255}, {22, 6, 200, 255, 255},
   {6, 6, 220, 255, 255}, {28, 6, 220, 255, 255},
   {12, 6, 240, 255, 255}, {34, 6, 240, 255, 255},
   {18, 4, 5, 255, 255}, {40, 4, 5, 255, 255}
);
const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 44, HSV_CYAN}
);
const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 44, HSV_GREEN}
);
const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 44, 15, 255, 255}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    qwerty_layer,
    lower_layer,
    raise_layer,
    adjust_layer
);
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
#endif // RGBLIGHT_ENABLE

#ifndef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}
#else
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return state;
}
#endif // RGBLIGHT_ENABLE
