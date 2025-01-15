/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "action.h"
#include "math.h"
#include QMK_KEYBOARD_H

enum custom_keycodes {
    BSP_ESC = SAFE_RANGE, // Custom keycode for Backspace/Escape
    K11 = KC_E,
    K12 = KC_T,
    K13 = KC_R,
    K14 = KC_I,
    K21 = KC_A,
    K22 = KC_O,
    K23 = KC_N,
    K24 = KC_S
};

enum combos {
  C1113,
  C1112,
  C1114,
  C1221,
  C1321,
  C1322,
  C1421,
  C1123,
  C1223,
  C1422,
  C1423,
  C1124,
  C1224,
  C1324,
  C1122,
  C111213,
  C111214,
  C111314,
  C112213,
  C112223,
  C112324,
  C212324,
  C211213,
  C211214,
  C211314,
  C212223,
  C222324,
  C231112,
  C231114,
};

const uint16_t PROGMEM c1112[] = {K11, K12, COMBO_END};
const uint16_t PROGMEM c1113[] = {K11, K13, COMBO_END};
const uint16_t PROGMEM c1114[] = {K11, K14, COMBO_END};
const uint16_t PROGMEM c1221[] = {K12, K21, COMBO_END};
const uint16_t PROGMEM c1321[] = {K13, K21, COMBO_END};
const uint16_t PROGMEM c1322[] = {K13, K22, COMBO_END};
const uint16_t PROGMEM c1421[] = {K14, K21, COMBO_END};
const uint16_t PROGMEM c1123[] = {K11, K23, COMBO_END};
const uint16_t PROGMEM c1223[] = {K12, K23, COMBO_END};
const uint16_t PROGMEM c1422[] = {K14, K22, COMBO_END};
const uint16_t PROGMEM c1423[] = {K14, K23, COMBO_END};
const uint16_t PROGMEM c1124[] = {K11, K24, COMBO_END};
const uint16_t PROGMEM c1224[] = {K12, K24, COMBO_END};
const uint16_t PROGMEM c1324[] = {K13, K24, COMBO_END};
const uint16_t PROGMEM c1122[] = {K11, K22, COMBO_END};
const uint16_t PROGMEM c111213[] = {K11, K12, K13, COMBO_END};
const uint16_t PROGMEM c111214[] = {K11, K12, K14, COMBO_END};
const uint16_t PROGMEM c111314[] = {K11, K13, K14, COMBO_END};
const uint16_t PROGMEM c112213[] = {K11, K22, K13, COMBO_END};
const uint16_t PROGMEM c112223[] = {K11, K22, K23, COMBO_END};
const uint16_t PROGMEM c112324[] = {K11, K23, K24, COMBO_END};
const uint16_t PROGMEM c212324[] = {K21, K23, K24, COMBO_END};
const uint16_t PROGMEM c211213[] = {K21, K12, K13, COMBO_END};
const uint16_t PROGMEM c211214[] = {K21, K12, K14, COMBO_END};
const uint16_t PROGMEM c211314[] = {K21, K13, K14, COMBO_END};
const uint16_t PROGMEM c212223[] = {K21, K22, K23, COMBO_END};
const uint16_t PROGMEM c222324[] = {K22, K23, K24, COMBO_END};
const uint16_t PROGMEM c231112[] = {K23, K11, K12, COMBO_END};
const uint16_t PROGMEM c231114[] = {K23, K11, K14, COMBO_END};


combo_t key_combos[] = {
  [C1112] = COMBO(c1112, KC_L),
  [C1113] = COMBO(c1113, KC_DOT),
  [C1114] = COMBO(c1114, KC_Z),
  [C1221] = COMBO(c1221, KC_C),
  [C1321] = COMBO(c1321, KC_V),
  [C1322] = COMBO(c1322, KC_SCLN),
  [C1421] = COMBO(c1421, KC_D),
  [C1123] = COMBO(c1123, KC_U),
  [C1223] = COMBO(c1223, KC_P),
  [C1422] = COMBO(c1422, KC_SLSH),
  [C1423] = COMBO(c1423, KC_G),
  [C1124] = COMBO(c1124, KC_M),
  [C1224] = COMBO(c1224, KC_B),
  [C1324] = COMBO(c1324, KC_F),
  [C1122] = COMBO(c1122, KC_COMM),
  [C111213] = COMBO(c111213, KC_Y),
  [C111214] = COMBO(c111214, KC_MINS),
  [C111314] = COMBO(c111314, KC_EQL),
  [C112213] = COMBO(c112213, KC_BSLS),
  [C112223] = COMBO(c112223, KC_QUOT),
  [C112324] = COMBO(c112324, KC_LBRC),
  [C212324] = COMBO(c212324, KC_RBRC),
  [C211213] = COMBO(c211213, KC_X),
  [C211214] = COMBO(c211214, KC_J),
  [C211314] = COMBO(c211314, KC_K),
  [C212223] = COMBO(c212223, KC_W),
  [C222324] = COMBO(c222324, KC_H),
  [C231112] = COMBO(c231112, KC_Q),
  [C231114] = COMBO(c231114, KC_SCLN)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t tap_timer; // Timer to track tap vs hold

    switch (keycode) {
        case BSP_ESC:
            if (record->event.pressed) {
                tap_timer = timer_read(); // Start the timer when pressed
            } else {
                if (timer_elapsed(tap_timer) < TAPPING_TERM) {
                    tap_code(KC_BSPC);  // Send Backspace on tap
                } else {
                    tap_code(KC_ESC);   // Send Escape on hold
                }
            }
            return false;  // Skip further processing for this key
        default:
            return true;   // Process other keycodes normally
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(

  //,------------------------------------------------------------------------------.          ,----------------------------------------------------------------------------.
       KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,               KC_GRV,  OSM(MOD_LGUI), OSM(MOD_LALT),  OSM(MOD_LCTL), OSM(MOD_LSFT), BSP_ESC,
  //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
       KC_TAB, LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),         KC_G,               KC_BTN1,                 K11,           K12,         K13,        K14,  LT(1,KC_TAB),
  //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
        MO(3),         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,               LT(2,KC_BTN3),           K21,           K22,         K23,        K24,       KC_BTN2,
  //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
                                                KC_BTN1, LT(1,KC_SPC),LT(2, KC_ENT),           XXXXXXX,  LT(2, KC_SPC), LT(3,KC_ENT)
                                            //`------------------------------------'         `-------------------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         XXXXXXX,    KC_MINS,    KC_UP,    KC_EQL,    XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      XXXXXXX, KC_LEFT,  KC_DOWN,    KC_RIGHT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_EQL,   KC_7,   KC_8,   KC_9,  XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_DOT,     KC_4,   KC_5,   KC_6, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_0,       KC_1,   KC_2,   KC_3,   KC_PIPE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  KC_SPC, _______,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_F11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F12,   KC_F7,   KC_F8,   KC_F9,  XXXXXXX,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,                      KC_F11,  KC_F4, KC_F5, KC_F6, XXXXXXX,  XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,                      KC_F10, KC_F1, KC_F2, KC_F3, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______,  KC_SPC, _______,    XXXXXXX, _______, _______
                                        //`--------------------------'  `--------------------------'
  )
};


