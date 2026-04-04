#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "deferred_exec.h"

#define _DVORAK_MAC 0
#define _DVORAK_WINDOWS 1
#define _ACTIONS 2
#define _NUMPAD 3
#define _FUNCTIONS 4

// --- COMMON Short-cuts ---
#define ZOOM_RAISE_HAND ROPT(KC_Y)
#define ZOOM_LEAVE_MEETING G(KC_W)
#define ZOOM_TOGGLE_VIDEO LSG(KC_V)
#define ZOOM_TOGGLE_MUTE LSG(KC_A)

// --- MAC Short-cuts (Layer 0) ---
#define MAC_REFRESH G(KC_R)
#define MAC_SLACK_ADD_LINK SGUI(KC_U)
#define MAC_COPY G(KC_C)
#define MAC_CUT G(KC_X)
#define MAC_PASTE G(KC_V)
#define MAC_PASTE_SPECIAL RCS(KC_V)
#define MAC_SELECT_ALL G(KC_A)
#define MAC_SAVE G(KC_S)
#define MAC_SPOTLIGHT G(KC_SPC)
#define MAC_SCRNSHOT LSG(KC_5)
#define MAC_NEXT_WINDOW G(KC_GRV)
#define MAC_CLOSE_OTHERS LAG(KC_W)


// --- ACTION Short-cuts (Layer 2) ---
#define ACT_SCREENSHOT SGUI(KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK_MAC] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, MAC_REFRESH,                        MAC_SLACK_ADD_LINK, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
        KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, MAC_SELECT_ALL,                        KC_SLASH, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS,
        KC_CAPS, LT(_ACTIONS, KC_A), KC_O, KC_E, KC_U, KC_I, MAC_SAVE,                        _______, KC_D, KC_H, KC_T, KC_N, KC_S, LT(_ACTIONS, KC_MINUS),
        KC_LSFT, LGUI_T(KC_SCLN), LALT_T(KC_Q), KC_J, KC_K, KC_X, MAC_SPOTLIGHT,                        _______, KC_B, KC_M, KC_W, RALT_T(KC_V), RGUI_T(KC_Z), KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LBRC, KC_RBRC,                                                                   KC_SCLN, KC_GRV, KC_RALT, KC_RCTL,
                                            KC_SPC, KC_BSPC,                        KC_DEL, KC_ENT,
                                            MAC_NEXT_WINDOW, MAC_CLOSE_OTHERS,                        _______, _______,
                                            MAC_COPY, MAC_PASTE,                        MAC_CUT, MAC_PASTE_SPECIAL
        ),

    [_DVORAK_WINDOWS] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, MAC_REFRESH,                        MAC_SLACK_ADD_LINK, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
        KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, MAC_SELECT_ALL,                        KC_SLASH, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS,
        KC_CAPS, LT(_ACTIONS, KC_A), KC_O, KC_E, KC_U, KC_I, MAC_SAVE,                        _______, KC_D, KC_H, KC_T, KC_N, KC_S, LT(_ACTIONS, KC_MINUS),
        KC_LSFT, LGUI_T(KC_SCLN), LALT_T(KC_Q), KC_J, KC_K, KC_X, MAC_SPOTLIGHT,                        _______, KC_B, KC_M, KC_W, RALT_T(KC_V), RGUI_T(KC_Z), KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LBRC, KC_RBRC,                                                                   KC_SCLN, KC_GRV, KC_RALT, KC_RCTL,
                                            KC_SPC, KC_BSPC,                        KC_DEL, KC_ENT,
                                            KC_APP, MAC_CLOSE_OTHERS,                        _______, _______,
                                            MAC_COPY, MAC_PASTE,                        MAC_CUT, MAC_PASTE_SPECIAL
        ),

    [_ACTIONS] = LAYOUT(
        TO(0), LCAG(KC_1), LCAG(KC_2), LCA(KC_D), LCA(KC_LEFT), LCA(KC_E), LCA(KC_C),                        MEH(KC_5), LCA(KC_T), LCA(KC_RIGHT), LCA(KC_G), LCAG(KC_9), LCAG(KC_0), _______,

        _______, _______, _______, LSA(KC_B), LSA(KC_S), LSA(KC_C), _______,                        KC_APPLICATION, _______, KC_HOME, KC_UP, KC_END, _______, _______,
        _______, _______, _______, _______, LSA(KC_P), LSA(KC_D), _______,                        ACT_SCREENSHOT, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RALT, _______,
        _______, _______, _______, _______, _______, _______, QK_BOOT,                        QK_CLEAR_EEPROM, _______, KC_PGUP, _______, KC_PGDN, _______, _______,
        _______, _______, _______, _______,                                                                   SGUI(KC_M), SGUI(KC_O), SGUI(KC_H), SGUI(KC_K),
                                            _______, _______,                        _______, _______,
                                            _______, LCA(KC_EQL),                        KC_MPLY, KC_KB_MUTE,
                                            HYPR(KC_SPC), LCA(KC_MINUS),                        KC_VOLU, KC_VOLD
        ),

    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                        _______, KC_NUM_LOCK, KC_KP_ASTERISK, KC_KP_PLUS, KC_KP_MINUS, _______, _______,
        _______, _______, KC_UP, _______, _______, _______, _______,                        _______, KC_KP_SLASH, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______,                        _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
        _______, _______, _______, _______,                                                                   KC_KP_0, KC_KP_DOT, _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______
        ),

    [_FUNCTIONS] = LAYOUT(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,                                                                   _______, _______, _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______
        )
};

