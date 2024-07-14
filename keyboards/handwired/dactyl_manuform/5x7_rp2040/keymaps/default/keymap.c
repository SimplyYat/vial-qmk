// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ = │                     │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
     * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E │ R │ T │ = │                     │ Y │ Y │ U │ I │ O │ P │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ A │ S │ D │ F │ G │ B │                     │ / │ H │ J │ K │ L │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ V │                     │ N │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┴───┴───┘ ┌───┬───┐ ┌───┬───┐ └───┴───┴───┼───┼───┼───┼───┤
     * │Ctl│F4 │F5 │GUI│             │ C │ V │ │Alt│ A │             │ ← │ ↓ │ ↑ │ → │
     * └───┴───┴───┴───┘             ├───┼───┤ ├───┼───┤             └───┴───┴───┴───┘
     *                               │Bks│PgU│ │PgD│Ent│
     *                               ├───┼───┤ ├───┼───┤
     *                               │Alt│Del│ │Ctl│Spc│
     *                               └───┴───┘ └───┴───┘
     */
    [0] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_EQL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_EQL,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_B,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_V,
        KC_LCTL, KC_F4,   KC_F5,   KC_LGUI,
                                                     KC_C,    KC_V,
                                                     KC_BSPC, KC_PGUP,
                                                     KC_LALT, KC_DEL,

        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_Y,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSLS, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_N,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_RALT, KC_A,
        KC_PGDN, KC_ENT,
        KC_RCTL, KC_SPC
    )
};