#define SCROLL_STEP_H 10
#define SCROLL_STEP_V 10
#define SCROLL_VALUE 1
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;


// Arrow keys slight slowing
#define ARROW_STEP_X 20
#define ARROW_STEP_Y 20
int accumulated_arrow_x = 0;
int accumulated_arrow_y = 0;

// Arrow keys slight slowing
#define VOLUME_STEP_Y 40
#define BRIGHT_STEP_X 40
int accumulated_volume_y = 0;
int accumulated_bright_x = 0;


// add non-linear scaling to all mouse movements
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    // arrow key emulation
    if (layer_state_is(1)) {
        accumulated_arrow_x += mouse_report.x;
        accumulated_arrow_y += mouse_report.y;

        if (accumulated_arrow_x < -ARROW_STEP_X) {
            tap_code(KC_LEFT);
            accumulated_arrow_x = 0;
            accumulated_arrow_y = 0;
        }
        if (accumulated_arrow_x > ARROW_STEP_X) {
            tap_code(KC_RIGHT);
            accumulated_arrow_x = 0;
            accumulated_arrow_y = 0;
        }
        if (accumulated_arrow_y > ARROW_STEP_Y) {
            tap_code(KC_DOWN);
            accumulated_arrow_x = 0;
            accumulated_arrow_y = 0;
        }
        if (accumulated_arrow_y < -ARROW_STEP_Y) {
            tap_code(KC_UP);
            accumulated_arrow_x = 0;
            accumulated_arrow_y = 0;
        }

        // return a null report
        mouse_report.x = 0;
        mouse_report.y = 0;
        return mouse_report;
    }

    // volume and brightness
    if (layer_state_is(3)) {
        accumulated_bright_x += mouse_report.x;
        accumulated_volume_y += mouse_report.y;

        if (accumulated_bright_x < -BRIGHT_STEP_X) {
            tap_code(KC_BRID);
            accumulated_bright_x = 0;
            accumulated_volume_y = 0;
        }
        if (accumulated_bright_x > BRIGHT_STEP_X) {
            tap_code(KC_BRIU);
            accumulated_bright_x = 0;
            accumulated_volume_y = 0;
        }
        if (accumulated_volume_y > VOLUME_STEP_Y) {
            tap_code(KC_VOLD);
            accumulated_bright_x = 0;
            accumulated_volume_y = 0;
        }
        if (accumulated_volume_y < -VOLUME_STEP_Y) {
            tap_code(KC_VOLU);
            accumulated_bright_x = 0;
            accumulated_volume_y = 0;
        }

        // return a null report
        mouse_report.x = 0;
        mouse_report.y = 0;
        return mouse_report;
    }

    if (layer_state_is(2)) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
         scroll_accumulated_h += (float)mouse_report.x;
         scroll_accumulated_v += (float)mouse_report.y;


        if (fabs(scroll_accumulated_v) >= SCROLL_STEP_V) {
            if (scroll_accumulated_v > 0) {
             mouse_report.v = (float)SCROLL_VALUE;
            } else {
             mouse_report.v = -(float)SCROLL_VALUE;
            }
            scroll_accumulated_v = 0;
            scroll_accumulated_h = 0;
        }
        if (fabs(scroll_accumulated_h) >= SCROLL_STEP_H) {
            if (scroll_accumulated_h > 0) {
                mouse_report.h = -(float)SCROLL_VALUE;
            } else {
                mouse_report.h = (float)SCROLL_VALUE;
            }
            scroll_accumulated_h = 0;
            scroll_accumulated_v = 0;

        }

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    if (get_mods() & MOD_MASK_SHIFT) {
        mouse_report.x *= 3;
        mouse_report.y *= 3;
    }
    return mouse_report;
}

