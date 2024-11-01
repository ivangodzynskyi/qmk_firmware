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

#include QMK_KEYBOARD_H

#define BW_TAP_TIME 200  //configure max tap time, 200ms here

enum custom_keycodes {
  BW_BSPC_L1 = SAFE_RANGE,
  BW_TAB_L2,
  BW_BSPC_L3,
  BW_TAB_L3,
  BW_DELETE_CMD,
  BW_ENTER_CTL,
  BW_ESC_ALT
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t bspc_l1_timer;
  static uint16_t tab_l2_timer;
  static uint16_t bspc_l3_timer;
  static uint16_t tab_l3_timer;
  static uint16_t delete_cmd_timer;
  static uint16_t enter_ctl_timer;
  static uint16_t esc_alt_timer;
  switch (keycode) {
    // combined backspace and layer 1 key
    case BW_BSPC_L1:
      if (record->event.pressed) {
        bspc_l1_timer = timer_read();
        layer_on(1); 
      } else {
        layer_off(1); 
        if (timer_elapsed(bspc_l1_timer) < BW_TAP_TIME)
          tap_code(KC_BSPC);
      }
      return false;
    // combined tab and layer 2 key
    case BW_TAB_L2:
      if (record->event.pressed) {
        tab_l2_timer = timer_read();
        layer_on(2); 
      } else {
        layer_off(2);
        if (timer_elapsed(tab_l2_timer) < BW_TAP_TIME)
          tap_code(KC_TAB);
      }
      return false;
      // combined backspace and layer 3 key
    case BW_BSPC_L3:
      if (record->event.pressed) {
        bspc_l3_timer = timer_read();
        layer_on(3); 
      } else {
        layer_off(3); 
        if (timer_elapsed(bspc_l3_timer) < BW_TAP_TIME)
          tap_code(KC_BSPC);
      }
      return false;
    // combined tab and layer 3 key
    case BW_TAB_L3:
      if (record->event.pressed) {
        tab_l3_timer = timer_read();
        layer_on(3); 
      } else {
        layer_off(3);
        if (timer_elapsed(tab_l3_timer) < BW_TAP_TIME)
          tap_code(KC_TAB);
      }
      return false;
    // combined delete and command key
    case BW_DELETE_CMD:
      if (record->event.pressed) {
        delete_cmd_timer = timer_read();
        register_code(KC_LGUI); 
      } else {
        unregister_code(KC_LGUI); 
        if (timer_elapsed(delete_cmd_timer) < BW_TAP_TIME)
          tap_code(KC_DEL);
      }
      return false;
    // combined enter and control key
    case BW_ENTER_CTL:
      if (record->event.pressed) {
        enter_ctl_timer = timer_read();
        register_code(KC_LCTL); 
      } else {
        unregister_code(KC_LCTL); 
        if (timer_elapsed(enter_ctl_timer) < BW_TAP_TIME)
          tap_code(KC_ENT);
      }
      return false;
    // combined escape and alt key
    case BW_ESC_ALT:
      if (record->event.pressed) {
        esc_alt_timer = timer_read();
        register_code(KC_RALT); 
      } else {
        unregister_code(KC_RALT); 
        if (timer_elapsed(esc_alt_timer) < BW_TAP_TIME)
          tap_code(KC_ESC);
      }
      return false; 
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            BW_DELETE_CMD, BW_BSPC_L1, BW_ENTER_CTL,    XXXXXXX, BW_TAB_L2, BW_ESC_ALT
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN,KC_RIGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     XXXXXXX,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     XXXXXXX, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     XXXXXXX, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