uint32_t set_os_layer(uint32_t trigger_time, void* cb_arg) {
    switch (detected_host_os()) {
        case OS_MACOS:
        case OS_IOS:
            keymap_config.swap_lctl_lgui = false;
            keymap_config.swap_rctl_rgui = false;
            set_single_persistent_default_layer(_DVORAK_MAC);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
            keymap_config.swap_lctl_lgui = true;
            keymap_config.swap_rctl_rgui = true;
            set_single_persistent_default_layer(_DVORAK_WINDOWS);
            break;
        default:
            return 500;
    }
    return 0;
}

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
#else
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
    debug_mouse=false;
#endif

    defer_exec(500, set_os_layer, NULL);
}

void set_colour(uint8_t led_index, uint16_t hue, uint8_t sat, uint8_t val){
    uint8_t brightness = val;
    if (val > rgb_matrix_get_val()) {
        brightness = rgb_matrix_get_val();
    }
    HSV hsv = (HSV){hue, sat, brightness};
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
}

// Custom RGB indicator behaviour:
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t led_processed_count = 0;
    //uint8_t brightness = rgb_matrix_config.hsv.v;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (led_processed_count == RGB_MATRIX_LED_PROCESS_LIMIT){
                return false;
            }
            uint8_t led_index = g_led_config.matrix_co[row][col];
            uint16_t keycode = keymap_key_to_keycode(0, (keypos_t){col,row});
            if (led_index >= led_min && led_index <= led_max && led_index != NO_LED) {
                led_processed_count++;

                switch (keycode)
                {
                    case KC_CAPS_LOCK:
                        set_colour(led_index, HSV_GREEN);
                        break;
                    case KC_A ... KC_Z:
                        if(host_keyboard_led_state().caps_lock){
                            set_colour(led_index, HSV_RED);
                        }
                        else{
                            set_colour(led_index, HSV_BLUE);
                        }
                        break;
                    case KC_ENTER:
                        set_colour(led_index, HSV_MAGENTA);
                        break;
                    case KC_BACKSPACE:
                    case KC_DELETE:
                    case QK_BOOTLOADER:
                        set_colour(led_index, HSV_RED);
                        break;
                    case KC_TAB ... KC_SLASH:
                    case MODIFIER_KEYCODE_RANGE:
                        set_colour(led_index, HSV_GOLD);
                        break;
                    case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
                    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                    case MAGIC_KEYCODE_RANGE:
                        set_colour(led_index, HSV_PURPLE);
                        break;
                    default:
                        //set_colour(led_index, base_colour.r, base_colour.g, base_colour.b);
                        break;
                }

                // Whenever a layer above base is active, recolour only the keys that are different on that layer:
                if (get_highest_layer(layer_state) > 0) {
                    uint8_t layer = get_highest_layer(layer_state);
                    uint16_t momentary_keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (momentary_keycode > KC_TRNS) {
                        // The middle layer is green, except that the numpad section turns
                        // orange when Num Lock is on:
                        if (host_keyboard_led_state().num_lock &&
                        (momentary_keycode == KC_KP_EQUAL ||
                        (momentary_keycode >= KC_NUM_LOCK && momentary_keycode <= KC_KP_DOT)
                        )) {
                            if(momentary_keycode == KC_NUM_LOCK){
                                set_colour(led_index,  HSV_GREEN);
                            }
                            else
                            {
                                set_colour(led_index, HSV_PURPLE);
                            }
                        } else {
                            set_colour(led_index, HSV_BLUE);
                        }
                        // Light arrow keys orange if Scroll Lock is on, otherwise light them purple:
                        if (momentary_keycode >= KC_RIGHT && momentary_keycode <= KC_UP) {
                            if (host_keyboard_led_state().scroll_lock) {
                                set_colour(led_index, HSV_ORANGE);
                            } else {
                                set_colour(led_index, HSV_PURPLE);
                            }
                        }
                    }
                    else{
                        set_colour(led_index, HSV_OFF);
                    }
                }
            }
        }
    }
    return false;
}
