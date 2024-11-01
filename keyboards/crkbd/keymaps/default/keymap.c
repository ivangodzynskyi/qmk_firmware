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


enum combos {
  UI_LEFT,
  IO_UP,
  COMMDOT_DOWN,
  OP_RIGHT
};

const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM commdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};

combo_t key_combos[] = {
  [UI_LEFT] = COMBO(ui_combo, KC_LEFT),
  [IO_UP] = COMBO(io_combo, KC_UP),
  [COMMDOT_DOWN] = COMBO(commdot_combo, KC_DOWN),
  [OP_RIGHT] = COMBO(op_combo, KC_RIGHT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(

  //,------------------------------------------------------------------------------.          ,----------------------------------------------------------------------------.
       KC_GRV,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,               KC_Y,          KC_U,         KC_I,         KC_O,            KC_P, KC_LBRC,
  //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
       KC_TAB, LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),         KC_G,               KC_H, LGUI_T(KC_J), LALT_T(KC_K), LCTL_T(KC_L), LSFT_T(KC_SCLN), KC_QUOT,
  //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
        MO(3),         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,               KC_N,          KC_M,      KC_COMM,       KC_DOT,         KC_SLSH, KC_BTN2,
  //|--------+-------------+-------------+-------------+-------------+-------------|          |--------+--------------+-------------+-------------+----------------+--------|
                                                KC_BTN1, LT(1,KC_SPC),LT(2, KC_ENT),           XXXXXXX,       KC_BSPC,       KC_ESC
                                            //`------------------------------------'         `-------------------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, KC_LEFT,   KC_UP, KC_DOWN,KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  KC_SPC, _______,    XXXXXXX, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
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

// Modify these alues to adjust the scrolling speed
#define SCROLL_DIVISOR_H 5.0
#define SCROLL_DIVISOR_V 5.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Modify these to adjust non-linear mouse scaling
#define MAX_SCALE 32
#define MIN_SCALE 1
#define GROWTH_FACTOR 64
#define MOMENTUM 0.01

// Variable to store an exponential moving average scaling factor to denoise the non-linear scaling
float accumulated_factor = MIN_SCALE;

// Arrow keys slight slowing
#define ARROW_STEP_X 15
#define ARROW_STEP_Y 10
int accumulated_arrow_x = 0;
int accumulated_arrow_y = 0;

float average_arrow_x = 0;
float average_arrow_y = 0;

#define ARROW_MOMENTUM 0.8
#define Y_TO_X_RATE 5

// Alt-Tab parameteres
#define ALT_TAB_STEP 8
int accumulated_alt_tab = 0;
int pressed_command = 0;

// add non-linear scaling to all mouse movements
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    
    // arrow key emulation
    if (layer_state_is(1)) {
        // move one space per click here, biasing towards vertical
        // if you are moving in text horizontally and click an accidental
        // vertical, you can just click back.  If you are moving vertically
        // and send an accidental horizontal, you can't just click back
        // if you are in a line shorter than where you started.  Thus,
        // you should strongly prefer vertical movement to bias against
        // accidental sideways clicks.  Almost all text scrolling is
        // orthogonal, so this helps suppress diagonal motion.  Think of it
        // as if you are in a box, and you move when you hit an edge, 
        // resetting to the center each time.  

        // This version additionally keeps a running average and only allows
        // motion in the direction of the recent average 

        // update the accumulated arrow momentum
        average_arrow_x = average_arrow_x*ARROW_MOMENTUM + (float) mouse_report.x*(1-ARROW_MOMENTUM);
        average_arrow_y = average_arrow_y*ARROW_MOMENTUM + (float) mouse_report.y*(1-ARROW_MOMENTUM);

        // kill accumulated clicks orthogonal to average direction           
        if (Y_TO_X_RATE * fabs(average_arrow_x) > fabs(average_arrow_y)){
            accumulated_arrow_x += mouse_report.x;
            accumulated_arrow_y = 0;
        }
        if (fabs(average_arrow_y) > Y_TO_X_RATE * fabs(average_arrow_x)){
            accumulated_arrow_x = 0;
            accumulated_arrow_y += mouse_report.y;
        }
    
        // process queued clicks
        if (accumulated_arrow_x <= -ARROW_STEP_X){
            tap_code(KC_LEFT);
            accumulated_arrow_x += ARROW_STEP_X;
        }
        if (accumulated_arrow_x >= ARROW_STEP_X) {
            tap_code(KC_RIGHT);
            accumulated_arrow_x -= ARROW_STEP_X;
        }
        if (accumulated_arrow_y <= -ARROW_STEP_Y){
            tap_code(KC_UP);
            accumulated_arrow_y += ARROW_STEP_Y;
        }
        if (accumulated_arrow_y >= ARROW_STEP_Y) {
            tap_code(KC_DOWN);
            accumulated_arrow_y -= ARROW_STEP_Y;
        }
        
        // return a null report
        mouse_report.x = 0;
        mouse_report.y = 0;
        return mouse_report;
    }

    if (layer_state_is(2)) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        // scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        // scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = -(float)mouse_report.x / SCROLL_DIVISOR_H;
        mouse_report.v = (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Update accumulated scroll values by subtracting the integer parts
        // scroll_accumulated_h -= (int16_t)scroll_accumulated_h;
        // scroll_accumulated_v -= (int16_t)scroll_accumulated_v;

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

