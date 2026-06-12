// Copyright 2024 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "dynamic_keymap.h"
#include "caps_word.h"

#ifdef SPLIT_KEYBOARD
#include "transactions.h"

typedef struct {
    bool caps_word_on;
    uint16_t ccw_encoder;
    uint16_t cw_encoder;
    uint8_t led_colors[19];
} user_sync_state_t;

user_sync_state_t user_state = {
    .caps_word_on = false,
    .ccw_encoder = KC_TRNS,
    .cw_encoder = KC_TRNS,
    .led_colors = {0}
};
#endif

// Constant color values (change these to customize the lighting)
#define COLOR_ALPHABET_NORMAL (rgb_t){0, 140, 255}   // Light blue
#define COLOR_ALPHABET_CAPS   (rgb_t){255, 50, 0}    // Orange
#define COLOR_MODIFIER        (rgb_t){127, 0, 255}   // Violet
#define COLOR_HOLD_TAP        (rgb_t){255, 0, 127}   // Pink
#define COLOR_TAP_DANCE       (rgb_t){255, 0, 255}   // Magenta
#define COLOR_SYMBOL          (rgb_t){191, 0, 255}   // Purple
#define COLOR_NUMBER          (rgb_t){0, 255, 0}     // Green
#define COLOR_DELETE          (rgb_t){255, 0, 0}     // Red (delete/backspace)
#define COLOR_ENTER           (rgb_t){255, 90, 0}    // Gold (enter)
#define COLOR_LAYER           (rgb_t){75, 0, 130}    // Indigo/Deep Violet
#define COLOR_OTHER           (rgb_t){200, 160, 255} // Lavender
#define COLOR_ARROW           (rgb_t){255, 255, 255} // Pure White (arrow keys, space, tab)

bool is_caps_active(void) {
    bool caps_word_on = false;
#ifdef SPLIT_KEYBOARD
    caps_word_on = is_keyboard_master() ? is_caps_word_on() : user_state.caps_word_on;
#else
    caps_word_on = is_caps_word_on();
#endif
    return host_keyboard_led_state().caps_lock || caps_word_on;
}

uint16_t get_tap_keycode_for_hold_tap(uint16_t keycode) {
    if (IS_QK_LAYER_TAP(keycode)) {
        return QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }
    if (IS_QK_MOD_TAP(keycode)) {
        return QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }
    return KC_NO;
}

uint8_t get_hold_tap_color_index(uint16_t keycode, bool caps_active) {
    uint16_t tap_kc = get_tap_keycode_for_hold_tap(keycode);
    if (tap_kc != KC_NO) {
        uint16_t base = tap_kc;
        if (IS_QK_MODS(tap_kc)) {
            base = QK_MODS_GET_BASIC_KEYCODE(tap_kc);
        }
        if (base >= KC_A && base <= KC_Z) {
            return caps_active ? 13 : 12; // Hold-tap + Alphabet Caps vs Alphabet Normal
        }
        if ((base >= KC_1 && base <= KC_0) || (base >= KC_KP_1 && base <= KC_KP_0)) {
            return 14; // Hold-tap + Number
        }
        if ((base >= KC_MINUS && base <= KC_SLASH) || base == KC_NONUS_HASH || base == KC_GRAVE) {
            return 15; // Hold-tap + Symbol
        }
        if (base == KC_LEFT || base == KC_DOWN || base == KC_UP || base == KC_RGHT || base == KC_SPC || base == KC_TAB) {
            return 21; // Hold-tap + Arrow/Space/Tab
        }
        if (IS_QK_MODS(tap_kc) && (QK_MODS_GET_MODS(tap_kc) & MOD_MASK_SHIFT)) {
            uint16_t basic = QK_MODS_GET_BASIC_KEYCODE(tap_kc);
            if ((basic >= KC_1 && basic <= KC_0) || (basic >= KC_MINUS && basic <= KC_SLASH) || basic == KC_NONUS_HASH || basic == KC_GRAVE) {
                return 15; // Hold-tap + Symbol
            }
        }
    }
    return 4; // Default Hold-tap color (Pink)
}

