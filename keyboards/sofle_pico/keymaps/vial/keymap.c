// Copyright 2024 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
        /*
        * QWERTY
        * ,-----------------------------------------.                    ,-----------------------------------------.
        * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
        * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
        * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
        * `-----------------------------------------/       /     \      \-----------------------------------------'
        *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
        *            |      |      |      |      |/       /         \      \ |      |      |      |      |
        *            `----------------------------------'           '------''---------------------------'
        */

        [_QWERTY] = LAYOUT(
        KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_GRV,
        KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,     XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                          KC_LGUI, KC_LALT, KC_LCTL, TL_LOWR, KC_ENT,      KC_SPC , TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
        ),
        /* LOWER
        * ,-----------------------------------------.                    ,-----------------------------------------.
        * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
        * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
        * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
        * `-----------------------------------------/       /     \      \-----------------------------------------'
        *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
        *            |      |      |      |      |/       /         \      \ |      |      |      |      |
        *            `----------------------------------'           '------''---------------------------'
        */
        [_LOWER] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        _______, KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                          _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
        ),
        /* RAISE
        * ,----------------------------------------.                    ,-----------------------------------------.
        * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
        * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
        * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
        * `-----------------------------------------/       /     \      \-----------------------------------------'
        *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
        *            |      |      |      |      |/       /         \      \ |      |      |      |      |
        *            `----------------------------------'           '------''---------------------------'
        */
        [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, KC_INS,  KC_PSCR, KC_APP,  XXXXXXX, XXXXXXX,                          KC_PGUP, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, KC_BSPC,
        _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_CAPS,                          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_BSPC,
        _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                          _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
        ),
        /* ADJUST
        * ,-----------------------------------------.                    ,-----------------------------------------.
        * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * |QK_BOOT|     |      |      |      |      |                    |      |      |      |      |      |      |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
        * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
        * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
        * `-----------------------------------------/       /     \      \-----------------------------------------'
        *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
        *            |      |      |      |      |/       /         \      \ |      |      |      |      |
        *            `----------------------------------'           '------''---------------------------'
        */
        [_ADJUST] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                          _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
        )
    // clang-format on
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
};
#endif

#ifdef OLED_ENABLE
#include "dynamic_keymap.h"

static uint8_t oled_current_mode = 0; // 0 = logo, 1 = typing

static void oled_write_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_VOLD: oled_write_P(PSTR("Vol-"), false); break;
        case KC_VOLU: oled_write_P(PSTR("Vol+"), false); break;
        case KC_PGUP: oled_write_P(PSTR("PgUp"), false); break;
        case KC_PGDN: oled_write_P(PSTR("PgDn"), false); break;
        case KC_MNXT: oled_write_P(PSTR("Next"), false); break;
        case KC_MPRV: oled_write_P(PSTR("Prev"), false); break;
        case KC_MUTE: oled_write_P(PSTR("Mute"), false); break;
        case KC_UP:   oled_write_P(PSTR("Up  "), false); break;
        case KC_DOWN: oled_write_P(PSTR("Down"), false); break;
        case KC_MS_WH_UP: oled_write_P(PSTR("ScrU"), false); break;
        case KC_MS_WH_DOWN: oled_write_P(PSTR("ScrD"), false); break;
        case KC_TAB:  oled_write_P(PSTR("Tab "), false); break;
        case LSFT(KC_TAB): oled_write_P(PSTR("STab"), false); break;
        case KC_TRNS:
        case KC_NO:   oled_write_P(PSTR("None"), false); break;
        default:      oled_write_P(PSTR("??? "), false); break;
    }
}

bool oled_task_user(void) {
    if (last_input_activity_elapsed() < 10000) {
        if (oled_current_mode == 0) {
            oled_clear();
            oled_current_mode = 1;
        }

        // Layer Status
        oled_set_cursor(0, 1);
        oled_write_P(PSTR("Layer:\n"), false);
        switch (get_highest_layer(layer_state)) {
            case _QWERTY: oled_write_P(PSTR("BASE    \n"), false); break;
            case _LOWER:  oled_write_P(PSTR("FUNCTION\n"), false); break;
            case _RAISE:  oled_write_P(PSTR("ACTIONS \n"), false); break;
            case _ADJUST: oled_write_P(PSTR("SYSTEM  \n"), false); break;
            default:      oled_write_P(PSTR("UNKNOWN \n"), false); break;
        }

        // Encoder Status
        oled_set_cursor(0, 6);
        oled_write_P(PSTR("Encoder:\n"), false);

        uint16_t ccw = KC_TRNS;
        uint16_t cw = KC_TRNS;
        uint8_t enc_idx = is_keyboard_left() ? 0 : 1;
        for (int i = 3; i >= 0; i--) {
            if ((layer_state & (1UL << i)) || i == 0) {
                if (ccw == KC_TRNS) ccw = dynamic_keymap_get_encoder(i, enc_idx, false);
                if (cw == KC_TRNS) cw = dynamic_keymap_get_encoder(i, enc_idx, true);
            }
        }

        if (ccw == KC_TRNS && cw == KC_TRNS) {
            oled_write_P(PSTR("None      \n"), false);
        } else {
            oled_write_keycode(ccw);
            oled_write_P(PSTR("/"), false);
            oled_write_keycode(cw);
            oled_write_P(PSTR(" \n"), false); // space padding to 10 chars
        }

        // Modifiers Status
        oled_set_cursor(0, 11);
        oled_write_P(PSTR("Mods:\n"), false);
        uint8_t mods = get_mods();
        char mod_str[11] = "          "; // 10 spaces
        if (mods & MOD_MASK_SHIFT) { mod_str[0]='S'; mod_str[1]='f'; mod_str[2]='t'; }
        if (mods & MOD_MASK_CTRL)  { mod_str[4]='C'; mod_str[5]='t'; mod_str[6]='l'; }

        char mod_str2[11] = "          "; // 10 spaces
        if (mods & MOD_MASK_ALT)   { mod_str2[0]='A'; mod_str2[1]='l'; mod_str2[2]='t'; }
        if (mods & MOD_MASK_GUI)   { mod_str2[4]='G'; mod_str2[5]='u'; mod_str2[6]='i'; }

        oled_write(mod_str, false);
        oled_write_P(PSTR("\n"), false);
        oled_write(mod_str2, false);

        return false;
    } else {
        if (oled_current_mode == 1) {
            oled_clear();
            oled_current_mode = 0;
        }
        return true;
    }
}
#endif
