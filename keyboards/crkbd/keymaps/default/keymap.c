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
//#include "print.h"
#include QMK_KEYBOARD_H


enum combos {
  MOUSE_COMBO,
  MOUSE_COMBO3,
  ENTER_COMBO,
  SCRDN_COMBO,
  SCRUP_COMBO
};

const uint16_t PROGMEM mouse_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM mouse_combo3[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_O, KC_I, COMBO_END};
const uint16_t PROGMEM scrdn_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM scrup_combo[] = {KC_E, KC_R, COMBO_END};

combo_t key_combos[] = {
  [MOUSE_COMBO] = COMBO(mouse_combo, KC_BTN1),
  [MOUSE_COMBO3] = COMBO(mouse_combo3, KC_BTN3),
  [ENTER_COMBO] = COMBO(enter_combo, KC_ENT),
  [SCRDN_COMBO] = COMBO(scrdn_combo, KC_WH_D),
  [SCRUP_COMBO] = COMBO(scrup_combo, KC_WH_U)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
      //,------------------------------------------------------------------------------.          ,----------------------------------------------------------------------------.
           KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,               KC_Y,          KC_U,         KC_I,         KC_O,            KC_P, KC_LBRC,
      //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
           KC_TAB, LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),         KC_G,               KC_H,  LGUI_T(KC_J), LALT_T(KC_K), LCTL_T(KC_L), LSFT_T(KC_SCLN), KC_QUOT,
      //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
     LT(4,KC_ENT),         KC_Z,         KC_X,         KC_C,   LT(2,KC_V),         KC_B,               KC_N,    LT(2,KC_M),LT(3,KC_COMM),       KC_DOT,         KC_SLSH, KC_BTN2,
      //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
                                                    KC_BTN1,LT(1,KC_BSPC),LT(2, KC_ESC),            XXXXXXX,  LT(1,KC_SPC), KC_BTN3
  ),

    [1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RBRC,
      //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          _______, _______, _______, _______, _______, _______,                       KC_EQL,    KC_4,    KC_5,    KC_6, KC_PLUS, KC_BSLS,
      //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,    KC_1,    KC_2,    KC_3, KC_PIPE, XXXXXXX,
      //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______, _______,    _______,    KC_0, KC_PDOT

  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F12,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  KC_SPC, _______,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, XXXXXXX,                      XXXXXXX, KC_LEFT, XXXXXXX,   KC_UP,KC_RIGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, _______, KC_DOWN, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
    [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    XXXXXXX, _______, _______
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
//    if (mouse_report.x != 0 || mouse_report.y != 0) {
//        uprintf("Mouse report: x: %d, y: %d\n", mouse_report.x, mouse_report.y);
//    }
    float x = mouse_report.x;
    float y = mouse_report.y;

//    float cos30 = 0.9659258;
//    float sin30 = -0.2588190;

//    mouse_report.x = (int8_t)(x * cos30 + y * sin30);
//    mouse_report.y = (int8_t)(-x * sin30 + y * cos30);

    mouse_report.x = y;
    mouse_report.y = -x;


    // arrow key emulation
    if (layer_state_is(3)) {
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
    if (layer_state_is(4)) {
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