uint8_t get_tap_dance_color_index(uint16_t keycode, bool caps_active) {
#ifdef VIAL_TAP_DANCE_ENABLE
    uint8_t index = QK_TAP_DANCE_GET_INDEX(keycode);
    vial_tap_dance_entry_t entry;
    if (dynamic_keymap_get_tap_dance(index, &entry)) {
        uint16_t tap_kc = entry.on_tap;
        if (tap_kc != KC_NO && tap_kc != KC_TRNS) {
            uint16_t base = tap_kc;
            if (IS_QK_MODS(tap_kc)) {
                base = QK_MODS_GET_BASIC_KEYCODE(tap_kc);
            }
            if (base >= KC_A && base <= KC_Z) {
                return caps_active ? 17 : 16; // Tap-dance + Alphabet Caps vs Alphabet Normal
            }
            if ((base >= KC_1 && base <= KC_0) || (base >= KC_KP_1 && base <= KC_KP_0)) {
                return 18; // Tap-dance + Number
            }
            if ((base >= KC_MINUS && base <= KC_SLASH) || base == KC_NONUS_HASH || base == KC_GRAVE) {
                return 19; // Tap-dance + Symbol
            }
            if (base == KC_LEFT || base == KC_DOWN || base == KC_UP || base == KC_RGHT || base == KC_SPC || base == KC_TAB) {
                return 22; // Tap-dance + Arrow/Space/Tab
            }
            if (IS_QK_MODS(tap_kc) && (QK_MODS_GET_MODS(tap_kc) & MOD_MASK_SHIFT)) {
                uint16_t basic = QK_MODS_GET_BASIC_KEYCODE(tap_kc);
                if ((basic >= KC_1 && basic <= KC_0) || (basic >= KC_MINUS && basic <= KC_SLASH) || basic == KC_NONUS_HASH || basic == KC_GRAVE) {
                    return 19; // Tap-dance + Symbol
                }
            }
        }
    }
#endif
    return 5; // Default Tap-dance color (Magenta)
}

uint8_t get_color_index(uint16_t keycode, bool caps_active, bool is_base_layer) {
    if (!is_base_layer && (keycode == KC_TRNS || keycode == KC_NO)) {
        return 0; // Off
    }
    if (keycode == KC_TRNS || keycode == KC_NO) {
        return 11; // Other
    }
    if (IS_QK_TAP_DANCE(keycode)) {
        return get_tap_dance_color_index(keycode, caps_active);
    }
    if (IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode)) {
        return get_hold_tap_color_index(keycode, caps_active);
    }
    if (IS_QK_TO(keycode) || IS_QK_MOMENTARY(keycode) || IS_QK_DEF_LAYER(keycode) ||
        IS_QK_TOGGLE_LAYER(keycode) || IS_QK_ONE_SHOT_LAYER(keycode) ||
        IS_QK_LAYER_TAP_TOGGLE(keycode) || IS_QK_PERSISTENT_DEF_LAYER(keycode)) {
        return 10; // Layer
    }
    if (IS_QK_ONE_SHOT_MOD(keycode)) {
        return 3; // Modifier
    }

    uint16_t base = keycode;
    if (IS_QK_MODS(keycode)) {
        base = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }

    if (base >= KC_LCTL && base <= KC_RGUI) {
        return 3; // Modifier
    }
    if (base == KC_LEFT || base == KC_DOWN || base == KC_UP || base == KC_RGHT || base == KC_SPC || base == KC_TAB) {
        return 20; // Arrow keys / Space / Tab
    }
    if (base == KC_BSPC || base == KC_DEL) {
        return 8; // Delete/Backspace
    }
    if (base == KC_ENT || base == KC_KP_ENTER) {
        return 9; // Enter
    }
    if ((base >= KC_1 && base <= KC_0) || (base >= KC_KP_1 && base <= KC_KP_0)) {
        return 7; // Number
    }
    if (base >= KC_A && base <= KC_Z) {
        return caps_active ? 2 : 1; // Caps alphabet vs normal alphabet
    }
    if ((base >= KC_MINUS && base <= KC_SLASH) || base == KC_NONUS_HASH || base == KC_GRAVE) {
        return 6; // Symbol
    }
    if (IS_QK_MODS(keycode) && (QK_MODS_GET_MODS(keycode) & MOD_MASK_SHIFT)) {
        uint16_t basic = QK_MODS_GET_BASIC_KEYCODE(keycode);
        if ((basic >= KC_1 && basic <= KC_0) || (basic >= KC_MINUS && basic <= KC_SLASH) || basic == KC_NONUS_HASH || basic == KC_GRAVE) {
            return 6; // Symbol
        }
    }
    return 11; // Other
}

rgb_t get_color_from_index(uint8_t color_idx) {
    switch (color_idx) {
        case 1:  return COLOR_ALPHABET_NORMAL;
        case 2:  return COLOR_ALPHABET_CAPS;
        case 3:  return COLOR_MODIFIER;
        case 4:  return COLOR_HOLD_TAP;
        case 5:  return COLOR_TAP_DANCE;
        case 6:  return COLOR_SYMBOL;
        case 7:  return COLOR_NUMBER;
        case 8:  return COLOR_DELETE;
        case 9:  return COLOR_ENTER;
        case 10: return COLOR_LAYER;
        case 11: return COLOR_OTHER;
        case 12: {
            rgb_t base = COLOR_ALPHABET_NORMAL;
            rgb_t effect = COLOR_HOLD_TAP;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 13: {
            rgb_t base = COLOR_ALPHABET_CAPS;
            rgb_t effect = COLOR_HOLD_TAP;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 14: {
            rgb_t base = COLOR_NUMBER;
            rgb_t effect = COLOR_HOLD_TAP;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 15: {
            rgb_t base = COLOR_SYMBOL;
            rgb_t effect = COLOR_HOLD_TAP;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 16: {
            rgb_t base = COLOR_ALPHABET_NORMAL;
            rgb_t effect = COLOR_TAP_DANCE;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 17: {
            rgb_t base = COLOR_ALPHABET_CAPS;
            rgb_t effect = COLOR_TAP_DANCE;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 18: {
            rgb_t base = COLOR_NUMBER;
            rgb_t effect = COLOR_TAP_DANCE;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 19: {
            rgb_t base = COLOR_SYMBOL;
            rgb_t effect = COLOR_TAP_DANCE;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 20: return COLOR_ARROW;
        case 21: {
            rgb_t base = COLOR_ARROW;
            rgb_t effect = COLOR_HOLD_TAP;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        case 22: {
            rgb_t base = COLOR_ARROW;
            rgb_t effect = COLOR_TAP_DANCE;
            return (rgb_t){(3 * base.r + effect.r) / 4, (3 * base.g + effect.g) / 4, (3 * base.b + effect.b) / 4};
        }
        default: return (rgb_t){0, 0, 0};
    }
}

rgb_t get_keycode_color(uint16_t keycode, bool caps_active, bool is_base_layer) {
    return get_color_from_index(get_color_index(keycode, caps_active, is_base_layer));
}

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

#ifdef SPLIT_KEYBOARD
void user_sync_callback(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_sync_state_t)) {
        memcpy(&user_state, initiator2target_buffer, sizeof(user_sync_state_t));
    }
}

void keyboard_post_init_user(void) {
    if (!is_keyboard_master()) {
        transaction_register_rpc(USER_SYNC_STATE, user_sync_callback);
    }
}

uint8_t get_slave_led_index(uint8_t i) {
    if (is_keyboard_left()) {
        return i + 29;
    } else {
        return i;
    }
}

void pack_color_5bit(uint8_t *arr, uint8_t led_idx, uint8_t val) {
    uint16_t bit_offset = (uint16_t)led_idx * 5;
    uint8_t byte_idx = bit_offset / 8;
    uint8_t bit_idx = bit_offset % 8;

    uint16_t mask = ~(0x1F << bit_idx);
    arr[byte_idx] &= (mask & 0xFF);
    if (bit_idx > 3) {
        arr[byte_idx + 1] &= ((mask >> 8) & 0xFF);
    }

    arr[byte_idx] |= ((val & 0x1F) << bit_idx);
    if (bit_idx > 3) {
        arr[byte_idx + 1] |= ((val & 0x1F) >> (8 - bit_idx));
    }
}

uint8_t unpack_color_5bit(const uint8_t *arr, uint8_t led_idx) {
    uint16_t bit_offset = (uint16_t)led_idx * 5;
    uint8_t byte_idx = bit_offset / 8;
    uint8_t bit_idx = bit_offset % 8;

    uint16_t val = arr[byte_idx];
    if (bit_idx > 3) {
        val |= ((uint16_t)arr[byte_idx + 1] << 8);
    }
    return (val >> bit_idx) & 0x1F;
}

void calculate_slave_led_colors(uint8_t *arr, bool caps_active) {
    uint8_t layer = get_highest_layer(layer_state);
    bool is_base = (layer == 0);
    memset(arr, 0, 19);

    uint8_t slave_min = is_keyboard_left() ? 29 : 0;
    uint8_t slave_max = is_keyboard_left() ? 58 : 29;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= slave_min && index < slave_max) {
                uint8_t i = index - slave_min;
                uint16_t keycode = dynamic_keymap_get_keycode(layer, row, col);
                uint8_t color_idx = get_color_index(keycode, caps_active, is_base);

                pack_color_5bit(arr, i, color_idx);
            }
        }
    }
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        user_sync_state_t new_state;
        new_state.caps_word_on = is_caps_word_on();

        uint16_t ccw = KC_TRNS;
        uint16_t cw = KC_TRNS;
        uint8_t slave_enc_idx = is_keyboard_left() ? 1 : 0;

        for (int i = 3; i >= 0; i--) {
            if ((layer_state & (1UL << i)) || i == 0) {
                if (ccw == KC_TRNS) ccw = dynamic_keymap_get_encoder(i, slave_enc_idx, false);
                if (cw == KC_TRNS) cw = dynamic_keymap_get_encoder(i, slave_enc_idx, true);
            }
        }
        new_state.ccw_encoder = ccw;
        new_state.cw_encoder = cw;
        calculate_slave_led_colors(new_state.led_colors, is_caps_active());

        static user_sync_state_t last_user_state = {0};
        if (memcmp(&new_state, &last_user_state, sizeof(user_sync_state_t)) != 0) {
            if (transaction_rpc_send(USER_SYNC_STATE, sizeof(user_sync_state_t), &new_state)) {
                last_user_state = new_state;
            }
        }
    }
}
#endif

#ifdef OLED_ENABLE

static uint8_t oled_current_mode = 0; // 0 = logo, 1 = typing
static bool oled_was_on = false;
static uint32_t wake_timer = 0;

static void oled_write_key(uint8_t key) {
    if (key >= KC_A && key <= KC_Z) {
        char str[2] = {(char)('A' + (key - KC_A)), '\0'};
        oled_write(str, false);
    } else if (key >= KC_1 && key <= KC_0) {
        char str[2] = {(char)((key == KC_0) ? '0' : '1' + (key - KC_1)), '\0'};
        oled_write(str, false);
    } else {
        switch(key) {
            case KC_LBRC: oled_write_P(PSTR("["), false); break;
            case KC_RBRC: oled_write_P(PSTR("]"), false); break;
            case KC_MINS: oled_write_P(PSTR("-"), false); break;
            case KC_EQL:  oled_write_P(PSTR("="), false); break;
            case KC_COMM: oled_write_P(PSTR(","), false); break;
            case KC_DOT:  oled_write_P(PSTR("."), false); break;
            case KC_SLSH: oled_write_P(PSTR("/"), false); break;
            case KC_SCLN: oled_write_P(PSTR(";"), false); break;
            case KC_QUOT: oled_write_P(PSTR("'"), false); break;
            case KC_BSLS: oled_write_P(PSTR("\\"), false); break;
            case KC_LEFT: oled_write_P(PSTR("<"), false); break;
            case KC_RIGHT:oled_write_P(PSTR(">"), false); break;
            case KC_UP:   oled_write_P(PSTR("^"), false); break;
            case KC_DOWN: oled_write_P(PSTR("v"), false); break;
            case KC_TAB:  oled_write_P(PSTR("Tb"), false); break;
            case KC_SPC:  oled_write_P(PSTR("_"), false); break;
            case KC_ENT:  oled_write_P(PSTR("En"), false); break;
            default:      oled_write_P(PSTR("?"), false); break;
        }
    }
}

static void oled_write_keycode(uint16_t keycode) {
    uint16_t mod = keycode & 0xFF00;
    uint8_t key = keycode & 0xFF;
    if (mod != 0) {
        if (mod == QK_LGUI || mod == QK_RGUI) oled_write_P(PSTR("W+"), false);
        else if (mod == QK_LSFT || mod == QK_RSFT) oled_write_P(PSTR("S+"), false);
        else if (mod == QK_LCTL || mod == QK_RCTL) oled_write_P(PSTR("C+"), false);
        else if (mod == QK_LALT || mod == QK_RALT) oled_write_P(PSTR("A+"), false);
        else oled_write_P(PSTR("M+"), false);
        oled_write_key(key);
        return;
    }

    switch (keycode) {
        case KC_VOLD: oled_write_P(PSTR("Vol-"), false); break;
        case KC_VOLU: oled_write_P(PSTR("Vol+"), false); break;
        case KC_PGUP: oled_write_P(PSTR("PgUp"), false); break;
        case KC_PGDN: oled_write_P(PSTR("PgDn"), false); break;
        case KC_MNXT: oled_write_P(PSTR("Next"), false); break;
        case KC_MPRV: oled_write_P(PSTR("Prev"), false); break;
        case KC_MUTE: oled_write_P(PSTR("Mute"), false); break;
        case KC_MS_WH_UP: oled_write_P(PSTR("ScrU"), false); break;
        case KC_MS_WH_DOWN: oled_write_P(PSTR("ScrD"), false); break;
        case KC_TRNS:
        case KC_NO:   oled_write_P(PSTR("None"), false); break;
        default:      oled_write_key(key); break;
    }
}

bool oled_task_user(void) {
    bool oled_on = is_oled_on();
    if (oled_on && !oled_was_on) {
        wake_timer = timer_read32();
    }
    oled_was_on = oled_on;

    if (timer_elapsed32(wake_timer) < OLED_LOGO_DURATION) {
        if (oled_current_mode == 1) {
            oled_clear();
            oled_current_mode = 0;
        }
        return true;
    }

    if (last_input_activity_elapsed() < OLED_STATUS_TIMEOUT || get_current_wpm() > 0) {
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

#ifdef SPLIT_KEYBOARD
        if (!is_keyboard_master()) {
            ccw = user_state.ccw_encoder;
            cw = user_state.cw_encoder;
        } else {
            uint8_t enc_idx = is_keyboard_left() ? 0 : 1;
            for (int i = 3; i >= 0; i--) {
                if ((layer_state & (1UL << i)) || i == 0) {
                    if (ccw == KC_TRNS) ccw = dynamic_keymap_get_encoder(i, enc_idx, false);
                    if (cw == KC_TRNS) cw = dynamic_keymap_get_encoder(i, enc_idx, true);
                }
            }
        }
#else
        for (int i = 3; i >= 0; i--) {
            if ((layer_state & (1UL << i)) || i == 0) {
                if (ccw == KC_TRNS) ccw = dynamic_keymap_get_encoder(i, 0, false);
                if (cw == KC_TRNS) cw = dynamic_keymap_get_encoder(i, 0, true);
            }
        }
#endif

        if (ccw == KC_TRNS && cw == KC_TRNS) {
            oled_write_P(PSTR("None      \n"), false);
        } else {
            uint16_t ccw_mod = ccw & 0xFF00;
            uint16_t cw_mod = cw & 0xFF00;
            uint8_t ccw_key = ccw & 0xFF;
            uint8_t cw_key = cw & 0xFF;

            if (ccw_mod != 0 && ccw_mod == cw_mod) {
                if (ccw_mod == QK_LGUI || ccw_mod == QK_RGUI) oled_write_P(PSTR("Gui+"), false);
                else if (ccw_mod == QK_LSFT || ccw_mod == QK_RSFT) oled_write_P(PSTR("Sft+"), false);
                else if (ccw_mod == QK_LCTL || ccw_mod == QK_RCTL) oled_write_P(PSTR("Ctl+"), false);
                else if (ccw_mod == QK_LALT || ccw_mod == QK_RALT) oled_write_P(PSTR("Alt+"), false);
                else oled_write_P(PSTR("Mod+"), false);

                oled_write_key(ccw_key);
                oled_write_P(PSTR("/"), false);
                oled_write_key(cw_key);
                oled_write_P(PSTR("  \n"), false);
            } else {
                oled_write_keycode(ccw);
                oled_write_P(PSTR("/"), false);
                oled_write_keycode(cw);
                oled_write_P(PSTR(" \n"), false);
            }
        }

        // Modifiers Status
        oled_set_cursor(0, 11);
        oled_write_P(PSTR("Mods:\n"), false);
        uint8_t mods = get_mods();
        char mod_str[11] = "          "; // 10 spaces
        if (mods & MOD_MASK_SHIFT) { mod_str[0]='S'; mod_str[1]='f'; mod_str[2]='t'; }
        if (mods & MOD_MASK_CTRL)  { mod_str[4]='C'; mod_str[5]='t'; mod_str[6]='l'; }

        bool cw_on = false;
#ifdef SPLIT_KEYBOARD
        cw_on = is_keyboard_master() ? is_caps_word_on() : user_state.caps_word_on;
#else
        cw_on = is_caps_word_on();
#endif
        if (cw_on) { mod_str[8]='C'; mod_str[9]='W'; }

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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool caps_active = is_caps_active();
    uint8_t layer = get_highest_layer(layer_state);
    bool is_base = (layer == 0);

#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
#endif
        uint8_t master_min = 0;
        uint8_t master_max = 58;
#ifdef SPLIT_KEYBOARD
        master_min = is_keyboard_left() ? 0 : 29;
        master_max = is_keyboard_left() ? 29 : 58;
#endif

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index >= master_min && index < master_max) {
                    uint16_t keycode = dynamic_keymap_get_keycode(layer, row, col);
                    rgb_t rgb = get_keycode_color(keycode, caps_active, is_base);
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                }
            }
        }
#ifdef SPLIT_KEYBOARD
    } else {
        uint8_t slave_min = is_keyboard_left() ? 0 : 29;
        uint8_t slave_max = is_keyboard_left() ? 29 : 58;

        for (uint8_t i = led_min; i < led_max; ++i) {
            if (i >= slave_min && i < slave_max) {
                uint8_t idx = i - slave_min;
                uint8_t color_idx = unpack_color_5bit(user_state.led_colors, idx);
                rgb_t rgb = get_color_from_index(color_idx);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
#endif
    return false;
}
